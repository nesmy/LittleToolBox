#pragma once

#include "Config.h"
#include "Data.h"

namespace LTB {

    // common component
    struct InfoComponent{
        inline InfoComponent(const InfoComponent&) = default;
        inline InfoComponent() = default;
        std::string Name = "Entity";
    };

    // transform component
    struct TransformComponent {
        inline TransformComponent(const TransformComponent&) = default;
        inline TransformComponent() = default; 
        Transform Transforms;
    };

    // camera component
    struct CameraComponent {
        inline CameraComponent(const CameraComponent&) = default;
        inline CameraComponent() = default; 
        Camera3D Camera; 
    };

    // camera2D component
    struct Camera2DComponent
    {
        inline Camera2DComponent(const Camera2DComponent&) = default;
        inline Camera2DComponent() = default;
	    Camera2D Camera;
    };

    // model component
    struct ModelComponent 
    { 
        inline ModelComponent(const ModelComponent&) = default;
        inline ModelComponent() = default; 
        Model mModel;
    };

    // sprite component
    struct SpriteComponent {
        inline SpriteComponent(const SpriteComponent&) = default;
        inline SpriteComponent() = default; 
        Sprite mSprite;
    };

    // base entity
    struct Entity 
    {
        inline Entity(EntityRegistry* registry, EntityID entity): 
            m_Registry(registry), m_EnttID(entity) 
        {}
        
        inline Entity(EntityRegistry* registry): 
        m_Registry(registry) 
        {
            m_EnttID = m_Registry->create();		 			
        }

        inline virtual ~Entity() = default;
        inline Entity() = default;		

        inline operator EntityID () 
        { 
            return m_EnttID; 
        }

        inline operator bool()  
        { 
            return m_Registry != nullptr && 
            m_Registry->valid(m_EnttID);
        }       

        inline EntityID ID() 
        { 
            return m_EnttID; 
        }
        
        // ++

        template<typename T, typename... Args>
        inline T& Attach(Args&&... args) 
        {
            return m_Registry->get_or_emplace<T>
            (m_EnttID, std::forward<Args>(args)...);
        }

        template<typename T>
        inline void Detach() 
        { 
            m_Registry->remove<T>(m_EnttID); 
        }

        inline void Destroy() 
        {
            if(m_Registry) 
            { 
                m_Registry->destroy(m_EnttID); 
            }
        }

        template<typename T>
        inline bool Has()  
        { 
            return m_Registry != nullptr && 
            m_Registry->all_of<T>(m_EnttID); 
        }

        template<typename T>
        inline T& Get() 
        { 
            return m_Registry->get<T>(m_EnttID); 
        }

    protected:
        EntityRegistry* m_Registry = nullptr;
        EntityID m_EnttID = NENTT;
    };
}