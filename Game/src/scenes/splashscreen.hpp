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
#pragma once

#include "Lib/src/core/sprite.hpp"
#include "Lib/src/core/scene.hpp"
#include "Lib/src/assets/assetsloader.hpp"
#include "Lib/src/assets/font.hpp"
#include "Lib/src/core/text.hpp"
#include "Lib/src/assets/surface.hpp"

#include <map>

enum class SplashSprite
{
    Background,
    FpsFont
};

class SplashScreen : public Scene
{
public:
    SplashScreen(Window &window, int switchToScene);

    bool Init() override;
    void Activate() override;
    void Update(const Timestep &dt) override;
    void Render() override;

    bool IsFinished() { return currentSeconds > showForSeconds; }

private:
    Window &window;

    AssetsLoader<Surface> textureLoader{};
    AssetsLoader<Font> fontLoader{};
    std::map<SplashSprite, int> assetIds;

    std::map<SplashSprite, std::unique_ptr<Sprite>> sprites;
    std::map<SplashSprite, std::unique_ptr<Text>> texts;

    float showForSeconds;
    float currentSeconds;
    int switchToScene;
};