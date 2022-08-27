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
#pragma once

#include "Dynamo/src/core/sprite.hpp"
#include "Dynamo/src/core/scene.hpp"
#include "Dynamo/src/assets/assetloader.hpp"
#include "Dynamo/src/assets/font.hpp"
#include "Dynamo/src/core/text.hpp"
#include "Dynamo/src/assets/surface.hpp"

#include <map>

enum class SplashResource
{
    SplashBackground,
    FpsFont
};

class SplashScreen : public Scene
{
public:
    SplashScreen(Window &window, Log &log) : window(window), log(log), textureLoader(log), fontLoader(log) {}

    bool Init() override;
    void Activate() override;
    bool Completed() override;
    void Update(const Timestep &dt) override;
    void Render() override;

private:
    Window &window;
    Log &log;

    AssetLoader<Surface> textureLoader;
    AssetLoader<Font> fontLoader;
    std::map<SplashResource, int> assetIds{};

    std::map<SplashResource, std::unique_ptr<Sprite>> images{};
    std::map<SplashResource, std::unique_ptr<Sprite>> sprites{};
    std::map<SplashResource, std::unique_ptr<Text>> texts{};

    float showForSeconds = 3.f;
    float currentSeconds = 0.f;
};