// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Ballista.
//
// Ballista is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Ballista is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Ballista.  If not, see <http://www.gnu.org/licenses/>.
#pragma once

#include "DynamoEngine/src/entities/compositegameobject.hpp"
#include "DynamoEngine/src/assets/assetloader.hpp"

#include "Ballista/src/entities/arrow.hpp"

#include <map>

enum BallistaPart
{
    BackWheel,
    FrontWheel,
    Bow,
    Chassis,
    ArrowPart,
};

struct BallistaAssetConfig
{
    std::string chassisTexturePath;
    std::string backwheelTexturePath;
    std::string frontwheelTexturePath;
    std::string bowTexturePath;
    std::string arrowTexturePath;
};

class Ballista : public CompositeGameObject
{
public:
    Ballista(const BallistaAssetConfig &config, AssetLoader<Texture> &textureLoader, float spriteScale = 0.3f);
    ~Ballista() = default;

    void Init(float groundLevel);

    float GetSize() const { return scale * size; }
    float GetScale() const { return scale; }

    void ReloadArrow();
    void SetRotationSpeed(float angSpeed);
    void SetLaunchOrientation(float orientation);
    std::unique_ptr<Arrow> ShootArrow(float strength);

    bool ArrowIsLaunched() { return arrowLaunched; }

private:
    BallistaAssetConfig config{};
    AssetLoader<Texture> &textureLoader;
    std::map<BallistaPart, int> textureIds{};

    bool arrowLaunched = false;
    float maxLaunchSpeed = 15.0f;

    std::map<BallistaPart, int> partIds{};
    float scale{};
    // Height of the ballista sprite in pixels
    int size = 764;
    int chassisHeight{};
    int bowHeight{};
    int bowWidth{};
    int arrowWidth{};
    int arrowHeight{};
};