#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
class Box : public CS230::GameObject {
public:
	Box(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Box; }
	std::string TypeName() override { return "Robot"; }

};
