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
#include "ballista.hpp"

#include "Ballista/src/utilities/physics.hpp"
#include "Ballista/src/entities/ballistaframepart.hpp"
#include "Ballista/src/entities/ballistawheel.hpp"

#include <iostream>

Ballista::Ballista(const BallistaAssetConfig &config, AssetLoader<Texture> &textureLoader, float spriteScale)
    : config(config), textureLoader(textureLoader), scale(spriteScale)
{
    textureIds[BallistaPart::Chassis] = textureLoader.AddAsset(config.chassisTexturePath);
    textureIds[BallistaPart::BackWheel] = textureLoader.AddAsset(config.backwheelTexturePath);
    textureIds[BallistaPart::FrontWheel] = textureLoader.AddAsset(config.frontwheelTexturePath);
    textureIds[BallistaPart::Bow] = textureLoader.AddAsset(config.bowTexturePath);
    textureIds[BallistaPart::ArrowPart] = textureLoader.AddAsset(config.arrowTexturePath);

    int chassisWidth = textureLoader.GetAsset(textureIds[BallistaPart::Chassis])->GetWidth() * scale;
    chassisHeight = textureLoader.GetAsset(textureIds[BallistaPart::Chassis])->GetHeight() * scale;
    glm::vec2 pos(0.f, chassisHeight);
    const Sprite chassisSprite(textureLoader.GetAsset(textureIds[BallistaPart::Chassis]), chassisWidth, chassisHeight);
    partIds[BallistaPart::Chassis] = AddObject(std::make_unique<BallistaFramePart>(chassisSprite, pos));

    int backWheelWidth = textureLoader.GetAsset(textureIds[BallistaPart::BackWheel])->GetWidth() * scale;
    int backWheelHeight = textureLoader.GetAsset(textureIds[BallistaPart::BackWheel])->GetHeight() * scale;
    pos = {chassisHeight * 0.3f * scale, 2.4f * backWheelHeight + chassisHeight};
    const Sprite backWheelSprite(textureLoader.GetAsset(textureIds[BallistaPart::BackWheel]), backWheelWidth, backWheelHeight);
    partIds[BallistaPart::BackWheel] = AddObject(std::make_unique<BallistaWheel>(backWheelSprite, pos));

    int frontWheelWidth = textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel])->GetWidth() * scale;
    int frontWheelHeight = textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel])->GetHeight() * scale;
    pos = {chassisWidth * 0.75f - frontWheelWidth, frontWheelHeight * 1.4f + chassisHeight};
    const Sprite frontWheelSprite(textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel]), frontWheelWidth, frontWheelHeight);
    partIds[BallistaPart::FrontWheel] = AddObject(std::make_unique<BallistaWheel>(frontWheelSprite, pos));

    bowWidth = textureLoader.GetAsset(textureIds[BallistaPart::Bow])->GetWidth() * scale;
    bowHeight = textureLoader.GetAsset(textureIds[BallistaPart::Bow])->GetHeight() * scale;
    pos = {chassisHeight * 0.1f, bowHeight * 1.3f};
    const Sprite bowSprite(textureLoader.GetAsset(textureIds[BallistaPart::Bow]), bowWidth, bowHeight);
    partIds[BallistaPart::Bow] = AddObject(std::make_unique<BallistaFramePart>(bowSprite, pos));

    arrowWidth = textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart])->GetWidth() * scale;
    arrowHeight = textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart])->GetHeight() * scale;
    glm::vec2 arrowPosition = {chassisHeight * 0.1f + (bowWidth - arrowWidth) / 2.0f, arrowHeight * 2.f + bowHeight};
    const Sprite arrowSprite(textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart]), arrowWidth, arrowHeight);
    partIds[BallistaPart::ArrowPart] = AddObject(std::make_unique<Arrow>(arrowSprite, arrowPosition));

    maxLaunchSpeed *= GetSize() / 2.0f;
}

void Ballista::Init(float groundLevel)
{
    SetPosition({0.f, groundLevel - (size + chassisHeight / 1.5f) * scale});
}

void Ballista::ReloadArrow()
{
    if (!arrowLaunched)
        return;
    glm::vec2 arrowPosition = {chassisHeight * 0.1f + (bowWidth - arrowWidth) / 2.0f, arrowHeight * 2.f + bowHeight};
    const float orientation = GetObject(partIds[BallistaPart::Bow])->GetOrientation();
    const Sprite arrowSprite(textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart]), arrowWidth, arrowHeight, orientation);
    partIds[BallistaPart::ArrowPart] = AddObject(std::make_unique<Arrow>(arrowSprite, GetPosition() + arrowPosition));
    const float rotSpeed = GetObject(partIds[BallistaPart::Bow])->GetRotationSpeed();
    GetObject(partIds[BallistaPart::ArrowPart])->SetVelocity(GetVelocity());
    GetObject(partIds[BallistaPart::ArrowPart])->SetRotationSpeed(rotSpeed);
    arrowLaunched = false;
}

void Ballista::SetRotationSpeed(float angSpeed)
{
    GetObject(partIds[BallistaPart::Bow])->SetRotationSpeed(angSpeed);
    if (!arrowLaunched)
        GetObject(partIds[BallistaPart::ArrowPart])->SetRotationSpeed(angSpeed);
}

void Ballista::SetLaunchOrientation(float orientation)
{
    GetObject(partIds[BallistaPart::Bow])->Rotate(orientation);
    if (!arrowLaunched)
        GetObject(partIds[BallistaPart::ArrowPart])->Rotate(orientation);
}

std::unique_ptr<Arrow> Ballista::ShootArrow(float strength)
{
    if (arrowLaunched)
        return nullptr;
    arrowLaunched = true;
    std::unique_ptr<Arrow> arrow(static_cast<Arrow *>(ReleaseObject(partIds[BallistaPart::ArrowPart]).release()));
    arrow->AddVelocity(speedToVelocity(maxLaunchSpeed * strength, arrow->GetOrientation()));
    return arrow;
}