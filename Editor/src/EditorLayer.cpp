#include "EditorLayer.h"
#include "Core/Application.h"
#include "MenuBar.h"
#include "Inspector.h"
#include "Hierarchy.h"
#include "Viewport.h"
#include "Resource.h"
#include "SceneSerializer.h"
#include <ImGuizmo.h>
#include <ImGuiFileDialog.h>


namespace LTB {

    EditorLayer::EditorLayer()
        :Layer("EditorLayer"){}

    void EditorLayer::OnAttach(){
        Application::Get().AttachCallback<SelectEvent>([this] (auto e){
            for(auto& window : mWindows)
                window->OnSelect(mActiveScene->ToEntt<Entity>(e.EnttID));
        });        

        mActiveScene = CreateRef<Scene>();
        mBuffer = CreateScope<Framebuffer>(GetScreenWidth(), GetScreenHeight());

        OnGuiStart();

        auto asset = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/1_club.png");
        auto asset1 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/2_club.png");
        auto asset2 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/3_club.png");
        auto asset3 = Application::Get().GetAssets().AddTexture(RandomU64(), "Resources/Textures/Game/club/4_club.png");
        auto model1 = Application::Get().GetAssets().AddModel(RandomU64(), "Resources/Models/sphere.obj");

        SceneSerializer serializer(mActiveScene);
        // serializer.Deserialize("Resources/Saves/test.data");

        // auto cam = Application::Get().CreateEntt<Entity>();
        // cam.Attach<InfoComponent>().Name = "Cam";
        // cam.Attach<CameraComponent>();
        // auto& camTs = cam.Attach<TransformComponent>().Transforms;
        // camTs.translation = Vector3{0.0f};
#if 0
        auto test = mActiveScene->CreateEntity("Test");
        auto& mod = test.Attach<ModelComponent>();
        mod.mModel = model1->Data;
        mod.Box = GetMeshBoundingBox(mod.mModel.meshes[0]);

        auto test2 = mActiveScene->CreateEntity("Test1");
        test2.Get<TransformComponent>().Transforms.translation.x = -10;
        auto& mod2 = test2.Attach<ModelComponent>();
        mod2.mModel = model1->Data;
        mod2.Box = GetMeshBoundingBox(mod2.mModel.meshes[0]);

        auto test1 = mActiveScene->CreateEntity("Test2");
        auto& ts = test1.Get<TransformComponent>().Transforms;
        auto& sprite = test1.Attach<SpriteComponent>().mSprite;
        sprite.Texture = asset1->Data;
        ts.translation.x = 10;
        sprite.Box = {ts.translation.x, ts.translation.y, (float)(sprite.Texture.width + 5), (float)(sprite.Texture.height + 5)};
        // ts.translation.y = 100;
#endif
    }

    void EditorLayer::OnDetach(){

    }

    void EditorLayer::OnUpdate(float deltaTime){
        
        mBuffer->Resize();
        mBuffer->Bind();
        ClearBackground(GREEN);
        switch(mSceneState){
            case SceneState::Edit:
            {
                mActiveScene->OnUpdateEditor(deltaTime);
                break;
            }
            case SceneState::Play:
            {
                mActiveScene->OnUpdateRuntime(deltaTime);
                break;
            }
        }
        mBuffer->Unbind();
    }

    void EditorLayer::OnImGuiRender(){
        // Set up the main viewport
        static auto viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowViewport(viewport->ID);
        ImGui::SetNextWindowSize(viewport->Size);
        ImGui::SetNextWindowPos(viewport->Pos);

        static auto flags = ImGuiWindowFlags_NoBringToFrontOnFocus |
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_MenuBar;

        // if you want windows to dock to the viewport, call this.
    #ifdef IMGUI_HAS_DOCK
            ImGui::DockSpaceOverViewport(0,  NULL, ImGuiDockNodeFlags_PassthruCentralNode); // set ImGuiDockNodeFlags_PassthruCentralNode so that we can see the raylib contents behind the dockspace
    #endif
        {
            // Set window style
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 1));
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);

            // Begin the main window
            ImGui::Begin("MainWindow", NULL, flags);
            {
                // Set up the main dockspace
                ImGui::DockSpace(ImGui::GetID("MainDockspace"), ImVec2(0, 0),
                ImGuiDockNodeFlags_PassthruCentralNode);
                ImGui::PopStyleColor();
                ImGui::PopStyleVar(3);

                // Iterate through each window in the vector and call OnShow
                for(auto& window : mWindows)
                {
                    window->OnShow(this);
                    window->OnShowAsset(this);
                }

                // m_ViewportFocused = ImGui::IsWindowFocused();
                if (ImGuiFileDialog::Instance()->Display("OpenScene")) {
                    if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                        filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        filePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                        // action
                        if(!filePathName.empty())
                            OpenScene(filePathName);
                    }

                    // close
                    ImGuiFileDialog::Instance()->Close();
                }

                if (ImGuiFileDialog::Instance()->Display("SaveSceneAs")) {
                    if (ImGuiFileDialog::Instance()->IsOk()) { // action if OK
                        std::string SavefilePathName = ImGuiFileDialog::Instance()->GetFilePathName();
                        std::string SavefilePath = ImGuiFileDialog::Instance()->GetCurrentPath();
                        // action
                        if (!SavefilePathName.empty())
                        {
                        	SerializeScene(mActiveScene, SavefilePathName);
                        	mEditorScenePath = SavefilePathName;
                        }
                    }

                    // close
                    ImGuiFileDialog::Instance()->Close();
                }

                // Interface update
                OnGuiFrame();
            }
            ImGui::End();
        }
                    
    }

    void EditorLayer::OnGuiStart(){
        AttachWindow<MenuBarWindow>();
        AttachWindow<InspectorWindow>();
        AttachWindow<HierarchyWindow>();
        AttachWindow<ViewportWindow>();
        AttachWindow<ResourceWindow>();
    }

    void EditorLayer::OnGuiFrame(){

    }

    void EditorLayer::SerializeScene(Ref<Scene> scene, const std::filesystem::path& path)
	{
		SceneSerializer serializer(scene);
		serializer.Serialize(path.string());
	}

    void EditorLayer::Controls()
    {
        bool control = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
        bool shift = IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT);
        bool alt = IsKeyDown(KEY_LEFT_ALT) || IsKeyDown(KEY_RIGHT_ALT);
        if(IsKeyPressed(KEY_N)){
            if(control)
                NewScene();
        }

        if(IsKeyPressed(KEY_O)){
            if(control)
                OpenScene();
        }

        if(IsKeyPressed(KEY_S)){
            if(control){
                if(shift)
                    SaveSceneAs();
                else
                    SaveScene();
            }
                
        }
        if(IsKeyPressed(KEY_F4)){
            if(alt)
                Application::Get().Close();
        }


    }

    void EditorLayer::NewScene(){
        mActiveScene = CreateRef<Scene>();
        mEditorScenePath = std::filesystem::path();
    }

    void EditorLayer::OpenScene(){
        
        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("OpenScene", "Choose File", ".data", config);        
    }

    void EditorLayer::OpenScene(const std::filesystem::path& path){
        if (mSceneState != SceneState::Edit)
        {
            // OnSceneStop();
        }

		if (path.extension().string() != ".data")
		{
			LTB_WARN("Could not load {0} - not a scene file", path.filename().string());
			return;
		}
		
		Ref<Scene> newScene = CreateRef<Scene>();
		SceneSerializer serializer(newScene);
		if (serializer.Deserialize(path.string()))
		{					
			mActiveScene = newScene;
			mEditorScenePath = path;
		}
    }

    void EditorLayer::SaveScene(){
        if (!mEditorScenePath.empty())
			SerializeScene(mActiveScene, mEditorScenePath);			
		else
			SaveSceneAs();
    }

    void EditorLayer::SaveSceneAs()
	{

        IGFD::FileDialogConfig config;
        config.path = ".";
        ImGuiFileDialog::Instance()->OpenDialog("SaveSceneAs", "Choose File", ".data", config); 
	}
}