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

#include <glm/glm.hpp>

class GameObject
{
public:
    GameObject();
    GameObject(glm::vec2 position, glm::vec2 velocity) : position(position), velocity(velocity) {}
    virtual ~GameObject() = default;

    virtual void Update(const Timestep &dt) = 0;
    virtual void Display() = 0;

    const UUID &id() const { return objectId; }

private:
    UUID objectId{};
    glm::vec2 position{};
    glm::vec2 velocity{};
};