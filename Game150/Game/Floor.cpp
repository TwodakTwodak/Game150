/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Floor.h"

Floor::Floor(Math::vec3 start_position)
{
    collision_type = Block;
    side_sprite.Load("Assets/Side_Floor.spt");
    top_sprite.Load("Assets/Top_Floor.spt");
}
