#pragma once

#include "config.h"
#include "UUID.h"

namespace LTB {

    struct Entity;

    class Scene{
    public:
        Scene();
        ~Scene();

        static Ref<Scene> Copy(Ref<Scene> other);

        Entity CreateEntity(const std::string& name = std::string());
        Entity CreateEntityWithUUID(UUID uuid, const std::string& name = std::string());
        void DestroyEntity(Entity entity);

        void OnRuntimeStart();
        void OnRuntimeStop();
        void OnUpdateRuntime(float deltaTime);

        void OnUpdateEditor(float deltaTime);

        void DuplicateEntity(Entity entity);        

        void GlobalCam();
        void EndCam();

        void SwitchCam();

    public:
         // create entity
        template <typename Entt, typename... Args>
        inline Entt CreateEntt(Args&&... args)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&mRegistry, std::forward<Args>(args)...));
        }

        // convert id to entity
        template<typename Entt>
        inline Entt ToEntt(EntityID entity)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            return std::move(Entt(&mRegistry, entity));
        }

        // loop through entities with component
        template<typename Entt, typename Comp, typename Task>
        inline void EnttView(Task&& task)
        {
            // GEN_STATIC_ASSERT(std::is_base_of<Entity, Entt>::value);
            mRegistry.view<Comp>().each([this, &task]
            (auto entity, auto& comp)
            {
                task(std::move(Entt(&mRegistry, entity)), comp);
            });
        }

        template<typename Entt, typename Task>
        inline void AllEntt(Task&& task){
            mRegistry.each([this, &task]
            (auto entity)
            {
                task(std::move(Entt(&mRegistry, entity)));
            });
        }

    public:       
        Camera3D &GetCam() { return mGlobalCam;}
        Camera2D &GetCam2D() { return mGlobalCam2D;}
        bool &Is2D() { return Switch2d;}  
        void BlockUpdate(bool update);      
    private:
        EntityRegistry mRegistry;        
        Camera3D mGlobalCam = {0};
        Camera2D mGlobalCam2D = {0};
        Ray ray = {0};
        bool Switch2d;
        bool StopUpdate;
        friend struct Entity;
        friend class SceneSerializer;
    };
}