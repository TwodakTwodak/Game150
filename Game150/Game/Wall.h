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
		std::string GetName() override { return "Wall Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Wall Top"; }
	};

	Top top;
};

class Wall_long : public CS230::GameObject {
public:
	Wall_long(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Wall_long; }
	std::string TypeName() override { return "Wall_long"; }
	virtual void ResolveCollision(GameObject* other_object) override;
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
		std::string GetName() override { return "Wall-long-Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Wall-long-Top"; }
	};

	Top top;
};

class Wall_long_horizon : public CS230::GameObject {
public:
	Wall_long_horizon(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::Wall_long_horizon; }
	std::string TypeName() override { return "Wall-long-horizon"; }
	virtual void ResolveCollision(GameObject* other_object) override;
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
		std::string GetName() override { return "Wall-long-horizo-Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Wall-long-horizo-Top"; }
	};

	Top top;
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
	enum class Animations {
		Side,
		Top
	};
	class Side : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Floor Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "Floor Top"; }
	};

	Top top;
};

class FlatFloor : public CS230::GameObject {
public:
	FlatFloor(Math::vec3 position);
	GameObjectTypes Type() override { return GameObjectTypes::FlatFloor; }
	std::string TypeName() override { return "FlatFloor"; }
	virtual void ResolveCollision(GameObject* other_object) override;
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
		std::string GetName() override { return "FlatFloor Side"; }
	};

	Side side;

	class Top : public State {
	public:
		virtual void Enter(GameObject* object) override;
		virtual void Update(GameObject* object, double dt) override;
		virtual void CheckExit(GameObject* object) override;
		std::string GetName() override { return "FlatFloor Top"; }
	};

	Top top;
};

//class VerticFloor : public CS230::GameObject {
//public:
//	VerticFloor(Math::vec3 position);
//	GameObjectTypes Type() override { return GameObjectTypes::FlatFloor; }
//	std::string TypeName() override { return "VerticFloor"; }
//	virtual void ResolveCollision(GameObject* other_object) override;
//	bool CanCollideWith(GameObjectTypes);
//private:
//	CurrentDimension dimension;
//	enum class Animations {
//		Side,
//		Top
//	};
//	class Side : public State {
//	public:
//		virtual void Enter(GameObject* object) override;
//		virtual void Update(GameObject* object, double dt) override;
//		virtual void CheckExit(GameObject* object) override;
//		std::string GetName() override { return "VerticFloor Side"; }
//	};
//
//	Side side;
//
//	class Top : public State {
//	public:
//		virtual void Enter(GameObject* object) override;
//		virtual void Update(GameObject* object, double dt) override;
//		virtual void CheckExit(GameObject* object) override;
//		std::string GetName() override { return "VerticFloor Top"; }
//	};
//
//	Top top;
//};