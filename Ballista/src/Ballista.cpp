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
#include "Ballista.hpp"

#include "scenes/splashscreen.hpp"
#include "scenes/loadingscreen.hpp"
#include "scenes/gamescreen.hpp"

#include "DynamoEngine/src/core/entrypoint.hpp"
#include "DynamoEngine/src/core/text.hpp"

BallistaGame::BallistaGame(const WindowSpecification &windowSpec,
                           const ApplicationSpecification &applicationSpec)
    : Application(windowSpec, applicationSpec), sceneManager{}
{
    try
    {
        // Add scenes
        std::unique_ptr<Scene> splashScreen = std::make_unique<SplashScreen>(window, appLog);
        sceneIds[GameScene::SplashScreen] = sceneManager.AddScene(splashScreen);
        std::unique_ptr<Scene> gameScreen = std::make_unique<GameScreen>(window, appLog);
        sceneIds[GameScene::GameScene] = sceneManager.AddScene(gameScreen);

        sceneManager.SwitchScene(sceneIds[GameScene::SplashScreen]);
    }
    catch (const std::exception &e)
    {
        appLog.Warning(e.what());
        std::cerr << e.what() << std::endl;
    }
}

void BallistaGame::OnEvent(SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_QUIT:
        Close();
        break;
    default:
        sceneManager.ProcessInput(event);
        break;
    }
}

void BallistaGame::Update(const Timestep &dt)
{
    sceneManager.Update(dt);
    if (sceneManager.GetScene(sceneIds[GameScene::SplashScreen])->Completed())
        sceneManager.SwitchScene(sceneIds[GameScene::GameScene]);
}

void BallistaGame::Render()
{
    sceneManager.Render();
}

Application *CreateApplication(ApplicationCommandLineArguments args)
{
    WindowSpecification windowSpec = {
        .name = "Ballista!",
        .width = 1920,
        .height = 1080,
    };
    ApplicationSpecification appSpec = {
        .ShowFPSCounter = true,
        .args = args,
    };
    return new BallistaGame(windowSpec, appSpec);
}
