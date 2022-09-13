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
#include "gamescreen.hpp"

#include "DynamoEngine/src/core/text.hpp"

bool GameScreen::Init()
{
    assetIds[GameResource::Background] = textureLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_2/game_background_2.png");
    assetIds[GameResource::Ground] = textureLoader.AddAsset("assets/images/ground/grass_block.png");

    log.Trace("Main game screen initializing...");
    int width = window.GetWidth();
    int height = window.GetHeight();
    groundLevel = height - height / 10;
    AddBackground(GameResource::Background, {0, 0}, width, height);
    AddBackground(GameResource::Ground, {0, groundLevel}, width, height / 10);
    playerScale = 0.2f;
    player = std::make_unique<Ballista>(window, 0.2f);
    player->Init(groundLevel);
    gravity = {0.f, physics::constants::accelerationDueToGravity * playerScale * player->GetSize() / 2.0f};
    log.Trace("Main game screen initialized!");
    return true;
}

void GameScreen::Activate()
{
    currentSeconds = 0.f;
}

void GameScreen::ProcessInput(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_KEYDOWN:
        if (event->key.keysym.sym == SDLK_RIGHT)
        {
            player->SetVelocity({1000.f * playerScale, 0.f});
        }
        else if (event->key.keysym.sym == SDLK_LEFT)
        {
            player->SetVelocity({-1000.f * playerScale, 0.f});
        }

        if (event->key.keysym.sym == SDLK_UP)
        {
            player->SetRotationSpeed(-1.5f);
        }
        else if (event->key.keysym.sym == SDLK_DOWN)
        {
            player->SetRotationSpeed(1.5f);
        }

        if (event->key.keysym.sym == SDLK_SPACE)
        {
            player->ShootArrow(1.0f);
        }
        break;
    case SDL_KEYUP:
        player->SetVelocity({0.f, 0.f});
        player->SetRotationSpeed(0.f);
        break;
    default:
        break;
    }
}

void GameScreen::Update(const Timestep &dt)
{
    currentSeconds += dt.GetSeconds();
    player->Update(dt);
    if (player->GetArrow()->TouchDown(groundLevel))
    {
        player->GetArrow()->SetVelocity({0.f, 0.f});
    }
    else if (player->ArrowIsLaunched())
    {
        player->GetArrow()->AddVelocity(gravity * dt.GetSeconds());
    }
}

void GameScreen::Render()
{
    backgrounds[GameResource::Background].Render();
    backgrounds[GameResource::Ground].Render();
    player->Render();
    // ... ///
}

void GameScreen::AddText(GameResource type, SDL_Point position, int width, int height, SDL_Color color)
{
    auto font = fontLoader.GetAsset(assetIds[type]);
    TextSpecification textSpec = {
        color,
        font,
        {float(position.x), float(position.y), float(width), float(height)},
    };
    texts.try_emplace(type, window, " ", textSpec);
}

void GameScreen::AddBackground(GameResource type, SDL_Point position, int width, int height)
{
    auto texture = textureLoader.GetAsset(assetIds[type]);
    backgrounds.try_emplace(type, texture, position, width, height);
}

void GameScreen::AddSprite(GameResource type, int width, int height)
{
    auto texture = textureLoader.GetAsset(assetIds[type]);
    sprites.try_emplace(type, texture, width, height);
}