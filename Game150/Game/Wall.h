#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Wall : public CS230::GameObject {
public:
	Wall(Math::vec3 position, int size);
	GameObjectTypes Type() override { return GameObjectTypes::Wall; }
	std::string TypeName() override { return "Wall"; }
	virtual void ResolveCollision(GameObject* other_object) override;
private:
	CurrentDimension dimension;
};
