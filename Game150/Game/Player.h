/*
File Name:  Player.h
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/
#pragma once

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObject.h"


struct key_order {
	bool press;
};

class Player : public CS230::GameObject {
public:
	Player(Math::vec3 start_position);
	void Update(double dt) override;
	void Collision(GameObject* compare, Collision_Type type) override;
	void Collision_Floor(GameObject* compare);
	void Collision_Box(GameObject* compare);
	const Math::vec3& GetPosition() const { return GameObject::GetPosition(); };


private:
	
	static constexpr double xz_acceleration = 300;
	static constexpr double xz_drag = 450;
	static constexpr double max_velocity = 200;
	static constexpr double jump_velocity =350;
	static constexpr double dash_velocity = 3000;
	static constexpr double cool_time = 1.5;
	bool jumping = false;
	bool falling = false;
	double dash_start_pos;
	bool gravi = true;
	bool key_order[4];
	double cool_timer;

	void move(double dt);

	void gravity(double dt);

};