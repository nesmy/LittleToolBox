#pragma once
#include "EditorLayer.h"
#include "MenuList.h"
#include "Auxiliaries/ECS.h"

namespace LTB {

    class HierarchyWindow : public IWidget{
    public:
        inline HierarchyWindow(EditorLayer* context): IWidget(context)
		{
			mWindow.push_back(context->CreateWidget<MenuListWindow>());
		}

		inline void OnShow(EditorLayer* context) override
		{
			if(ImGui::Begin(ICON_FA_CUBES "\tHierarchy"))
			{
				context->GetActiveScene().EnttView<Entity, InfoComponent>([&] (auto entity, auto& info)
				{
					// check if current entity is selected
					bool isSelected = (mSelected.ID() == entity.ID());

					// makes each selectable unique
					ImGui::PushID((int32_t)entity.ID());

					// compute selectable label
					std::string label = ICON_FA_CUBE "\t" + info.Name;

					// special label with icons
					// if(entity.template Has<DirectLightComponent>())
					// 	label = ICON_FA_SUN "\t" + info.Name;
					if(entity.template Has<CameraComponent>())
						label = ICON_FA_VIDEO "\t" + info.Name;
					// if(entity.template Has<RigidBodyComponent>())
					// 	label = ICON_FA_PERSON "\t" + info.Name;
					// if(entity.template Has<SkyboxComponent>())
					// 	label = ICON_FA_CLOUD_SUN_RAIN "\t" + info.Name;
					if(entity.template Has<Camera2DComponent>())
					    label = ICON_FA_VIDEO "\t" + info.Name;

					// show entity selectable
					if(ImGui::Selectable(label.c_str(), &isSelected))
					{                        
						Application::Get().PostEvent<SelectEvent>(entity);
					}

					if (ImGui::IsItemHovered())
					{
						if (ImGui::IsMouseDoubleClicked(0) && isSelected)
						{
							ImGui::OpenPopup("ListComp");
						}
						if (ImGui::IsMouseReleased(1) && isSelected)
						{
							ImGui::OpenPopup("ListComp");
						}
					}

					if (ImGui::BeginPopup("ListComp"))
					{
						if(ImGui::BeginMenu("##"))
						{
							if (ImGui::MenuItem(ICON_FA_FORWARD " Add Camera"))
							{
								entity.template Attach<CameraComponent>();
							}
							if (ImGui::MenuItem(ICON_FA_FORWARD " Add Camera2D"))
							{
								entity.template Attach<Camera2DComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add DirectLight"))
							{
								// entity.template Attach<DirectLightComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add PointLight"))
							{
								// entity.template Attach<PointLightComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add SpotLight"))
							{
								// entity.template Attach<SpotLightComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add Sprite"))
							{
								entity.template Attach<SpriteComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add RigidBody"))
							{
								// entity.template Attach<RigidBodyComponent>();
								// entity.template Attach<ColliderComponent>().Collider.Type = ColliderType::BOX;
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add Collider"))
							{
								// entity.template Attach<ColliderComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add SkyBox"))
							{
								// entity.template Attach<SkyboxComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add Model"))
							{
								// entity.template Attach<ModelComponent>();
							}
							if(ImGui::MenuItem(ICON_FA_FORWARD " Add Script"))
							{
								// entity.template Attach<ScriptComponent>();
							}
							ImGui::EndMenu();
						}
						if(ImGui::Selectable(ICON_FA_RECYCLE "\tDelete"))
						{
							entity.Destroy();
						}
				    	ImGui::EndPopup();
					}


					// w are required to pop
					ImGui::PopID();
				});
			}
			ImGui::End();
		}

        inline void OnSelect(Entity entity) override
        {
            mSelected = entity;            
        }
    private:
        Entity mSelected;
	    std::vector<Widget> mWindow;
    };
}