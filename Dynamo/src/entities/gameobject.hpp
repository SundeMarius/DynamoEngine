// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Dynamo.
//
// Dynamo is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Dynamo is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Dynamo.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Dynamo/src/utilities/uuid.hpp"
#include "Dynamo/src/core/timestep.hpp"
#include "Dynamo/src/core/sprite.hpp"

#include <glm/glm.hpp>

#include <memory>

class GameObject
{
public:
    GameObject() = default;
    GameObject(glm::vec2 position, Sprite *sprite) : sprite(sprite), pos(position) {}
    virtual ~GameObject() = default;

    virtual void Update(const Timestep &dt) = 0;

    const UUID &id() const { return objectId; }

    void SetVelocity(const glm::vec2 &velocity) { vel = velocity; }
    void SetPosition(const glm::vec2 &newPosition) { sprite->SetPosition(pos = newPosition); }

    glm::vec2 GetPosition() const { return pos; }
    glm::vec2 GetVelocity() const { return vel; }

    // Rotate sprite
    void Rotate(float angle);
    // Change velocity direction
    void SetHeading(float angle);

    void Render();

protected:
    UUID objectId{};
    Sprite *sprite = nullptr;

    glm::vec2 pos{0.f};
    glm::vec2 vel{0.f};
};