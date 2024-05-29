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




Map::Map() {
}

void Map::Load() {

	player_ptr = new Player({ 300, 300, 300 });
	//background = Engine::GetTextureManager().Load("Assets/Background.png");
	AddGSComponent(new CS230::GameObjectManager);
	GetGSComponent<CS230::GameObjectManager>()->Add(player_ptr);
	AddGSComponent(new CS230::Camera({ { 0.15 * Engine::GetWindow().GetSize().x, 0, 0 }, { 0.35 * Engine::GetWindow().GetSize().x, 0, 0 }}));
	GetGSComponent<CS230::Camera>()->SetPosition({ 0, 0, 0 });

	AddGSComponent(new Background);
	GetGSComponent<Background>()->Add("Assets/Background.png", 0);

	Math::icube cameraLimit = { { 0,0, 0 }, { GetGSComponent<Background>()->GetSize().x - Engine::GetWindow().GetSize().x , GetGSComponent<Background>()->GetSize().y - Engine::GetWindow().GetSize().y , GetGSComponent<Background>()->GetSize().y - Engine::GetWindow().GetSize().y}  };
	GetGSComponent<CS230::Camera>()->SetLimit(cameraLimit);
	
	/*gameobjectmanager.Add(new Crates({ 200, 400, 400 }));
	gameobjectmanager.Add(new Crates({ 400, floor, 300 }));
	gameobjectmanager.Add(new Crates({ 600, 80, 200 }));*/
	/*
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
	*/
}

void Map::Update([[maybe_unused]] double dt) {
	if (Engine::GetInput().KeyDown(CS230::Input::Keys::Nine)) {
		dt = dt * 0.1;
	}
	UpdateGSComponents(dt);
	GetGSComponent<CS230::GameObjectManager>()->UpdateAll(dt);
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
	if (room < 5|| Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)) {
		room++;
		Unload();
		Load();
	}
	//player_ptr->GetPosition().x < 0 && 
	else if (room > 1|| Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Down)) {
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
	player_ptr->SetPosition({ 0, 100, 100});
	if (dimension.GetDimension() == Dimension::Side)
	{
		std::cout << "Side" << std::endl;
	}
	else
	{
		std::cout << "Top" << std::endl;
	}
	
}

void Map::Draw() {
	Engine::GetWindow().Clear(0x00F0F0FF);
	//background->Draw(Math::TranslationMatrix(Math::vec2{0,0}));
	Math::TransformationMatrix camera_matrix = GetGSComponent<CS230::Camera>()->GetMatrix();

	//GetGSComponent<Background>()->Draw(*GetGSComponent<CS230::Camera>());
	GetGSComponent<CS230::GameObjectManager>()->DrawAll(GetGSComponent<CS230::Camera>()->GetMatrix());
}

void Map::Unload() {
	//GetGSComponent<Background>()->Unload();
	GetGSComponent<Background>()->Unload();
	GetGSComponent<CS230::GameObjectManager>()->Unload();
	ClearGSComponents();
	//background = nullptr;
	player_ptr = nullptr;
}