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
#include "Ballista/src/scenes/gamescreen.hpp"

#include "Ballista/src/utilities/events.hpp"

#include "DynamoEngine/src/core/text.hpp"

bool GameScreen::Init()
{
    assetIds[GameResource::Background] = textureLoader.AddAsset(config.backgroundPath);
    assetIds[GameResource::Ground] = textureLoader.AddAsset(config.grassPath);

    int width = window.GetWidth();
    int height = window.GetHeight();
    groundLevel = height - height / 10;
    AddBackground(GameResource::Background, {0, 0}, width, height);
    AddBackground(GameResource::Ground, {0, groundLevel}, width, height / 10);

    player = std::make_unique<Ballista>(config.playerConfig, textureLoader, 0.15f);
    player->Init(groundLevel);
    player->SetLaunchOrientation(-math::constants::pi / 4.0f);
    gravity *= player->GetSize() / 2.f;
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
        else if (event->key.keysym.sym == SDLK_UP)
        {
            player->SetRotationSpeed(-1.5f);
        }
        else if (event->key.keysym.sym == SDLK_DOWN)
        {
            player->SetRotationSpeed(1.5f);
        }
        else if (event->key.keysym.sym == SDLK_SPACE)
        {
            Arrow *currentArrow = player->ShootArrow(0.8f);
            if (currentArrow)
            {
                arrows.back().reset(currentArrow);
                arrows.emplace_back();
                player->ReloadArrow();
            }
        }
        else if (event->key.keysym.sym == SDLK_ESCAPE)
        {
            eventTrigger.TriggerEvent(GameEvent::togglePauseGame);
        }
        break;
    case SDL_KEYUP:
        if (event->key.keysym.sym == SDLK_LEFT || event->key.keysym.sym == SDLK_RIGHT)
            player->SetVelocity({0.f, 0.f});
        if (event->key.keysym.sym == SDLK_UP || event->key.keysym.sym == SDLK_DOWN)
            player->SetRotationSpeed(0.f);
        break;
    default:
        break;
    }
}

void GameScreen::Update(const Timestep &dt)
{
    player->Update(dt);
    for (auto &arrow : arrows)
    {
        if (!arrow || !arrow->IsFreeFalling())
            continue;
        if (!ArrowHasLanded(arrow.get()))
        {
            arrow->Update(dt);
            ApplyGravity(arrow.get(), dt);
        }
    }
    currentSeconds += dt.GetSeconds();
}

void GameScreen::Render()
{
    backgrounds[GameResource::Background].Render();
    backgrounds[GameResource::Ground].Render();
    player->Render();
    for (auto &arrow : arrows)
        if (arrow)
            arrow->Render();
}

void GameScreen::AddText(GameResource type, SDL_Point position, int width, int height, SDL_Color color)
{
    auto font = fontLoader.GetAsset(assetIds[type]);
    TextSpecification textSpec = {
        font.get(),
        color,
        {position.x, position.y, width, height},
    };
    texts.try_emplace(type, window, " ", textSpec);
}

void GameScreen::AddBackground(GameResource type, SDL_Point position, int width, int height)
{
    auto texture = textureLoader.GetAsset(assetIds[type]);
    backgrounds.try_emplace(type, texture, position, width, height);
}

bool GameScreen::ArrowHasLanded(Arrow *arrow) const
{
    if (!arrow)
        return false;
    if ((arrow->GetPosition().y + arrow->GetSprite()->GetHeight() * glm::sin(arrow->GetOrientation())) > groundLevel)
    {
        arrow->SetVelocity({0.f, 0.f});
        arrow->SetRotationSpeed(0.f);
        arrow->DeactivateFreeFall();
        return true;
    }
    return false;
}

void GameScreen::ApplyGravity(Arrow *arrow, const Timestep &dt) const
{
    arrow->AddVelocity(gravity * dt.GetSeconds());
}
