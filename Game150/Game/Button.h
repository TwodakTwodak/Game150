#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Button : public CS230::GameObject {
public:
	Button(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Button; }
	std::string TypeName() override { return "Button"; }
	//virtual void ResolveCollision(GameObject* other_object) override;
	bool CanCollideWith(GameObjectTypes);
private:
	CurrentDimension dimension;
};
