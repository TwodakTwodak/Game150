/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Mode1.cpp
Project:    CS230 Engine
Author:     Jonathan Holmes, Seunghyeon Song
Created:    March 8, 2023
Upadted:    March 14, 2024
*/

#include "../Engine/Engine.h"
#include "States.h"
#include "Map.h"
#include "Player.h"
#include "Crates.h"
#include "Floor.h"
#include "Float_Floor.h"
#include "Button.h"
#include "../Engine/FileIO.h"
#include "Wall_Floor.h"



Player* player_ptr = nullptr;

Map::Map() {
}

void Map::Load() {

	player_ptr = new Player({ 0, 0, 300 });
	background = Engine::GetTextureManager().Load("Assets/Background.png");
	gameobjectmanager.Add(player_ptr);
	/*gameobjectmanager.Add(new Crates({ 200, 400, 400 }));
	gameobjectmanager.Add(new Crates({ 400, floor, 300 }));
	gameobjectmanager.Add(new Crates({ 600, 80, 200 }));*/
	if (room_object_memory[room] == 0)
	{
		while (GetRoom(load_object_number) <= room && GetRoom(load_object_number) != 0)
		{
			if (GetRoom(load_object_number) == room)//check room
			{
				if (GetType(load_object_number) == "box")//check type
				{
					gameobjectmanager.Add(new Crates(GetPosition(load_object_number)));
					gameobjectmanager.box_length.y += 1;
				}
				if (GetType(load_object_number) == "button")//check type
				{
					gameobjectmanager.Add(new Button(GetPosition(load_object_number)));
					gameobjectmanager.button_length.y += 1;
				}
				if (GetType(load_object_number) == "float_floor")
				{
					gameobjectmanager.Add(new Float_Floor(GetPosition(load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(load_object_number) == "floor") 
				{
					gameobjectmanager.Add(new Floor(GetPosition(load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(load_object_number) == "wall_floor")
				{
					gameobjectmanager.Add(new Wall_Floor(GetPosition(load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(load_object_number) == "wall_floor2")
				{
					gameobjectmanager.Add(new Wall_Floor2(GetPosition(load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
			}
			load_object_number++;
		}
		room_object_memory[room] = load_object_number - room_object_memory[room - 1];
	}
	else
	{
		int max_temp = room_object_memory[room] + room_object_memory[room - 1];
		int temp_load_object_number = room_object_memory[room - 1];

		while (temp_load_object_number < max_temp)
		{
			if (GetRoom(temp_load_object_number) == room)//check room
			{
				if (GetType(temp_load_object_number) == "box")//check type
				{
					gameobjectmanager.Add(new Crates(GetPosition(temp_load_object_number)));
					gameobjectmanager.box_length.y += 1;
				}
				if (GetType(temp_load_object_number) == "button")//check type
				{
					gameobjectmanager.Add(new Button(GetPosition(temp_load_object_number)));
					gameobjectmanager.button_length.y += 1;
				}
				if (GetType(temp_load_object_number) == "float_floor")
				{
					gameobjectmanager.Add(new Float_Floor(GetPosition(temp_load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(temp_load_object_number) == "wall_floor2")
				{
					gameobjectmanager.Add(new Wall_Floor2(GetPosition(temp_load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(temp_load_object_number) == "wall_floor")
				{
					gameobjectmanager.Add(new Wall_Floor(GetPosition(temp_load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
				if (GetType(temp_load_object_number) == "floor") 
				{
					gameobjectmanager.Add(new Floor(GetPosition(temp_load_object_number)));
					gameobjectmanager.floor_length.y += 1;
				}
			}
			temp_load_object_number++;
		}
	}

	gameobjectmanager.box_length.x = 1;
	gameobjectmanager.box_length.y += 1;

	gameobjectmanager.button_length.x = gameobjectmanager.box_length.y;
	gameobjectmanager.button_length.y += gameobjectmanager.button_length.x;

	gameobjectmanager.floor_length.x = gameobjectmanager.button_length.y;
	gameobjectmanager.floor_length.y += gameobjectmanager.floor_length.x;

	gameobjectmanager.Reorder(gameobjectmanager.main_view);
}

void Map::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Nine)) {
		dt = dt * 0.1;
	}
	gameobjectmanager.UpdateAll(dt);
	if (room == 2) {
		if (!static_cast<Button*>(gameobjectmanager.collision_objects[2])->press && player_ptr->GetPosition().x > Engine::GetWindow().GetSize().x - 200.0) {
			player_ptr->SetPosition({ Engine::GetWindow().GetSize().x - 200.0, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
		}
	}
	if (player_ptr->GetPosition().x > Engine::GetWindow().GetSize().x && room < 5|| Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		room++;
		Unload();
		Load();
	}
	else if (player_ptr->GetPosition().x < 0 && room > 1|| Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
		room--;	
		Unload();
		Load();
		player_ptr->SetPosition({ (double)Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
		
	}
	else if (player_ptr->GetPosition().x < 0 && room <= 1) {
		player_ptr->SetPosition({ 0, player_ptr->GetPosition().y, player_ptr->GetPosition().z});
	}
	else if (player_ptr->GetPosition().x >= Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x && room >= 5) {
		player_ptr->SetPosition({ (double)Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
	}
	
}

void Map::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	background->Draw(Math::TranslationMatrix(Math::vec2{0,0}));
	gameobjectmanager.DrawAll(Math::TransformationMatrix());
}

void Map::Unload() {
	gameobjectmanager.Unload();
	background = nullptr;
	player_ptr = nullptr;
}