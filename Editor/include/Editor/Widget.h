#pragma once

#include "Events.h"

namespace LTB {

    class EditorLayer;

    class IWidget{
    public:
        IWidget(EditorLayer*) {
            // m_SelectedAsset = CreateRef<AssetID>(0);
        };
        virtual ~IWidget() = default;
        virtual void OnSelect(Entity) {}
        // virtual void OnSelect(AssetID) {}
        virtual void OnShow(EditorLayer*) {}        
        virtual void OnShowAsset(EditorLayer*) {}        
        virtual void SetTitle(const char*) {}

        // Ref<AssetID> m_SelectedAsset;
    };

    using Widget = Scope<IWidget>;
}