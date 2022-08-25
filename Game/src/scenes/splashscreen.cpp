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
#include "Game/src/scenes/splashscreen.hpp"

SplashScreen::SplashScreen(Window &window, int switchToScene)
    : window(window), showForSeconds(3.0f),
      currentSeconds(0.0f), switchToScene(switchToScene) {}

bool SplashScreen::Init()
{
    assetIds[SplashSprite::Background] = textureLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_1/game_background_1.png");
    assetIds[SplashSprite::FpsFont] = fontLoader.AddAsset("assets/fonts/roboto/Roboto-Bold.ttf");

    auto background = textureLoader.GetAsset(assetIds[SplashSprite::Background]);
    SDL_Rect backgroundSize = {0, 0, window.GetWidth(), window.GetHeight()};

    auto fpsFont = fontLoader.GetAsset(assetIds[SplashSprite::FpsFont]);
    std::string text = "asas";
    TextSpecification textSpec = {
        {255, 255, 255, 255},
        fpsFont.get(),
        {window.GetWidth() - 100, window.GetHeight() - 30, 100, 30},
    };

    sprites[SplashSprite::Background] = std::make_unique<Sprite>(window, background.get(), backgroundSize);
    texts[SplashSprite::FpsFont] = std::make_unique<Text>(window, text, textSpec);

    return true;
}

void SplashScreen::Activate()
{
    currentSeconds = 0.0f;
}

void SplashScreen::Update(const Timestep &dt)
{
    currentSeconds += dt.GetSeconds();
    texts[SplashSprite::FpsFont]->SetText("FPS: " + std::to_string(window.GetFPS()));
}

void SplashScreen::Render()
{
    sprites[SplashSprite::Background]->Render();
    if (currentSeconds >= showForSeconds)
        texts[SplashSprite::FpsFont]->Render();
}