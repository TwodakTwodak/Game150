/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#pragma once
#include "../Engine/GameObject.h"

class Floor : public CS230::GameObject {
public:
    Floor(Math::vec3 start_position);
};