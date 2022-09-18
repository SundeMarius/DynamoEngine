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

    int width = window.GetWidth();
    int height = window.GetHeight();
    groundLevel = height - height / 10;
    player = std::make_unique<Ballista>(window, 0.10f);
    player->Init(groundLevel);
    player->SetLaunchOrientation(-math::constants::pi / 4.0f);
    AddBackground(GameResource::Background, {0, 0}, width, height);
    AddBackground(GameResource::Ground, {0, groundLevel}, width, height / 10);
    gravity = {0.f, physics::constants::accelerationDueToGravity * player->GetSize() / 2.0f};
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
            player->SetVelocity({1000.f * player->GetScale(), 0.f});
        }
        else if (event->key.keysym.sym == SDLK_LEFT)
        {
            player->SetVelocity({-1000.f * player->GetScale(), 0.f});
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
            Arrow *currentArrow = player->ShootArrow(1.0f);
            if (currentArrow)
                arrow.reset(currentArrow);
        }
        if (event->key.keysym.sym == SDLK_ESCAPE)
        {
            pauseGame = !pauseGame;
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
    if (pauseGame)
        return;
    currentSeconds += dt.GetSeconds();
    player->Update(dt);
    if (arrow)
    {
        if (arrow->TouchDown(groundLevel))
        {
            arrow->SetVelocity({0.f, 0.f});
            arrow->DeactivateFreeFall();
            player->ReloadArrow();
        }
        else
        {
            arrow->AddVelocity(gravity * dt.GetSeconds());
        }
        arrow->Update(dt);
    }
}

void GameScreen::Render()
{
    backgrounds[GameResource::Background].Render();
    backgrounds[GameResource::Ground].Render();
    player->Render();
    if (arrow)
        arrow->Render();
}

void GameScreen::AddText(GameResource type, SDL_Point position, int width, int height, SDL_Color color)
{
    auto font = fontLoader.GetAsset(assetIds[type]);
    TextSpecification textSpec = {
        font,
        color,
        {float(position.x), float(position.y), float(width), float(height)},
    };
    texts.try_emplace(type, window, " ", textSpec);
}

void GameScreen::AddBackground(GameResource type, SDL_Point position, int width, int height)
{
    auto texture = textureLoader.GetAsset(assetIds[type]);
    backgrounds.try_emplace(type, texture, position, width, height);
}