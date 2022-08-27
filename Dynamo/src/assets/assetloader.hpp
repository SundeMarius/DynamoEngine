// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo Engine.
//
// Dynamo Engine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dynamo Engine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dynamo Engine.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Dynamo/src/assets/asset.hpp"
#include "Dynamo/src/log/log.hpp"

#include <string>
#include <memory>
#include <unordered_map>

template <typename T>
class AssetLoader
{
    using AssetId = int;

public:
    AssetLoader(Log &log) : log(log) {}

    AssetId AddAsset(const std::string &filePath)
    {
        auto assetIterator = assets.find(filePath);
        if (assetIterator != assets.end())
            return assetIterator->second.id;

        log.Trace("Loading asset from " + filePath);
        auto as = std::make_unique<T>();
        if (!as->LoadFromFile(filePath))
            throw AssetInitializationError("Could not load asset file at " + filePath);
        log.Success("Loaded asset successfully");

        assets[filePath] = {
            .id = currentId,
            .asset = std::move(as),
        };
        return currentId++;
    }
    void RemoveAsset(AssetId id)
    {
        for (const auto &[filePath, assetElement] : assets)
        {
            if (assetElement.id == id)
            {
                assets.erase(filePath);
                log.Trace("Removed asset from " + filePath);
                return;
            }
        }
    }
    T *GetAsset(AssetId id)
    {
        for (const auto &[filePath, assetElement] : assets)
        {
            if (assetElement.id == id)
            {
                return assetElement.asset.get();
            }
        }
        return nullptr;
    }

private:
    Log &log;

    struct AssetElement
    {
        int id = 0;
        std::unique_ptr<T> asset{};
    };
    AssetId currentId = 0;
    std::unordered_map<std::string, AssetElement> assets{};
};