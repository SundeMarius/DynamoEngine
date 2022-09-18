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
#include "DynamoEngine/src/core/application.hpp"
#include "DynamoEngine/src/core/scenemanager.hpp"

#include <map>

enum class GameScene
{
    SplashScreen,
    LoadingScene,
    GameScene,
};

class Game : public Application
{
public:
    Game(const WindowSpecification &windowSpec,
         const ApplicationSpecification &applicationSpec);

    void OnEvent(SDL_Event *event) override;

    void Update(const Timestep &dt) override;

    void Render() override;

private:
    SceneManager sceneManager;
    std::map<GameScene, int> sceneIds{};

    uint32_t switchToGameSceneEventType;
};