#pragma once

namespace LTB {

    class Layer {
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnImGuiRender() {}

        inline const std::string& GetName() const { return mDebugName;}
    private:
        std::string mDebugName;
    };
}