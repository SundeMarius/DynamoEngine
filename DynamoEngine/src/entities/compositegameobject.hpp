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

#include "DynamoEngine/src/core/timestep.hpp"
#include "DynamoEngine/src/entities/gameobject.hpp"

#include <glm/glm.hpp>

#include <memory>
#include <map>

class CompositeGameObject : public GameObject
{
public:
    virtual ~CompositeGameObject() = default;

    int AddObject(std::unique_ptr<GameObject> object);
    void RemoveObject(int objectId);
    GameObject *GetObject(int objectId);
    std::unique_ptr<GameObject> ReleaseObject(int objectId);

    void SetPosition(const glm::vec2 &position) override;
    void AddPosition(const glm::vec2 &displacement) override;
    void SetVelocity(const glm::vec2 &velocity) override;
    void AddVelocity(const glm::vec2 &velocity) override;
    void Rotate(float angle) override;

    void Render();

    void Update(const Timestep &dt) override;

protected:
    std::map<int, std::unique_ptr<GameObject>> objects{};
    int objectId = 0;
};