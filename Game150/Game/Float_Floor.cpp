/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Float_Floor.h"

Float_Floor::Float_Floor(Math::vec3 start_position) : CS230::GameObject(start_position)
{
    collision_type = Block;
    side_sprite.Load("Assets/Side_Float_Floor.spt");
    top_sprite.Load("Assets/Top_Float_Floor.spt");
}
