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
#include "DynamoEngine/src/entities/sprite.hpp"

#include <glm/glm.hpp>

class GameObject
{
public:
    GameObject() = default;
    GameObject(const Sprite &sprite, glm::vec2 position) : sprite(sprite), pos(position) {}
    virtual ~GameObject() = default;

    virtual void SetPosition(const glm::vec2 &position) { pos = position; }
    virtual void AddPosition(const glm::vec2 &displacement) { pos += displacement; }
    virtual void SetOrientation(float angle) { sprite.SetOrientation(angle); }
    virtual void Rotate(float angle) { sprite.Rotate(angle); }
    virtual void SetRotationSpeed(float rotSpeed) { angSpeed = rotSpeed; }
    virtual void AddRotationSpeed(float rotSpeed) { angSpeed += rotSpeed; }
    virtual void SetVelocity(const glm::vec2 &velocity) { vel = velocity; }
    virtual void AddVelocity(const glm::vec2 &velocity) { vel += velocity; }

    float GetRotationSpeed() const { return angSpeed; }
    float GetOrientation() const { return sprite.GetOrientation(); }
    const glm::vec2 GetPosition() const { return pos; }
    const glm::vec2 GetVelocity() const { return vel; }

    Sprite *GetSprite() { return &sprite; }

    void Render() const;
    virtual void Update(const Timestep &dt) = 0;

protected:
    Sprite sprite{};
    glm::vec2 pos{0.f};
    glm::vec2 vel{0.f};
    float angSpeed{0.f};
};