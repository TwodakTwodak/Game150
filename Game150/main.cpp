/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  main.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include <iostream>

#include "Engine/Engine.h"
#include "Engine/FileIO.h"
#include "Game/Splash.h"
#include "Game/Map.h"
#include "Game/Logo.h"
#include "Game//MainMenu.h"

int main() {
    try {
        Engine& engine = Engine::Instance();
        engine.Start("Shadow Diminesion");

        engine.AddFont("Assets/Font_Simple.png");
        engine.AddFont("Assets/Font_Outlined.png");

        Splash splash;
        engine.GetGameStateManager().AddGameState(splash);
        Logo logo;
        engine.GetGameStateManager().AddGameState(logo);
        MainMenu maimnenu;
        engine.GetGameStateManager().AddGameState(maimnenu);
        FileInput("Assets/object.txt");
        Map map;
        engine.GetGameStateManager().AddGameState(map);

        while (engine.HasGameEnded() == false) {
            engine.Update();
        }

        engine.Stop();

        return 0;
    }
    catch (std::exception& e) {
        std::cerr << e.what() << "\n";
        return -1;
    }
}
