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
#include "splashscreen.hpp"

bool SplashScreen::Init()
{
    assetIds[SplashResource::SplashBackground] = surfaceLoader.AddAsset("assets/images/craftpix-402033-free-horizontal-2d-game-backgrounds/PNG/game_background_4/game_background_4.png");

    log.Trace("Splash screen initializing...");
    auto background = surfaceLoader.GetAsset(assetIds[SplashResource::SplashBackground]);
    SDL_FRect backgroundSize = {0.f, 0.f, float(window.GetWidth()), float(window.GetHeight())};
    images[SplashResource::SplashBackground] = std::make_unique<Sprite>(
        window,
        backgroundSize,
        background);
    log.Success("Splash screen initialized");
    return true;
}

void SplashScreen::Activate()
{
    currentSeconds = 0.0f;
}

bool SplashScreen::Completed()
{
    return currentSeconds > showForSeconds;
}

void SplashScreen::Update(const Timestep &dt)
{
    currentSeconds += dt.GetSeconds();
}

void SplashScreen::Render()
{
    images[SplashResource::SplashBackground]->Render();
}