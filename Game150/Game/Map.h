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
#include "Player.h"
#include "../Engine/Dimension.h"
#include <vector>
#include "../Engine/Vec3.h"

struct PortalLocation {
public:
    void SetLocation(Math::vec3 loc) { location = loc; }
    void SetNum(int n) { num = n; }
    Math::vec3 GetLocation() { return location; }
private:
    Math::vec3 location;
    int num;
};

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
    static constexpr double floor = 200;
    static constexpr double timer_max = 30;
    
    void ExitCheck();
    void BoxCollisionNum(int value);
    std::vector<PortalLocation> GivePortal1();
    std::vector<PortalLocation> GivePortal2();

    void SwitchNumIncrease();
private:
    CS230::GameObjectManager gameobjectmanager;
    CS230::Texture* background;
    
    int load_object_number = 0;
    int room_object_memory[100] = { 0 };
    int memory = 1;
    int room = 1;
    
    //temp
    bool button_work = false;
    Player* player_ptr;
    Math::TransformationMatrix matrix;
    CurrentDimension dimension;
    
    int collsion_num = 0;
    int button_num = 0;
    int portal_num = 0;
    int room_num = 0;
    
    PortalLocation pl;
    
    int switch_num = 0;

    bool room_moving_available = true;
    Music backgroundMusic;
};

//Why don't it work when i change driection of headerfile, why does it work after retyping.