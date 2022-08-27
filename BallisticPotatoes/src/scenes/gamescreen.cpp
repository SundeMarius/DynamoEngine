// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of BallisticPotatoes.
//
// BallisticPotatoes is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// BallisticPotatoes is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with BallisticPotatoes.  If not, see <http://www.gnu.org/licenses/>.
#include "gamescreen.hpp"

bool GameScreen::Init()
{
    assetIds[GameResource::FpsFont] = fontLoader.AddAsset("assets/fonts/open-sans/OpenSans-Semibold.ttf");
    assetIds[GameResource::Background1] = surfaceLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_1/game_background_1.png");
    assetIds[GameResource::Background2] = surfaceLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_2/game_background_2.png");
    assetIds[GameResource::Background3] = surfaceLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_3/game_background_3.1.png");
    assetIds[GameResource::Background4] = surfaceLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_4/game_background_4.png");
    assetIds[GameResource::Ground] = surfaceLoader.AddAsset("assets/images/ground/grass_block.png");

    int textX = window.GetWidth() * 0.96;
    int textY = 0;
    int textWidth = window.GetWidth() * 0.04;
    int textHeight = window.GetHeight() * 0.04;
    AddText(GameResource::FpsFont, textX, textY, textWidth, textHeight, {150, 150, 200, 230});
    log.Trace("FPS font initialized!");

    log.Trace("Main game screen initializing...");
    AddImage(GameResource::Background3, 0, 0, window.GetWidth(), window.GetHeight());

    int groundPosX = 0;
    int groundPosY = window.GetHeight() - window.GetHeight() / 10;
    int groundWidth = window.GetWidth();
    int groundHeight = window.GetHeight() / 10;
    AddSprite(GameResource::Ground, groundPosX, groundPosY, groundWidth, groundHeight);

    // Add player
    SDL_FRect playerBox = {0.1f * window.GetWidth(), 0.1f * window.GetHeight(), 0.2f * window.GetWidth(), 0.1f * window.GetHeight()};
    SDL_Color color = {200, 100, 100, 200};
    sprites[GameResource::CannonPlayer] = std::make_unique<Sprite>(window, playerBox, color);
    player = Cannon({0.4 * window.GetWidth(), 0.5 * window.GetHeight()}, sprites[GameResource::CannonPlayer].get());
    player.SetVelocity({15.f, -40.f});

    log.Trace("Main game screen initialized!");
    return true;
}

void GameScreen::Activate()
{
    currentSeconds = 0.f;
}

void GameScreen::Update(const Timestep &dt)
{
    currentSeconds += dt.GetSeconds();
    player.Update(dt);
    texts[GameResource::FpsFont]->SetText("FPS: " + std::to_string(window.GetFPS()));
}

void GameScreen::Render()
{
    images[GameResource::Background3]->Render();
    sprites[GameResource::Ground]->Render();
    player.Render();
    // ...
    texts[GameResource::FpsFont]->Render();
}

void GameScreen::AddText(GameResource type, float textPosX, float textPosY, float textWidth, float textHeight, SDL_Color color)
{
    auto font = fontLoader.GetAsset(assetIds[type]);
    TextSpecification textSpec = {
        color,
        font,
        {textPosX, textPosY, textWidth, textHeight},
    };
    texts[type] = std::make_unique<Text>(window, "", textSpec);
}

void GameScreen::AddImage(GameResource type, float posX, float posY, float width, float height)
{
    auto texture = surfaceLoader.GetAsset(assetIds[type]);
    SDL_FRect size = {posX, posY, width, height};
    images[type] = std::make_unique<Sprite>(window, size, texture);
}

void GameScreen::AddSprite(GameResource type, float posX, float posY, float width, float height)
{
    auto surface = surfaceLoader.GetAsset(assetIds[type]);
    SDL_FRect size = {posX, posY, width, height};
    sprites[type] = std::make_unique<Sprite>(window, size, surface);
}

void GameScreen::AddSprite(GameResource type, float posX, float posY, float width, float height, SDL_Color color)
{
    SDL_FRect box = {posX, posY, width, height};
    SDL_Color col = color;
    sprites[type] = std::make_unique<Sprite>(window, box, col);
}
