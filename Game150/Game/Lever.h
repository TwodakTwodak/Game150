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

	class Side : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Lever Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Lever Top"; }
	};

	Top top;

	class Work_Side : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Lever Work Side"; }
	};

	Work_Side work_side;

	class Work_Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Lever Work Top"; }
	};

	Work_Top work_top;
};
