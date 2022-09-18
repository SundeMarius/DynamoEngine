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

Game::Game(const WindowSpecification &windowSpec,
           const ApplicationSpecification &applicationSpec)
    : Application(windowSpec, applicationSpec), sceneManager{}
{
    try
    {
        // Register custom game events
        switchToGameSceneEventType = SDL_RegisterEvents(1);

        // Add scenes
        appLog.Trace("Splash screen initializing...");
        sceneIds[GameScene::SplashScreen] = sceneManager.AddScene(std::make_unique<SplashScreen>(window, switchToGameSceneEventType));
        appLog.Success("Splash screen initialized");

        appLog.Trace("Main game screen initializing...");
        sceneIds[GameScene::GameScene] = sceneManager.AddScene(std::make_unique<GameScreen>(window));
        appLog.Trace("Main game screen initialized!");

        sceneManager.SwitchScene(sceneIds[GameScene::SplashScreen]);
    }
    catch (const std::exception &e)
    {
        appLog.Warning(e.what());
    }
}

void Game::OnEvent(SDL_Event *event)
{
    if (event->type == switchToGameSceneEventType)
        sceneManager.SwitchScene(sceneIds[GameScene::GameScene]);
    switch (event->type)
    {
    case SDL_QUIT:
        Close();
        break;
    default:
        sceneManager.ProcessInput(event);
    }
}

void Game::Update(const Timestep &dt)
{
    sceneManager.Update(dt);
}

void Game::Render()
{
    sceneManager.Render();
}

Application *CreateApplication(ApplicationCommandLineArguments args)
{
    WindowSpecification windowSpec = {
        .name = "Cross bow mayham",
        .width = 1920,
        .height = 1080,
    };
    ApplicationSpecification appSpec = {
        .ShowFPSCounter = true,
        .args = args,
    };
    return new Game(windowSpec, appSpec);
}
