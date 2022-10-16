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
#include "game.hpp"

#include "scenes/splashscreen.hpp"
#include "scenes/loadingscreen.hpp"
#include "scenes/gamescreen.hpp"
#include "utilities/events.hpp"

#include "DynamoEngine/src/core/entrypoint.hpp"
#include "DynamoEngine/src/core/text.hpp"

#include <fstream>
#include <iostream>

Game::Game(const ApplicationSpecification &applicationSpec) : Application(applicationSpec)
{
    try
    {
        eventTrigger.RegisterEvent(GameEvent::togglePauseGame);
        eventTrigger.RegisterEvent(GameEvent::switchToGameScene);
        eventTrigger.RegisterEvent(GameEvent::arrowLaunched);

        int width = window.GetWidth();
        int height = window.GetHeight();
        fpsTextSpec = TextSpecification(
            window,
            applicationSpec.config.at("Debug").at("fontPath"),
            {200, 200, 200, 255}, {int(width * 0.95f), 0, int(width * 0.04f), int(height * 0.04f)});

        appLog.Trace("Splash screen initializing...");
        sceneIds[GameScene::SplashScreen] = sceneManager.AddScene(std::make_unique<SplashScreen>(window, eventTrigger));
        appLog.Success("Splash screen initialized");

        appLog.Trace("Main game screen initializing...");
        BallistaAssetConfig playerConfig = {
            .chassisTexturePath = applicationSpec.config.at("Assets").at("Player").at("chassisTexturePath"),
            .backwheelTexturePath = applicationSpec.config.at("Assets").at("Player").at("backwheelTexturePath"),
            .frontwheelTexturePath = applicationSpec.config.at("Assets").at("Player").at("frontwheelTexturePath"),
            .bowTexturePath = applicationSpec.config.at("Assets").at("Player").at("bowTexturePath"),
            .arrowTexturePath = applicationSpec.config.at("Assets").at("Player").at("arrowTexturePath"),
        };
        GameSceneAssetConfig sceneConfig = {
            .backgroundPath = applicationSpec.config.at("Assets").at("GameScene").at("backgroundPath"),
            .grassPath = applicationSpec.config.at("Assets").at("GameScene").at("grassPath"),
            .playerConfig = playerConfig,
        };
        sceneIds[GameScene::GameScene] = sceneManager.AddScene(std::make_unique<GameScreen>(sceneConfig, window, eventTrigger));
        appLog.Success("Main game screen initialized!");

        TurnFPSCounterOff();
        sceneManager.SwitchScene(sceneIds[GameScene::SplashScreen]);
    }
    catch (const std::exception &e)
    {
        appLog.Error(e.what());
        std::cerr << "An error occured while initializing the game\n";
        Close();
    }
}

void Game::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        Close();
    }
    else if (event->type == eventTrigger.GetEventType(GameEvent::switchToGameScene))
    {
        TurnFPSCounterOn();
        sceneManager.SwitchScene(sceneIds[GameScene::GameScene]);
    }
    else if (event->type == eventTrigger.GetEventType(GameEvent::togglePauseGame))
    {
        pauseGame = !pauseGame;
    }
    else if (event->type == eventTrigger.GetEventType(GameEvent::arrowLaunched))
    {
        appLog.Debug("Arrow launched!");
    }
    else
    {
        sceneManager.ProcessInput(event);
    }
}

void Game::Update(const Timestep &dt)
{
    if (pauseGame)
        return;
    sceneManager.Update(dt);
}

void Game::Render()
{
    if (pauseGame)
        return;
    sceneManager.Render();
    if (showDebugInfo)
        RenderFpsCounter();
}

void Game::RenderFpsCounter()
{
    fpsText = Text(window, "FPS: " + std::to_string(window.GetFPS()), fpsTextSpec);
    fpsText.Render();
}

Application *CreateApplication(ApplicationCommandLineArguments args)
{
    if (args.argc < 2)
    {
        std::cerr << "Please provide the config file as an argument: " + std::string(args.argv[0]) + " config.json\n";
        return nullptr;
    }
    std::string configFilePath = args.argv[1];
    try
    {
        std::ifstream file(configFilePath);
        file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
        json config = json::parse(file);
        WindowSpecification winSpec = {
            .name = config.at("Game").at("name"),
            .width = config.at("Window").at("width"),
            .height = config.at("Window").at("height"),
        };
        ApplicationSpecification appSpec = {
            .config = config,
            .windowSpecification = winSpec,
            .args = args,
        };
        return new Game(appSpec);
    }
    catch (std::iostream::failure &e)
    {
        std::cerr << "Error opening/reading file " + configFilePath + ": " << strerror(errno) << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    return nullptr;
}
