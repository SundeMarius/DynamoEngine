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
#include "ballista.hpp"

#include "Ballista/src/utilities/physics.hpp"
#include "Ballista/src/entities/ballistaframepart.hpp"
#include "Ballista/src/entities/ballistawheel.hpp"

#include <iostream>

Ballista::Ballista(Window &window, float spriteScale)
    : textureLoader(window), scale(spriteScale)
{
    textureIds[BallistaPart::Chassis] = textureLoader.AddAsset("assets/sprites/ballista/pieces/chassis.png");
    textureIds[BallistaPart::BackWheel] = textureLoader.AddAsset("assets/sprites/ballista/pieces/backwheel.png");
    textureIds[BallistaPart::FrontWheel] = textureLoader.AddAsset("assets/sprites/ballista/pieces/front-wheel.png");
    textureIds[BallistaPart::Bow] = textureLoader.AddAsset("assets/sprites/ballista/pieces/bow.png");
    textureIds[BallistaPart::ArrowPart] = textureLoader.AddAsset("assets/sprites/ballista/pieces/spear.png");

    int swChassis = textureLoader.GetAsset(textureIds[BallistaPart::Chassis])->GetWidth() * scale;
    shChassis = textureLoader.GetAsset(textureIds[BallistaPart::Chassis])->GetHeight() * scale;
    glm::vec2 pos(0.f, shChassis);
    const Sprite chassisSprite(textureLoader.GetAsset(textureIds[BallistaPart::Chassis]), swChassis, shChassis);
    partIds[BallistaPart::Chassis] = AddObject(new BallistaFramePart(chassisSprite, pos));

    int swBackWheel = textureLoader.GetAsset(textureIds[BallistaPart::BackWheel])->GetWidth() * scale;
    int shBackWheel = textureLoader.GetAsset(textureIds[BallistaPart::BackWheel])->GetHeight() * scale;
    pos = {shChassis * 0.3f * scale, 2.4f * shBackWheel + shChassis};
    const Sprite backWheelSprite(textureLoader.GetAsset(textureIds[BallistaPart::BackWheel]), swBackWheel, shBackWheel);
    partIds[BallistaPart::BackWheel] = AddObject(new BallistaWheel(backWheelSprite, pos));

    int swFrontWheel = textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel])->GetWidth() * scale;
    int shFrontWheel = textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel])->GetHeight() * scale;
    pos = {swChassis * 0.75f - swFrontWheel, shFrontWheel * 1.4f + shChassis};
    const Sprite frontWheelSprite(textureLoader.GetAsset(textureIds[BallistaPart::FrontWheel]), swFrontWheel, shFrontWheel);
    partIds[BallistaPart::FrontWheel] = AddObject(new BallistaWheel(frontWheelSprite, pos));

    swBow = textureLoader.GetAsset(textureIds[BallistaPart::Bow])->GetWidth() * scale;
    shBow = textureLoader.GetAsset(textureIds[BallistaPart::Bow])->GetHeight() * scale;
    pos = {shChassis * 0.1f, shBow * 1.3f};
    const Sprite bowSprite(textureLoader.GetAsset(textureIds[BallistaPart::Bow]), swBow, shBow);
    partIds[BallistaPart::Bow] = AddObject(new BallistaFramePart(bowSprite, pos));

    swArrow = textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart])->GetWidth() * scale;
    shArrow = textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart])->GetHeight() * scale;
    pos = {shChassis * 0.1f + (swBow - swArrow) / 2.0f, shArrow * 2.f + shBow};
    const Sprite arrowSprite(textureLoader.GetAsset(textureIds[BallistaPart::ArrowPart]), swArrow, shArrow);
    partIds[BallistaPart::ArrowPart] = AddObject(new Arrow(arrowSprite, pos));

    maxLaunchSpeed *= size * scale / 2.0f;
}

void Ballista::Init(float groundLevel)
{
    glm::vec2 displacement = {0.f, groundLevel - (size + shChassis / 1.5f) * scale};
    SetPosition(displacement);
}

/* void Ballista::InitArrow()
{
    arrow = Arrow(sprites.GetPart(partIds[BallistaPart::ArrowPart]));
    arrow.Move(pos);
    arrow.Rotate(orientation);
} */

void Ballista::SetRotationSpeed(float angSpeed)
{
    GetObject(partIds[BallistaPart::Bow])->SetRotationSpeed(angSpeed);
    GetObject(partIds[BallistaPart::ArrowPart])->SetRotationSpeed(angSpeed);
}

void Ballista::SetVelocity(const glm::vec2 &velocity)
{
    GetObject(partIds[BallistaPart::BackWheel])->SetVelocity(velocity);
    GetObject(partIds[BallistaPart::FrontWheel])->SetVelocity(velocity);
    GetObject(partIds[BallistaPart::Bow])->SetVelocity(velocity);
    GetObject(partIds[BallistaPart::Chassis])->SetVelocity(velocity);
    if (!GetArrow()->IsFreeFalling())
    {
        GetObject(partIds[BallistaPart::ArrowPart])->SetVelocity(velocity);
    }
}

void Ballista::ShootArrow(float strength)
{
    auto arrow = GetArrow();
    if (arrow->IsFreeFalling())
        return;
    arrow->SetVelocity(speedToVelocity(maxLaunchSpeed * strength, arrow->GetOrientation()));
    arrow->ActivateFreeFall();
}

// void Ballista::Update(const Timestep &dt)
// {
//     const float dts = dt.GetSeconds();
//     /*     if (arrowLaunched && !arrow.TouchDown(groundLvl))
//             arrow.GetVelocity() += arrowAcceleration * dts; */
//     AddPosition(vel * dts);
//     GetObject(partIds[BallistaPart::Bow])->Rotate(rotSpeed * dts);
//     GetObject(partIds[BallistaPart::ArrowPart])->Rotate(rotSpeed * dts);
// }