/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#pragma once
#include "../Engine/GameObject.h"

class Locked_Wall : public CS230::GameObject {
public:
    Locked_Wall(Math::vec3 start_position);
};