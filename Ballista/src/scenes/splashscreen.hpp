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

#include "DynamoEngine/src/core/image.hpp"
#include "DynamoEngine/src/core/scene.hpp"
#include "DynamoEngine/src/assets/assetloader.hpp"
#include "DynamoEngine/src/assets/font.hpp"
#include "DynamoEngine/src/core/text.hpp"
#include "DynamoEngine/src/assets/texture.hpp"

#include "Ballista/src/utilities/eventtrigger.hpp"

#include <map>

enum class SplashResource
{
    SplashBackground,
};

class SplashScreen : public Scene
{
public:
    SplashScreen(Window &window, EventTrigger &eventTrigger) : window(window), eventTrigger(eventTrigger), fontLoader(window) {}

    bool Init() override;
    void Activate() override;
    void Finish() override;
    void Update(const Timestep &dt) override;
    void ProcessInput(SDL_Event *event) override { (void)event; }
    void Render() override;

private:
    Window &window;
    EventTrigger &eventTrigger;
    AssetLoader<Font> fontLoader;

    float showForSeconds = 1.f;
    float currentSeconds = 0.f;
};