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

#include "Lib/src/entities/gameobject.hpp"
#include "Lib/src/core/resourceloader.hpp"
#include "Lib/src/core/texture.hpp"

#include <SDL2/SDL.h>

#include <vector>
#include <memory>
#include <algorithm>

using GameObjectPtr = std::unique_ptr<GameObject>;
using GameObjectContainer = std::vector<GameObjectPtr>;

class Scene
{
public:
    Scene(ResourceSpecification &rSpec) : resources(std::make_unique<ResourceLoader>(rSpec)) {}

    void AddObject(GameObjectPtr object)
    {
        objects.emplace_back(std::move(object));
    }
    void RemoveObject(GameObjectPtr object)
    {
        std::erase(objects, object);
    }
    const GameObjectContainer &GetGameObjects()
    {
        return objects;
    }

    void Render();

    std::unique_ptr<ResourceLoader> &Resources() { return resources; }

private:
    GameObjectPtr player;
    GameObjectContainer objects;

    std::unique_ptr<ResourceLoader> resources;
};