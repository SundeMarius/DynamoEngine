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
#include "Dynamo/src/core/application.hpp"
#include "Dynamo/src/core/scenemanager.hpp"

#include <map>

enum class GameScene
{
    SplashScreen,
    GameScene,
    LoadingScene,
    FpsFont
};

class BallisticPotatoesGame : public Application
{
public:
    BallisticPotatoesGame(const WindowSpecification &windowSpec,
                          const ApplicationSpecification &applicationSpec);

    void OnEvent(SDL_Event *event) override;

    void Update(const Timestep &dt) override;

    void Render() override;

private:
    SceneManager sceneManager;
    std::map<GameScene, int> sceneIds{};
};