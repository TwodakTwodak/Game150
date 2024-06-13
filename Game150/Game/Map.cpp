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
#include "../Engine/FileIO.h"
#include "Background.h"
#include "Gravity.h"
#include "Box.h"
#include "Wall.h"
#include "Portal.h"
#include "Exit.h"
#include "Lever.h"
#include "Button.h"
#include "Trampoline.h"
#include "Room.h"
#include "raylib.h" 

std::vector<PortalLocation> portal_location1;
std::vector<PortalLocation> portal_location2;
int switch_pressed = 0;
bool on_exit;
Map::Map(): backgroundMusic {} {
	States currentState = static_cast<States>(Engine::GetGameStateManager().GetCurrentGameState());
	if (currentState == States::Map) {
		InitAudioDevice();
	}
}

void Map::Load() {
	backgroundMusic = LoadMusicStream("Assets/c.mp3");
	PlayMusicStream(backgroundMusic);
	portal_num = 0;
	switch_pressed = 0;
	on_exit = false;
	room_moving_available = true;
	switch_num = 0;
	portal_num = 0;
	button_num = 0;
	room_num = 0;
	dimension.SetDimension(Dimension::Side);
	player_ptr = new Player({ 200, 400, floor+66 });
	AddGSComponent(new CS230::GameObjectManager);
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);

	AddGSComponent(new CS230::Camera({ { 1.0 * Engine::GetWindow().GetSize().x, 0, 0 }, { 1.0 * Engine::GetWindow().GetSize().x, 0, 0 }}));
	GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0, 0 });

	AddGSComponent(new Background);
	GetGSComponent<Background>()->Add("Assets/Background.png", 0);

	Math::icube cameraLimit = { { 0,0, 0 }, { Engine::GetWindow().GetSize().x , Engine::GetWindow().GetSize().y , Engine::GetWindow().GetSize().y}  };
	GetGSComponent<CS230::Camera>()->SetLimit(cameraLimit);

	AddGSComponent(new Gravity(Map::gravity));

	//GetGSComponent<CS230::GameObjectManager>()->Add(new Box({ 100, 100, floor }));

	//GetGSComponent<CS230::GameObjectManager>()->Add(new Wall({ 700, 550, floor }));
	//
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 0, -200, 0 }, 1));
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 0, 900, 0 }, 1));
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ -200, 0, 0 }, 2));
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 1600, 0, 0 }, 2));
	//
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Floor({ 0, 0, 0 }));

	//GetGSComponent<CS230::GameObjectManager>()->Add(new Button({ 700, 100, 200 }));
	//button_num++;

	//
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Portal1({ 100, 100, 200 }, portal_num));
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Portal2({ 1400, 100, 200 }, portal_num));
	//
	//pl.SetLocation({ 100, 100, 200 });
	//pl.SetNum(portal_num);
	//portal_location1.push_back(pl);
	//pl.SetLocation({ 1400, 100, 200 });
	//portal_location2.push_back(pl);
	//portal_num++;
	//
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Lever({ 500, 500, 200 }));
	//switch_num++;
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Lever({ 1000, 300, 200 }));
	//switch_num++;

	//GetGSComponent<CS230::GameObjectManager>()->Add(new Exit({ 1400, 500, 200 }));

	//GetGSComponent<CS230::GameObjectManager>()->Add(new Trampoline({ 1000, 100, 100 }));
	
	//GetGSComponent<CS230::GameObjectManager>()->Add(new Exit(static_cast<int>(States::MainMenu), Math::icube{ { 1300, 50, 50 }, { 1600, 800, 800 } }));
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
					GetGSComponent<CS230::GameObjectManager>()->Add(new Box(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "button")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Button(GetPosition(load_object_number)));
					button_num++;
				}
				if (GetType(load_object_number) == "lever")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Lever(GetPosition(load_object_number)));
					switch_num++;
				}
				if (GetType(load_object_number) == "wall")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Wall(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "floor")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "trampoline")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Trampoline(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "exit")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Exit(GetPosition(load_object_number)));
				}
				if (GetType(load_object_number) == "portal1")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Portal1(GetPosition(load_object_number), portal_num));
					pl.SetLocation(GetPosition(load_object_number));
					pl.SetNum(portal_num);
					portal_location1.push_back(pl);
				}
				if (GetType(load_object_number) == "portal2")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Portal2(GetPosition(load_object_number), portal_num));
					pl.SetLocation(GetPosition(load_object_number));
					portal_location2.push_back(pl);
					++portal_num;
				}				
				if (GetType(load_object_number) == "room")//check type
				{
					room_num++;
					GetGSComponent<CS230::GameObjectManager>()->Add(new Room(GetPosition(load_object_number), room_num));
				}
				if (GetType(load_object_number) == "float_floor")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new FlatFloor(GetPosition(load_object_number)));
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
					GetGSComponent<CS230::GameObjectManager>()->Add(new Box(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "button")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Button(GetPosition(temp_load_object_number)));
					button_num++;
				}
				if (GetType(temp_load_object_number) == "lever")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Lever(GetPosition(temp_load_object_number)));
					switch_num++;
				}
				if (GetType(temp_load_object_number) == "wall")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Wall(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "floor")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Floor(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "trampoline")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Trampoline(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "exit")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Exit(GetPosition(temp_load_object_number)));
				}
				if (GetType(temp_load_object_number) == "portal1")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Portal1(GetPosition(temp_load_object_number), portal_num));
					pl.SetLocation(GetPosition(temp_load_object_number));
					pl.SetNum(portal_num);
					portal_location1.push_back(pl);
				}
				if (GetType(temp_load_object_number) == "portal2")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new Portal2(GetPosition(temp_load_object_number), portal_num));
					pl.SetLocation(GetPosition(temp_load_object_number));
					portal_location2.push_back(pl);
					++portal_num;
				}
				if (GetType(temp_load_object_number) == "room")//check type
				{
					room_num++;
					GetGSComponent<CS230::GameObjectManager>()->Add(new Room(GetPosition(temp_load_object_number), room_num));
				}
				if (GetType(temp_load_object_number) == "float_floor")//check type
				{
					GetGSComponent<CS230::GameObjectManager>()->Add(new FlatFloor(GetPosition(temp_load_object_number)));
				}
			}
			temp_load_object_number++;
		}
	}
	GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 0, -200, 0 }, 1));
	GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 0, 900, 0 }, 1));
	GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ -200, 0, 0 }, 2));
	GetGSComponent<CS230::GameObjectManager>()->Add(new Outskirts({ 1600, 0, 0 }, 2));

	on_exit = false;

}

void Map::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Nine)) {
		dt = dt * 0.1;
	}
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
	GetGSComponent<CS230::Camera>()->Update(player_ptr->GetPosition());
	/*
	if (dimension.GetDimension() == Dimension::Side)
	{
		GetGSComponent<CS230::Camera>()->Update({ player_ptr->GetPosition().x, player_ptr->GetPosition().z});
	}
	else
	{
		GetGSComponent<CS230::Camera>()->Update({ player_ptr->GetPosition().x, player_ptr->GetPosition().y });
	}*/
	
	/*
	if (room == 2) {
		if (!static_cast<Button*>(gameobjectmanager.collision_objects[2])->press && player_ptr->GetPosition().x > Engine::GetWindow().GetSize().x - 200.0) {
			player_ptr->SetPosition({ Engine::GetWindow().GetSize().x - 200.0, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
		}
	}
	*/
	//player_ptr->GetPosition().x > Engine::GetWindow().GetSize().x && 
	if (room < 5&& Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		room++;
		Unload();
		Load();
	}
	//player_ptr->GetPosition().x < 0 && 
	else if (room > 1&& Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
		room--;	
		Unload();
		Load();
		//player_ptr->SetPosition({ (double)Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
	}
	/*
	else if (player_ptr->GetPosition().x < 0 && room <= 1) {
		player_ptr->SetPosition({ 0, player_ptr->GetPosition().y, player_ptr->GetPosition().z});
	}
	else if (player_ptr->GetPosition().x >= Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x && room >= 5) {
		player_ptr->SetPosition({ (double)Engine::GetWindow().GetSize().x - player_ptr->side_sprite.texture->GetSize().x, player_ptr->GetPosition().y, player_ptr->GetPosition().z });
	}
	*/
	/*
	if (dimension.GetDimension() == Dimension::Side)
	{
		std::cout << "Side" << std::endl;
	}
	else
	{
		std::cout << "Top" << std::endl;
	}
	*/

	if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::R))
	{
		GetGSComponent<CS230::GameObjectManager>()->Unload();
		Engine::GetGameStateManager().ReloadGameState();
	}
	collsion_num = GetGSComponent<CS230::GameObjectManager>()->BoxCollisionTest();
	if (on_exit && collsion_num==button_num&&switch_num==switch_pressed&& room_moving_available)
	{
		room++;
		room_moving_available = false;
		Unload();
		Load();
	}
	std::cout << switch_num << ", " << switch_pressed << std::endl;
	std::cout << collsion_num << ", " << button_num << std::endl;
	std::cout << room << std::endl;
	//fix it with next room's starting position
	UpdateMusicStream(backgroundMusic);

}

void Map::Draw() {
	Engine::GetWindow().Clear(0x000000FF);
	Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();

	GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(GetGSComponent<CS230::Camera>()->GetMatrix());
}

void Map::Unload() {
	GetGSComponent<Background>()->Unload();
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
	//background = nullptr;
	player_ptr = nullptr;
	button_num = 0;
	portal_num = 0;
	UnloadMusicStream(backgroundMusic);
}

void Map::ExitCheck()
{
	on_exit = true;
}

void Map::BoxCollisionNum(int value)
{
	collsion_num = value;
}

std::vector<PortalLocation> Map::GivePortal1()
{
	return portal_location1; 
}
std::vector<PortalLocation> Map::GivePortal2()
{
	return portal_location2; 
}
void Map::SwitchNumIncrease() { switch_pressed++; }
