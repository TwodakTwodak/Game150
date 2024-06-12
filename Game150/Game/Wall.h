#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Wall : public CS230::GameObject {
public:
	Wall(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Wall; }
	std::string TypeName() override { return "Wall"; }
	virtual void ResolveCollision(GameObject* other_object) override;
private:
	CurrentDimension dimension;
	enum class Animations {
		Side,
		Top
	};
};

class Outskirts : public CS230::GameObject {
public:
	Outskirts(Math::vec3 position, int size);
	GameObjectTypes Type() override { return GameObjectTypes::Outskirts; }
	std::string TypeName() override { return "Outskirts"; }
	virtual void ResolveCollision(GameObject* other_object) override;

private:
	CurrentDimension dimension;
};

class Floor : public CS230::GameObject {
public:
	Floor(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Floor; }
	std::string TypeName() override { return "Floor"; }
	virtual void ResolveCollision(GameObject* other_object) override;
private:
	CurrentDimension dimension;
};
