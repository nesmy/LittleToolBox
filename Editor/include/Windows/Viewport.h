#pragma once
#include "EditorLayer.h"
#include "FA.h"
#include "Math/LTBMath.h"
#include <ImGuizmo.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace LTB {
    class ViewportWindow : public IWidget {
    public:
        inline ViewportWindow(EditorLayer* context): IWidget(context)
        {
            // m_Frame = (ImTextureID)context->GetSceneFrame();
            mPlay = LoadTexture("Resources/Icons/PlayButton.png");
            viewportRect = {0,0, (float)GetScreenWidth(), (float)GetScreenHeight()};
        }

        inline void OnShow(EditorLayer* context) override
        {
            
            bool Open = false;
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
		    ImGui::SetNextWindowSizeConstraints(ImVec2(400, 400), ImVec2((float)GetScreenWidth(), (float)GetScreenHeight()));
            if(ImGui::Begin(ICON_FA_IMAGE "\tViewport", &Open, ImGuiWindowFlags_NoScrollbar))
            {

                auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
                auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
                auto viewportOffset = ImGui::GetWindowPos();
                m_ViewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
                m_ViewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

                m_ViewportFocused = ImGui::IsWindowFocused();
                m_ViewportHovered = ImGui::IsWindowHovered();                
                context->GetActiveScene().BlockUpdate(!m_ViewportFocused && !m_ViewportHovered);

                ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
                m_ViewportSize = { viewportPanelSize.x, viewportPanelSize.y };

                if (m_ViewportSize.x > 0 && m_ViewportSize.y > 0) {
                        viewportRect.width = m_ViewportSize.x;
                        viewportRect.height = m_ViewportSize.y;
                }
                //-------------------------------------

                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 2));
                ImGui::PushStyleVar(ImGuiStyleVar_ItemInnerSpacing, ImVec2(0, 0));
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
                auto& colors = ImGui::GetStyle().Colors;
                const auto& buttonHovered = colors[ImGuiCol_ButtonHovered];
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(buttonHovered.x, buttonHovered.y, buttonHovered.z, 0.5f));
                const auto& buttonActive = colors[ImGuiCol_ButtonActive];
                ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(buttonActive.x, buttonActive.y, buttonActive.z, 0.5f));

                ImGui::Begin("##toolbar", nullptr, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);

                float size = ImGui::GetWindowHeight() - 4.0f;
                // Ref<Texture2D> icon = m_SceneState == SceneState::Edit ? m_IconPlay : m_IconStop;
                ImGui::SetCursorPosX((ImGui::GetWindowContentRegionMax().x * 0.5f) - (size * 0.5f));
                if (ImGui::ImageButton("##play",(ImTextureID)&mPlay, ImVec2(size, size)))
                {
                    // if (m_SceneState == SceneState::Edit)
                    //     OnScenePlay();
                    // else if (m_SceneState == SceneState::Play)
                    //     OnSceneStop();
                }
                ImGui::PopStyleVar(2);
                ImGui::PopStyleColor(3);
                ImGui::End();
                //-----------------------------------------------
                m_Frame = (ImTextureID)&context->GetBuffer()->GetTexture().texture;                
                ImGui::Image(m_Frame, ImVec2{m_ViewportSize.x, m_ViewportSize.y}, ImVec2{0, 1}, ImVec2{1,0});

                // get imgui io
                auto& io = ImGui::GetIO();

                if(ImGui::IsWindowHovered())
                {                        
                    
                }

                //gizmo3D
                if(!context->GetActiveScene().Is2D()){
                    Inputs();
                    auto& camera = context->GetActiveScene().GetCam();
                    ray = GetMouseRay({ImGui::GetMousePos().x, ImGui::GetMousePos().y}, camera);
                    if(ImGui::IsItemHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        
                        ImVec2 mousePos = ImGui::GetMousePos();
                        ImVec2 viewportPos = ImGui::GetItemRectMin();  // Top-left of viewport in screen space

                        Vector2 adjustedMousePos = { 
                            mousePos.x - viewportPos.x,  // Convert to viewport-local coordinates
                            mousePos.y - viewportPos.y
                        };
                        mSelected = PickObject(camera, context);
                    }
                    float matrix[16];                


                    Matrix view = GetCameraMatrix(camera);
                    Matrix projection = MatrixPerspective(DEG2RAD * camera.fovy, (m_ViewportBounds[1].x - m_ViewportBounds[0].x) / (m_ViewportBounds[1].y - m_ViewportBounds[0].y), 0.01f, 1000.0f);                
                    // Snapping
                    bool snap = IsKeyPressed(KEY_LEFT_CONTROL);
                    float snapValue = 0.5f; // Snap to 0.5m for translation/scale
                    // Snap to 45 degrees for rotation
                    if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
                        snapValue = 45.0f;

                    float snapValues[3] = { snapValue, snapValue, snapValue };

                    if(mSelected != NENTT){
                        context->GetActiveScene().EnttView<Entity, ModelComponent>([this,&snap, &snapValues, &matrix, &view, &projection] (auto& entity, auto& comp) {
                            if(mSelected.ID() == entity.ID()){
                                auto& transform = entity.template Get<TransformComponent>().Transforms;
                                auto& name = entity.template Get<InfoComponent>().Name;
                                Matrix worldMatrix = Math::GetTransformMatrix(transform.translation, transform.rotation, transform.scale);
                                memcpy(matrix, MatrixToFloatV(MatrixTranspose(worldMatrix)).v, sizeof(matrix));
                                ImGuizmo::SetOrthographic(false);
                                ImGuizmo::SetDrawlist();

                                ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);                            
                                ImGuizmo::Manipulate(MatrixToFloatV(view).v, 
                                                    MatrixToFloatV(projection).v, 
                                                    (ImGuizmo::OPERATION)m_GizmoType, 
                                                    ImGuizmo::WORLD, matrix                                               
                                                    );

                                // Matrix updatedMatrix = MatrixTranspose(*(Matrix*)matrix);
                                // Matrix updatedMatrix = MatrixTranspose(Matrix{ matrix[0], matrix[1], matrix[2], matrix[3],
                                //                                 matrix[4], matrix[5], matrix[6], matrix[7],
                                //                                 matrix[8], matrix[9], matrix[10], matrix[11],
                                //                                 matrix[12], matrix[13], matrix[14], matrix[15] });
                                // // MatrixDecompose(updatedMatrix, &transform.translation, &transform.rotation, &transform.scale);
                                // // Extract new translation, rotation, and scale
                                // Vector3 newTranslation, newScale;
                                // Quaternion newRotation;
                                // MatrixDecompose(updatedMatrix, &newTranslation, &newRotation, &newScale);
                                // transform.translation = newTranslation;
                                // transform.rotation = newRotation;
                                // transform.scale = newScale;
                                LTB_INFO("{}", name);
                            }
                        });
                    }
                }else{
                    auto& camera = context->GetActiveScene().GetCam2D();
                    if(ImGui::IsItemHovered() && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        mSelected = PickObject(camera, context);
                        LTB_INFO("clik");
                    }

                    Matrix view = GetCameraMatrix2D(camera);
                    Matrix projection = MatrixOrtho(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y, 1.0, 10.0f);

                    float matrix[16];

                    if(mSelected != NENTT){
                        context->GetActiveScene().EnttView<Entity, SpriteComponent>([this,&matrix, &view, &projection] (auto entity, auto& comp) {
                            if(mSelected.ID() == entity.ID()){
                                auto& transform = entity.template Get<TransformComponent>().Transforms;
                                auto& name = entity.template Get<InfoComponent>().Name;
                                Matrix worldMatrix = Math::GetTransformMatrix(transform.translation, transform.rotation, transform.scale);
                                memcpy(matrix, MatrixToFloatV(MatrixTranspose(worldMatrix)).v, sizeof(matrix));
                                ImGuizmo::SetOrthographic(false);
                                ImGuizmo::SetDrawlist();

                                ImGuizmo::SetRect(m_ViewportBounds[0].x, m_ViewportBounds[0].y, m_ViewportBounds[1].x - m_ViewportBounds[0].x, m_ViewportBounds[1].y - m_ViewportBounds[0].y);                            
                                ImGuizmo::Manipulate(MatrixToFloatV(view).v, 
                                                    MatrixToFloatV(projection).v, 
                                                    (ImGuizmo::OPERATION)m_GizmoType, 
                                                    ImGuizmo::WORLD, matrix                                               
                                                    );

                                LTB_INFO("{}", name);
                            }

                            if(CheckCollisionPointRec({ImGui::GetMousePos().x, ImGui::GetMousePos().y}, comp.mSprite.Box)){
                                // entityID = entity;
                                LTB_INFO("RECT2");
                            }
                        });
                    }
                    
                }

                // context->m_ViewportFocused = ImGui::IsWindowFocused();
                DrawRay(ray, MAROON);
            }
            ImGui::End();
            ImGui::PopStyleVar();
        }

        inline void OnSelect(Entity entity) override
        {
            mSelected = entity;
        }
        
        inline Entity PickObject(Camera3D camera, EditorLayer* context){
            
            Entity entityID;            
            RayCollision collision = {0};
            collision.distance = FLT_MAX;
            collision.hit = false;
            
            context->GetActiveScene().EnttView<Entity, ModelComponent>([this, &collision, &entityID] (auto& entity, auto& comp) {
                
                RayCollision boxHitInfo = GetRayCollisionBox(ray, comp.Box);

                if((boxHitInfo.hit) && (boxHitInfo.distance < collision.distance)){
                    collision = boxHitInfo;
                    entityID = entity;
                    // Check ray collision against model meshes
                    RayCollision meshHitInfo = { 0 };
                    for (int m = 0; m < comp.mModel.meshCount; m++)
                    {
                        // NOTE: We consider the model.transform for the collision check but 
                        // it can be checked against any transform Matrix, used when checking against same
                        // model drawn multiple times with multiple transforms
                        meshHitInfo = GetRayCollisionMesh(ray, comp.mModel.meshes[m], comp.mModel.transform);
                        if (meshHitInfo.hit)
                        {
                            // Save the closest hit mesh
                            if ((!collision.hit) || (collision.distance > meshHitInfo.distance)) collision = meshHitInfo;
                            
                            break;  // Stop once one mesh collision is detected, the colliding mesh is m
                        }
                    }

                    if (meshHitInfo.hit)
                    {
                        collision = meshHitInfo;
                        entityID = entity;                        
                    }
                }
            });
            return entityID;
        }

        inline Entity PickObject(Camera2D camera, EditorLayer* context){
            Entity entityID;
            context->GetActiveScene().EnttView<Entity, SpriteComponent>([this, &entityID] (auto& entity, auto& comp) {
                if(CheckCollisionPointRec(GetMousePosition(), comp.mSprite.Box)){
                    entityID = entity;                    
                }
            });
            return entityID;
        }

        

        inline void Inputs(){
            
            bool control = IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL);
            bool shift = IsKeyPressed(KEY_LEFT_SHIFT) || IsKeyPressed(KEY_RIGHT_SHIFT);

            // Gizmos			
            if(!ImGuizmo::IsUsing() && IsKeyPressed(KEY_Z)){
                m_GizmoType = -1;
            }
            if(!ImGuizmo::IsUsing() && IsKeyPressed(KEY_T)){
                m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
            }
            if(!ImGuizmo::IsUsing() && IsKeyPressed(KEY_R)){
                m_GizmoType = ImGuizmo::OPERATION::ROTATE;
            }
            if(!ImGuizmo::IsUsing() && IsKeyPressed(KEY_C)){
                m_GizmoType = ImGuizmo::OPERATION::SCALE;
            }
        }

    private:
        ImTextureID m_Frame;
        ImVec2 m_Viewport;
        Texture mPlay;
        Ray ray = {0};
        ImVec2 m_ViewportBounds[2];
        ImVec2 m_ViewportSize;
        Rectangle viewportRect;
        bool m_ViewportFocused = false, m_ViewportHovered = false;
        Entity mSelected;
        int m_GizmoType = -1;		
    };
}