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
#include "splashscreen.hpp"

bool SplashScreen::Init()
{
    assetIds[SplashResource::SplashBackground] = textureLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_4/game_background_4.png");
    SDL_Point point = {0, 0};
    auto background = textureLoader.GetAsset(assetIds[SplashResource::SplashBackground]);
    backgrounds.try_emplace(SplashResource::SplashBackground, background, point, window.GetWidth(), window.GetHeight());
    return true;
}

void SplashScreen::Activate()
{
    currentSeconds = 0.0f;
}

void SplashScreen::Finish()
{
    SDL_Event switchSceneEvent;
    switchSceneEvent.type = eventType;
    SDL_PushEvent(&switchSceneEvent);
}

void SplashScreen::Update(const Timestep &dt)
{
    currentSeconds += dt.GetSeconds();
    if (currentSeconds > showForSeconds)
        Finish();
}

void SplashScreen::Render()
{
    backgrounds[SplashResource::SplashBackground].Render();
}