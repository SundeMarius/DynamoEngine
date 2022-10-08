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

Application::Application(const ApplicationSpecification &applicationSpec)
    : window(applicationSpec.windowSpecification), appSpec(applicationSpec), appLog(applicationSpec.config.at("Debug").at("appLogFileName"))
{
    appLog.Trace("Initializing application: " + applicationSpec.windowSpecification.name);
    if (!Init())
        throw std::runtime_error("Fatal error occured while initializing the application components. See the log for details");
    appLog.Success("Application initialized successfully");
}

Application::~Application()
{
    appLog.Success("Application shut down successfully");
}

bool Application::Init()
{
    appLog.Trace("Initializing window of size " + std::to_string(window.GetWidth()) + "x" + std::to_string(window.GetHeight()));
    window.Init();
    appLog.Trace("Window initialized");
    // Initialize texture settings
    appLog.Trace("Initializing video components:");
    appLog.Trace("\tInitializing SDL_Image");
    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        appLog.Fatal(IMG_GetError());
        return false;
    }
    // Initialize font settings
    appLog.Trace("\tInitializing SDL_TTF");
    if (TTF_Init() < 0)
    {
        appLog.Fatal(TTF_GetError());
        return false;
    }
    appLog.Success("All video components initialized");
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
            SDL_RenderPresent(window.GetSDLRenderer());
            window.SetFrameTime(SDL_GetTicks64() - startTimeMilliSec);
        }
        catch (const std::exception &e)
        {
            appLog.Error(e.what());
            std::cerr << "An error occured while the game was running. See the log.\n";
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

void Application::Close()
{
    running = false;
}