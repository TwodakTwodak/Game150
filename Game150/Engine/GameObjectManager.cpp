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

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
}
void CS230::GameObjectManager::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		objects.erase(objects.begin() + i);
	}
	objects.clear();
}
void CS230::GameObjectManager::UpdateAll(double dt)
{
	CollisionTest();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt);
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
