// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Lib.
//
// Lib is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Lib is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Lib.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "Lib/src/utilities/uuid.hpp"
#include "Lib/src/core/timestep.hpp"
#include "Lib/src/core/sprite.hpp"

#include <glm/glm.hpp>

#include <memory>

class GameObject
{
public:
    GameObject();
    GameObject(glm::vec2 position, glm::vec2 velocity) : pos(position), vel(velocity) {}
    virtual ~GameObject() = default;

    void SetVelocity(glm::vec2 velocity) { vel = velocity; }
    void SetOrientation(float angle) {}

    virtual void Update(const Timestep &dt) = 0;
    virtual void Render() = 0;

    const UUID &id() const { return objectId; }

private:
    UUID objectId{};

    glm::vec2 pos{};
    glm::vec2 vel{};
};