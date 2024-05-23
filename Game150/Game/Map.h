/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#pragma once

#include "../Engine/GameState.h"
#include "../Engine/GameObjectManager.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObject.h"
#include "../Engine/Input.h"
#include "../Engine/Camera.h"


class Map : public CS230::GameState {
public:
    Map();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;
  
    std::string GetName() override {
        return "Map";
    }

    //In future we could choose gravity for each map!
    static constexpr double gravity = 800;
    static constexpr double floor = 100;
    static constexpr double timer_max = 30;
    int room = 1;

private:
    CS230::GameObjectManager gameobjectmanager;
    CS230::Texture* background;
    
    int load_object_number = 0;
    int room_object_memory[100] = { 0 };
    int memory = 1;

    //temp
    bool button_work = false;
};

//Why don't it work when i change driection of headerfile, why does it work after retyping.