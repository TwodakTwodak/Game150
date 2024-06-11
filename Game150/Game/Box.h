#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Box : public CS230::GameObject {
public:
	Box(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Box; }
	std::string TypeName() override { return "Box"; }
	virtual void ResolveCollision(GameObject* other_object) override;
	virtual void Update(double dt) override;
	bool WallCheck();
	bool CanCollideWith(GameObjectTypes);
private:
	CurrentDimension dimension;
	bool near_wall = false;
};
