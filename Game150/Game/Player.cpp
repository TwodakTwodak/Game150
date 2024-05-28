/*
File Name:  Player.cpp
Project:    Gam150 Engine
Author:     Seunghyeon Song
Created:    May 3, 2024
*/

#include "Player.h"
#include "../Engine/Engine.h"
#include "Map.h"
#include "../Engine/Collision.h"
#include "Gravity.h"


Player::Player(Math::vec3 start_position) : cool_timer(cool_time),
    GameObject(start_position)
{
    AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
    change_state(&state_idle);
    current_state->Enter(this);
}

void Player::Update(double dt) {
    GameObject::Update(dt);
    /*
    if (hurt_timer->Remaining() < 0)
    {
        hurt_timer->Reset();
        hurt_timer->Set(0);
    }
    */
    // Boundary Check

    Math::cube player_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
    /*
    if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + player_rect.Size().x / 2) {
        UpdatePosition({ -player_rect.Left(), 0, 0 });
        SetVelocity({ 0, GetVelocity().y, 0 });
    }
    if (GetPosition().x + player_rect.Size().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
        UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - player_rect.Right() , 0, 0 });
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    */
}

Math::ivec2 Player::GetSize()
{
    return GetGOComponent<CS230::Sprite>()->GetFrameSize();
}

void Player::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
    {
        UpdateVelocity({ xz_acceleration * dt, 0, 0 });
        if (GetVelocity().x > max_velocity)
        {
            SetVelocity({ max_velocity, GetVelocity().y, GetVelocity().z });
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left))
    {
        UpdateVelocity({ -xz_acceleration * dt, 0, 0 });
        if (GetVelocity().x < -max_velocity)
        {
            SetVelocity({ -max_velocity, GetVelocity().y, GetVelocity().z });
        }
    }
}

void Player::update_y_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right))
    {
        UpdateVelocity({ xz_acceleration * dt, 0, 0 });
        if (GetVelocity().x > max_velocity)
        {
            SetVelocity({ max_velocity, GetVelocity().y, GetVelocity().z });
        }
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left))
    {
        UpdateVelocity({ -xz_acceleration * dt, 0, 0 });
        if (GetVelocity().x < -max_velocity)
        {
            SetVelocity({ -max_velocity, GetVelocity().y, GetVelocity().z });
        }
    }
}

void Player::State_Jumping::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    player->SetVelocity({ player->GetVelocity().x, player->GetVelocity().y, Player::jump_velocity });
    player->standing_on = nullptr;
}
void Player::State_Jumping::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->UpdateVelocity({ 0, 0, -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    player->update_x_velocity(dt);
}
void Player::State_Jumping::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Up) == false) {
        player->change_state(&player->state_falling);
        player->SetVelocity({ player->GetVelocity().x, 0, 0 });
    }
    else if (player->GetVelocity().z <= 0) {
        player->change_state(&player->state_falling);
    }
}

void Player::State_Idle::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
}
void Player::State_Idle::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    (void)dt;
}
void Player::State_Idle::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::X))
    {
        player->change_state(&player->state_interacting);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)&& Dimension::Side ==player->dimension.GetDimension()) {
        player->change_state(&player->state_jumping);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Left_Shift) && Dimension::Top == player->dimension.GetDimension())
    {
        player->change_state(&player->state_dashing);
    }
}

void Player::State_Falling::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
}
void Player::State_Falling::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->UpdateVelocity({ 0, 0, -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue() * dt });
    player->update_x_velocity(dt);
}
void Player::State_Falling::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
}


void Player::State_Running::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (player->GetVelocity().x <= 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && player->GetScale().x > 0) {
        player->SetScale({ -player->GetScale().x, player->GetScale().y });
    }
    else if (player->GetVelocity().x >= 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && player->GetScale().x < 0)
    {
        player->SetScale({ -player->GetScale().x, player->GetScale().y });
    }

    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Running));
}
void Player::State_Running::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->update_x_velocity(dt);
    player->update_y_velocity(dt);
}
void Player::State_Running::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (player->GetVelocity().x == 0)
    {
        player->change_state(&player->state_idle);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Up)&& Dimension::Side == player->dimension.GetDimension())
    {
        player->change_state(&player->state_jumping);
    }
}


void Player::State_Dashing::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing));
    player->SetVelocity({ dash_velocity, player->GetVelocity().y, player->GetVelocity().z });
}
void Player::State_Dashing::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    //check time
}
void Player::State_Dashing::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    //if(time ended)
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::Right)) {
        player->change_state(&player->state_running);
    }
    else
    {
        player->change_state(&player->state_idle);
    }
    
}


void Player::State_Interacting::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Dashing));
    player->SetVelocity({ dash_velocity, player->GetVelocity().y, player->GetVelocity().z });
}
void Player::State_Interacting::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    (void)dt;
}
void Player::State_Interacting::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    //if(seeing paper ended, bool)
    player->change_state(&player->state_idle);

}


bool Player::CanCollideWith(GameObjectTypes) {
    return true;
}
void Player::ResolveCollision(GameObject* other_object)
{
    Math::cube player_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
    Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
    switch (other_object->Type())
    {
    case GameObjectTypes::Floor: [[fallthrough]];
    case GameObjectTypes::Box:
        
        break;
    case GameObjectTypes::Button:
    {
        break;
    }
    case GameObjectTypes::Portal:
    {
        //static_cast<Portal*>(other_object)->GoToState();
        break;
    }
    case GameObjectTypes::Switch:
    {
        break;
    }
    }
}

void Player::Draw(Math::TransformationMatrix camera_matrix) {
}