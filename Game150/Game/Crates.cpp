/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#include "Map.h"
#include "Crates.h"
#include "Button.h"
#include "../Engine/Collision.h"

Crates::Crates(Math::vec3 start_position) : 
    CS230::GameObject(start_position)
{
    collision_type = Move;
    side_sprite.Load("Assets/Crates1.spt");
    top_sprite.Load("Assets/Crates1.spt");
}

void Crates::Update(double dt) {
    check_view();
    gravity(dt);
    GameObject::Update(dt);
}

void Crates::Collision(GameObject* compare, Collision_Type type)
{
    if (type == Block) {
        Collision_Floor(compare);
    }
    else if (type == Detect) {
        Collision_Button(compare);
    }
}

void Crates::gravity(double dt)
{
    UpdateVelocity({ 0 , -Map::gravity * dt, 0 });
}

void Crates::Collision_Floor(GameObject* compare)
{
    UpdatePosition(collision->GetDistance(compare));
    if (collision->distance.x != 0) {
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z});
    }
    if (collision->distance.y > 0) {
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
    }
    if (collision->distance.z != 0) {
        SetVelocity({ GetVelocity().x, GetVelocity().y, 0 });
    }
}

void Crates::Collision_Button(GameObject* compare)
{
    if (collision->CollisionDetect(compare)) {
        static_cast<Button*>(compare)->press = true;
    }
    else {
        static_cast<Button*>(compare)->press = false;
    }
}
