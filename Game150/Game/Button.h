/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Button.h
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 8, 2024
*/

#pragma once
#include "../Engine/GameObject.h"

class Button : public CS230::GameObject {
public:
    Button(Math::vec3 start_position);
    void Update(double dt) override;
    //need fuction for collision!
    bool press = false;
};