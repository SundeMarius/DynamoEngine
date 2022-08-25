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
#include "CannonLaunch.hpp"
#include "scenes/splashscreen.hpp"

#include "Lib/src/core/entrypoint.hpp"
#include "Lib/src/core/text.hpp"

CannonLaunchGame::CannonLaunchGame(const WindowSpecification &windowSpec,
                                   const ApplicationSpecification &applicationSpec) : Application(windowSpec, applicationSpec)
{
    try
    {
        std::unique_ptr<Scene> splashScreen = std::make_unique<SplashScreen>(window, 1);
        int splashScreenID = sceneManager.AddScene(splashScreen);
        sceneManager.SwitchScene(splashScreenID);
    }
    catch (const std::exception &e)
    {
        appLog.Warning(e.what());
        std::cerr << e.what() << std::endl;
    }
}

void CannonLaunchGame::OnEvent(SDL_Event *event)
{
    if (event->type == SDL_QUIT)
    {
        Close();
    }
}

void CannonLaunchGame::Update(const Timestep &dt)
{
    sceneManager.Update(dt);
}

void CannonLaunchGame::Render()
{
    sceneManager.Render();
}

Application *CreateApplication(ApplicationCommandLineArguments args)
{
    WindowSpecification windowSpec = {
        .name = "Cannon hell",
        .width = 1920,
        .height = 1080,
    };
    ApplicationSpecification appSpec = {
        .ShowFPSCounter = true,
        .args = args,
    };
    return new CannonLaunchGame(windowSpec, appSpec);
}
