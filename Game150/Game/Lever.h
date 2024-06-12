#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Lever : public CS230::GameObject {
public:
	Lever(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Lever; }
	std::string TypeName() override { return "Lever"; }
	//virtual void ResolveCollision(GameObject* other_object) override;
	bool CanCollideWith(GameObjectTypes);
	bool HasBeenPressed();
	void Pressed();
private:
	CurrentDimension dimension;
	bool is_pressing;
	enum class Animations {
		Side,
		Top,
		WorkSide,
		WorkTop
	};
};
