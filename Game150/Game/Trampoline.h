#pragma once
#include "..\Engine\GameObject.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Trampoline : public CS230::GameObject {
public:
	Trampoline(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Trampoline; }
	std::string TypeName() override { return "Trampoline"; }
	//virtual void ResolveCollision(GameObject* other_object) override;
	bool CanCollideWith(GameObjectTypes);
private:
	CurrentDimension dimension;
	enum class Animations {
		Side,
		Top
	};
	class Side : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Trampoline Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Trampoline Top"; }
	};

	Top top;
};
