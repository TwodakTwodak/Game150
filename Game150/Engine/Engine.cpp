/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Engine.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Engine.h"
#include "GameStateManager.h"
#include <string>
#include <iostream>

Engine::Engine() :
#ifdef _DEBUG
    logger(CS230::Logger::Severity::Debug, true, last_tick)
#else
    logger(CS230::Logger::Severity::Event, true, last_tick)
#endif
{ }

void Engine::Start(std::string window_title) {
    last_tick = (std::chrono::system_clock::now());
    logger.LogEvent("Engine Started");
    window.Start(window_title);
    //Start other services
    last_test = last_tick;
    unsigned int seed = time(NULL);
    srand(seed);
    logger.LogEvent("Seed: "+ std::to_string(seed));
    //maybe need to fix
}

void Engine::Stop() {
    //Stop all services
    logger.LogEvent("Engine Stopped");
}

void Engine::Update() {

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    double dt = std::chrono::duration<double>(now - last_tick).count();

    if (dt > 1.0 / TargetFPS)
    {
        logger.LogVerbose("Engine Update");
        last_tick = now;
            

        frame_count++;
        if (frame_count >= FPSTargetFrames)
        {
             double time_between_now_and_last_test = std::chrono::duration<double>(now - last_test).count();
            logger.LogDebug("FPS: " + std::to_string(frame_count / time_between_now_and_last_test));
            
            frame_count = 0;
            last_test = now;
        }
            

        gamestatemanager.Update(dt);
        input.Update();
        window.Update();
        //Update other services
    }
}


bool Engine::HasGameEnded()
{
    if (gamestatemanager.HasGameEnded() == true || window.IsClosed()) return true;
}

void Engine::AddFont(const std::filesystem::path& file_name)
{
    fonts.push_back(file_name);
}