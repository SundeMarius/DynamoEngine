// Copyright (C) 2022 Marius Sunde Sivertsen, marius.sunde.sivertsen@protonmail.com
//
// This file is part of DynamoEngine.
//
// DynamoEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// DynamoEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with DynamoEngine. If not, see <http://www.gnu.org/licenses/>.

#include "DynamoEngine/src/core/application.hpp"

#include <SDL2/SDL_image.h>

#include <iostream>

Application::Application(const WindowSpecification &windowSpec,
                         const ApplicationSpecification &applicationSpec)
    : window(windowSpec), appSpec(applicationSpec), winSpec(windowSpec), appLog(appSpec.logFile)
{
    appLog.Trace("Initializing application: " + winSpec.name);
    if (!Init())
        throw std::runtime_error("Fatal error occured -- see " + appSpec.logFile);
    int width = window.GetWidth();
    int height = window.GetHeight();
    fpsFont.LoadFromFile(window, "assets/fonts/open-sans/OpenSans-Semibold.ttf");
    TextSpecification textSpec = {&fpsFont, {200, 200, 200, 255}, {width * 0.95f, 0.f, width * 0.04f, height * 0.04f}};
    fpsCounter = Text(window, "FPS: ", textSpec);
    appLog.Success("Application initialized successfully");
}

Application::~Application()
{
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
        appLog.Fatal(TTF_GetError());
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
            SDL_RenderClear(window.GetSDLRenderer());
            Update(window.GetFrameTime());
            Render();
            if (appSpec.ShowFPSCounter)
            {
                RenderFpsCounter();
            }
            SDL_RenderPresent(window.GetSDLRenderer());
            // Keep last frame time in window object
            window.SetFrameTime(SDL_GetTicks64() - startTimeMilliSec);
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

void Application::RenderFpsCounter()
{
    fpsCounter.SetText("FPS: " + std::to_string(window.GetFPS()));
    fpsCounter.Render();
}
