#pragma once

extern LTB::Application* LTB::CreateApplication();

int main(int argc, char** argv){

    LTB::Log::Init();
    LTB_CORE_INFO("Loading App");
    auto app = LTB::CreateApplication();

    app->Run();

    delete app;
    return 0;
}