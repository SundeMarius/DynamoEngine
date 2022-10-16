// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine.
//
// DynamoEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/assets/asset.hpp"
#include "DynamoEngine/src/log/log.hpp"

#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class AssetLoader
{
    using AssetId = int;

public:
    AssetLoader(Window &window) : window(window) {}

    AssetId AddAsset(const std::string &filePath)
    {
        auto [it, inserted] = assets.try_emplace(filePath);
        if (!inserted)
            return it->second.id;
        it->second.asset->LoadFromFile(window, filePath);
        it->second.id = currentId;
        return currentId++;
    }
    void RemoveAsset(AssetId id)
    {
        for (const auto &[filePath, assetElement] : assets)
        {
            if (assetElement.id == id)
            {
                assets.erase(filePath);
                return;
            }
        }
    }
    std::shared_ptr<T> GetAsset(AssetId id)
    {
        for (auto &[filePath, assetElement] : assets)
        {
            if (assetElement.id == id)
            {
                return assetElement.asset;
            }
        }
        return nullptr;
    }

private:
    Window &window;

    struct AssetElement
    {
        int id = 0;
        std::shared_ptr<T> asset = std::make_shared<T>();
    };
    std::unordered_map<std::string, AssetElement> assets{};
    AssetId currentId = 0;
};