#pragma once

#include "Config.h"

namespace LTB {

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