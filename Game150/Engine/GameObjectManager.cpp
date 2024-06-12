/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObjectManager.cpp
Project:    CS230 Engine
Author:     Huiuk Jang
Created:    May 1, 2024
*/
#include "GameObjectManager.h"
#include "../Game/GameObjectTypes.h"
#include "../Game/Map.h"
#include "../Game/Player.h"

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}
void CS230::GameObjectManager::Unload()
{
	for (GameObject* object : objects)
	{
		delete object;
	}
	objects.clear();
}
void CS230::GameObjectManager::UpdateAll(double dt)
{
	CollisionTest();
	for (GameObject* object : objects)
	{
		object->Update(dt);
	}
}
void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionTest() {
	Engine::GetGameStateManager().GetGSComponent<Player>()->BoxWallChange(false);
	for (GameObject* object_1 : objects) {
		for (GameObject* object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());

					if ((object_1->Type() == GameObjectTypes::Wall && object_2->Type() == GameObjectTypes::Box) ||
						(object_2->Type() == GameObjectTypes::Wall && object_1->Type() == GameObjectTypes::Box)) {
						Engine::GetGameStateManager().GetGSComponent<Player>()->BoxWallChange(true);
					}
					if ((object_1->Type() == GameObjectTypes::Outskirts && object_2->Type() == GameObjectTypes::Box) ||
						(object_2->Type() == GameObjectTypes::Outskirts && object_1->Type() == GameObjectTypes::Box)) {
						Engine::GetGameStateManager().GetGSComponent<Player>()->BoxWallChange(true);
					}
				}
			}
		}
	}

	for (GameObject* object_1 : objects) {
		for (GameObject* object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());

					object_1->ResolveCollision(object_2);

				}
			}
		}
	}
}

int CS230::GameObjectManager::BoxCollisionTest()  {
	int collision_num = 0;
	for (GameObject* object_1 : objects) {
		for (GameObject* object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					if ((object_1->Type() == GameObjectTypes::Box && object_2->Type() == GameObjectTypes::Button)
						|| (object_2->Type() == GameObjectTypes::Box && object_1->Type() == GameObjectTypes::Button))
					{
						collision_num++;
					}
				}
			}
		}
	}
	return collision_num/2;
}