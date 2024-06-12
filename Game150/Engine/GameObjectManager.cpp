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

void CS230::GameObjectManager::Add(GameObject* object)
{
	objects.push_back(object);
	draw_objects.push_back(object);
}
void CS230::GameObjectManager::Unload()
{
	for (GameObject* object : objects)
	{
		delete object;
	}
	objects.clear();
	draw_objects.clear();
}
void CS230::GameObjectManager::UpdateAll(double dt)
{
	CollisionTest();
	for (GameObject* object : objects)
	{
		object->Update(dt);
	}

	if (dimension.GetDimension() == Dimension::Side) {
		std::sort(std::begin(draw_objects), std::end(draw_objects),
			[](auto lhs, auto rhs) {
				return lhs->GetPosition().y > rhs->GetPosition().y;
			});
	}else {
		std::sort(std::begin(draw_objects), std::end(draw_objects),
			[](auto lhs, auto rhs) {
				return lhs->GetPosition().z < rhs->GetPosition().z;
			});
	}
	
}
void CS230::GameObjectManager::DrawAll(Math::TransformationMatrix camera_matrix)
{
	for (int i = 0; i < draw_objects.size(); i++)
	{
		draw_objects[i]->Draw(camera_matrix);
	}
}

void CS230::GameObjectManager::CollisionTest() {
	bool box_wall = false;
	for (GameObject* object_1 : objects) {
		for (GameObject* object_2 : objects) {
			if (object_1 != object_2 && object_1->CanCollideWith(object_2->Type())) {
				if (object_1->IsCollidingWith(object_2)) {
					Engine::GetLogger().LogEvent("Collision Detected: " + object_1->TypeName() + " and " + object_2->TypeName());

					if ((object_1->Type() == GameObjectTypes::Wall && object_2->Type() == GameObjectTypes::Box) ||
						(object_2->Type() == GameObjectTypes::Wall && object_1->Type() == GameObjectTypes::Box)) {
						box_wall = true;

						if (object_1->Type() == GameObjectTypes::Box) {
							object_1->ResolveCollision(object_2); 
						}
						else {
							object_2->ResolveCollision(object_1); 
						}
					}
					else if (object_1->Type() == GameObjectTypes::Player && object_2->Type() == GameObjectTypes::Box) {
						if (!box_wall) {
							object_2->ResolveCollision(object_1); 
						}
						else {
							object_1->ResolveCollision(object_2); 
						}
					}
					else if (object_2->Type() == GameObjectTypes::Player && object_1->Type() == GameObjectTypes::Box) {
						if (!box_wall) {
							object_1->ResolveCollision(object_2); 
						}
						else {
							object_2->ResolveCollision(object_1); 
						}
					}
					else {
						object_1->ResolveCollision(object_2); 
					}

					if (object_1->Type() == GameObjectTypes::Box || object_2->Type() == GameObjectTypes::Box) {
						box_wall = false;
					}

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