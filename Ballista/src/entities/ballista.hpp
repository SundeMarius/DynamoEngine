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

#include "DynamoEngine/src/entities/compositegameobject.hpp"
#include "DynamoEngine/src/assets/assetloader.hpp"

#include "Ballista/src/entities/arrow.hpp"
#include "Ballista/src/utilities/physics.hpp"

#include <map>

enum BallistaPart
{
    BackWheel,
    FrontWheel,
    Bow,
    Chassis,
    ArrowPart,
};

class Ballista : public CompositeGameObject
{
public:
    Ballista(Window &window, float spriteScale = 0.3f);
    ~Ballista() = default;

    void Init(float groundLevel);

    void SetRotationSpeed(float angSpeed);
    void SetVelocity(const glm::vec2 &velocity) override;

    float GetSize() const { return size; }
    Arrow *GetArrow() { return (Arrow *)GetObject(partIds[BallistaPart::ArrowPart]); }

    void ShootArrow(float strength);

    bool ArrowIsLaunched() { return GetArrow()->IsFreeFalling(); }

private:
    AssetLoader<Texture> textureLoader;
    std::map<BallistaPart, int> textureIds{};

    // Height of the ballista sprite in pixels
    float size = 764;
    float scale{0.3f};
    std::map<BallistaPart, int> partIds{};

    float maxLaunchSpeed = 20.0f;

    int shChassis{0};
    int shBow{0};
    int swBow{0};
    int swArrow{0};
    int shArrow{0};
};