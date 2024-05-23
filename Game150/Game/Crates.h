/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Crates.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "../Engine/GameObject.h"

class Crates : public CS230::GameObject {
public:
    Crates(Math::vec3 start_position);
    void Update(double dt) override;
    void Collision(GameObject* compare, Collision_Type type) override;
    void Collision_Floor(GameObject* compare);
    void Collision_Button(GameObject* compare);

private:
    void gravity(double dt);
};