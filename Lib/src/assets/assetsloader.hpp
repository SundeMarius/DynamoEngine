// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of CannonLaunch.
//
// CannonLaunch is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// CannonLaunch is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with CannonLaunch.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Lib/src/assets/asset.hpp"

#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class AssetsLoader
{
    using AssetId = int;

public:
    AssetId AddAsset(const std::string &filePath)
    {
        auto assetIterator = assets.find(filePath);
        if (assetIterator != assets.end())
            return assetIterator->second.id;

        auto asset = std::make_shared<T>();
        if (!asset->LoadFromFile(filePath))
            throw AssetInitializationError("Could not load asset file at " + filePath);

        assets.insert({filePath, {currentId, asset}});
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
        for (const auto &[filePath, assetElement] : assets)
        {
            if (assetElement.id == id)
            {
                return assetElement.asset;
            }
        }
        return nullptr;
    }

private:
    struct AssetElement
    {
        int id;
        std::shared_ptr<T> asset;
    };
    AssetId currentId = 0;
    std::unordered_map<std::string, AssetElement> assets{};
};