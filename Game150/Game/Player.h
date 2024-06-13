/*
File Name:  Player.h
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/
#pragma once

#include "../Engine/Input.h"
#include "../Engine/Camera.h"
#include "../Engine/GameObjectManager.h"
#include "GameObjectTypes.h"
#include "../Engine/Timer.h"
#include "../Engine/Dimension.h"

struct key_order {
	bool press;
};

class Player : public CS230::GameObject {
public:
	Player(Math::vec3 start_position);
	void Update(double dt) override;
    const Math::vec3& GetPosition() const { return GameObject::GetPosition(); }
    Math::ivec2 GetSize();
    GameObjectTypes Type() override { return GameObjectTypes::Player; }
    std::string TypeName() override { return "Player"; }
    bool CanCollideWith(GameObjectTypes);
    virtual void ResolveCollision(GameObject* other_object) override;
    //void Draw(Math::TransformationMatrix camera_matrix) override;
    bool StateDelivery();
    void BoxWallChange(bool change);
    GameObject* StandingOn() { return standing_on; }
    void SetStandingOn(GameObject* current_state);
private:
    CurrentDimension dimension;
    Math::TransformationMatrix matrix;

	//static constexpr double xz_acceleration = 100;
	static constexpr double max_velocity = 10;
	static constexpr double jump_velocity =350;
	static constexpr double dash_velocity = 100;
	static constexpr double cool_time = 1.5;
	bool jumping = false;
	bool falling = false;
	double dash_start_pos;
	bool gravi = true;
	bool key_order[4];
	double cool_timer;
    int dash_timer;
    double floor = 200;

	void move(double dt);

    void update_x_velocity(double dt);
    void update_y_velocity(double dt);

    class State_Idle : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Idle state_idle;

    class State_Jumping : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Jumping"; }
    };

    State_Jumping state_jumping;

    class State_Dashing : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Dashing"; }
    };

    State_Dashing state_dashing;

    class State_Falling : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Falling state_falling;


    class State_Walking : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State_Walking state_walking;




    class State_Idle_Top : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Idle"; }
    };

    State_Idle_Top state_idle_top;
    

    
    class State_Falling_Top : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Falling"; }
    };

    State_Falling_Top state_falling_top;


    class State_Walking_Top : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Running"; }
    };

    State_Walking_Top state_walking_top;

    enum class Animations {
        Idle,
        Walking,
        Jumping,
        Falling,
        TopIdle,
        TopWalking,
        TopFalling,
        Dashing,
    };

    static constexpr double hurt_time = 2.0;
    static constexpr double hurt_velocity = 350;
    static constexpr double hurt_acceleration = 300;

    CS230::Timer* hurt_timer;

    GameObject* standing_on;
    
    bool portal_available;
    bool is_portal_available;
    
    static constexpr double trampoline_velocity = 650;
    bool on_trampoline = false;
    bool not_did = true;
};
