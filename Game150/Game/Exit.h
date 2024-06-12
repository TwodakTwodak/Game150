#pragma once
#include "..\Engine\GameObjectManager.h"
#include "GameObjectTypes.h"
#include "../Engine/Dimension.h"
class Exit : public CS230::GameObject {
public:
    Exit(Math::vec3 position);
    std::string TypeName() override { return "Exit"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Exit; }

    void GoToState();
private:
    int to_state;
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
		std::string GetName() override { return "Exit Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Exit Top"; }
	};

	Top top;
};
