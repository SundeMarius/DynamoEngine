// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of Projects.
//
// Projects is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Projects is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Projects. If not, see <http://www.gnu.org/licenses/>.

#include "Dynamo/src/core/application.hpp"
#include "Dynamo/src/core/text.hpp"

#include <SDL2/SDL_image.h>

#include <iostream>

Application::Application(const WindowSpecification &windowSpec,
                         const ApplicationSpecification &applicationSpec)
    : window(windowSpec), appSpec(applicationSpec), winSpec(windowSpec), appLog(appSpec.logFile)
{
    appLog.Trace("Starting application: " + winSpec.name);
    if (!Init())
        throw std::runtime_error("Fatal error occured -- see log file " + appSpec.logFile);
    appLog.Success("Application initialized successfully");
}

Application::~Application()
{
    TTF_Quit();
    IMG_Quit();
    appLog.Trace("Application shut down");
}

bool Application::Init()
{
    window.Init();
    // Initialize texture settings
    if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
    {
        appLog.Fatal(IMG_GetError());
        return false;
    }
    // Initialize font settings
    if (TTF_Init() < 0)
    {
        appLog.Fatal(IMG_GetError());
        return false;
    }
    return true;
}

int Application::Start()
{
    SDL_Event event;
    while (running)
    {
        try
        {
            uint64_t startTimeMilliSec = SDL_GetTicks64();
            while (SDL_PollEvent(&event))
            {
                OnEvent(&event);
            }
            // Update time step is set to frame time in seconds
            SDL_RenderClear(window.GetRenderer());
            Update(frameTime);
            Render();
            SDL_RenderPresent(window.GetRenderer());
            // FPS
            frameTime = SDL_GetTicks64() - startTimeMilliSec;
            // Keep last frame time in window object
            window.SetFrameTime(frameTime);
        }
        catch (const std::exception &e)
        {
            appLog.Error(e.what());
        }
    }
    return 0;
}

void Application::Close()
{
    running = false;
}

int Application::GetFPS()
{
    int fps = frameTime.GetFPS();
    if (fps < 5)
    {
        appLog.Warning("Performance issues (" + std::to_string(fps) + " FPS)");
    }
    return fps;
}