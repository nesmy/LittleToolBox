#pragma once

#include "Config.h"
#include "Data.h"
#include "Scripts/Utilities.h"

namespace LTB {    

    //asset type

    enum class AssetType : uint8_t{

        UNKNOWN = 0,
        TEXTURE,
        SCENE,
        MODEL,
        SPRTIE,
        SCRIPT,
    };

     // define the base Asset structure
    struct Asset {        
        // generate unique asset id
        AssetID UID = EMPTY_ASSET; 

        // file path of asset
        std::string Source;       

        // name of the asset
        std::string Name; 
        
        // asset type
        AssetType Type;
    };

    struct TextureAsset : Asset{
        Texture2D Data;
    };

    struct ModelAsset : Asset {
        Model Data;
    };

    struct SpriteAsset : Asset {
        Sprite Data;
    };

    struct SceneAsset : Asset {
        // to do
    };

    struct ScriptAsset : Asset {
        //to do
    };

    // define an unordered map to store assets based on their type and UID
    using SharedAsset = Ref<Asset>;
    using AssetMap = std::unordered_map<AssetID, SharedAsset>;

    // asset registry to manage the addition and retrieval of assets
    struct AssetRegistry {
        inline AssetRegistry(){
            // add default asset for each type
            AddEmpty<TextureAsset>();
            AddEmpty<SceneAsset>();
        }

        inline auto AddTexture(AssetID uid, const std::string& source)
        {
            auto asset = CreateRef<TextureAsset>();
            asset->Data = LoadTexture(source.c_str());
            asset->Type = AssetType::TEXTURE;
            Add(uid, source, asset);
            return asset;
        }

        inline auto AddScene(AssetID uid, const std::string& source)
        {
            auto asset = CreateRef<SceneAsset>();
            asset->Type = AssetType::SCENE;
            Add(uid, source, asset);
            return asset;
        }

        inline auto AddModel(AssetID uid, const std::string& source)
        {
            auto asset = CreateRef<ModelAsset>();
            asset->Data = LoadModel(source.c_str());
            asset->Type = AssetType::MODEL;
            Add(uid, source, asset);
            return asset;
        }

        inline auto AddSprite(AssetID uid, const std::string& source)
        {
            auto asset = CreateRef<SpriteAsset>();
            asset->Data.Texture = LoadTexture(source.c_str());
            asset->Type = AssetType::SPRTIE;
            Add(uid, source, asset);
            return asset;
        }

        inline auto AddScript(AssetID uid, const std::string& source)
        {
            auto asset = CreateRef<ScriptAsset>();        
            asset->Type = AssetType::SCRIPT;
            Add(uid, source, asset);
            return asset;
        }

        // retrieve asset based on its uid
        template <typename T>
        inline T& Get(AssetID uid)
        {
            const uint32_t type = TypeID<T>();
            if (mRegistry[type].count(uid))
                return (T&)(*mRegistry[type][uid]);            
            return (T&)(*mRegistry[type][EMPTY_ASSET]);
        }

        // helps loop through all assets
        template <typename F>
        inline void View(F&& func)
        {
            for(auto& [_, assetMap] : mRegistry)
            {                
                for(auto& [uid, asset] : assetMap)
                {
                    if(uid != EMPTY_ASSET)
                    {
                        func(asset.get());                                        
                    }
                }
            }
        }

        // return collection of asset
        template <typename T>
        inline auto& GetMap()
        {
            return mRegistry[TypeID<T>()];
        }

        inline void Clear()
        {
            mRegistry.clear();
        }

    private:
        // adds a new asset to the registry
        template <typename T>
        inline void Add(
            AssetID uid, 
            const std::string& source, 
            Ref<T>& asset
        )
        {            
            asset->UID = uid;
            asset->Source = source;
            std::filesystem::path path(source);
            asset->Name = path.stem().string();
            mRegistry[TypeID<T>()][asset->UID] = asset;
        }

        template <typename T>        
        inline void AddEmpty()
        {
            mRegistry[TypeID<T>()][EMPTY_ASSET] = CreateRef<T>();
        }
    private:
        std::unordered_map<uint32_t, AssetMap> mRegistry; 
    };
}