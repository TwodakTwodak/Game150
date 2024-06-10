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
#include <cmath>

Player::Player(Math::vec3 start_position) :
    GameObject(start_position)
{
    //AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
    AddGOComponent(new CS230::Sprite("Assets/Player.spt", this));
    change_state(&state_idle);
    current_state->Enter(this);
    GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));

}

void Player::Update(double dt) {
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Space))
    {
        if (dimension.GetDimension() == Dimension::Side)
        {
            dimension.SetDimension(Dimension::Top);
        }
        else
        {
            dimension.SetDimension(Dimension::Side);
        }
    }
    GameObject::Update(dt);
    /*
    if (hurt_timer->Remaining() < 0)
    {
        hurt_timer->Reset();
        hurt_timer->Set(0);
    }
    */
    // Boundary Check
    /*
    Math::cube player_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
    
    if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + player_rect.Size().x / 2) {
        UpdatePosition({ -player_rect.Left(), 0, 0 });
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    if (GetPosition().x + player_rect.Size().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
        UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - player_rect.Right() , 0, 0 });
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    if (GetPosition().y< Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + player_rect.Size().y / 2) {
        UpdatePosition({ 0, -player_rect.Bottom(), 0 });
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
    }
    if (GetPosition().y + player_rect.Size().y / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y) {
        UpdatePosition({ 0 , Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y-player_rect.Top(), 0 });
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
    }
    */
    //std::cout << player_rect.point_1.x << " " << player_rect.point_1.y << " "<<player_rect.point_1.z << std::endl;
}

Math::ivec2 Player::GetSize()
{
    return GetGOComponent<CS230::Sprite>()->GetFrameSize();
}

void Player::update_x_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::D))
    {
        SetVelocity({ max_velocity, 0, GetVelocity().z });

    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A))
    {
        SetVelocity({ -max_velocity, 0, GetVelocity().z });
    }
}

void Player::update_y_velocity(double dt) {
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W))
    {
        SetVelocity({ 0, max_velocity, GetVelocity().z });
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S))
    {
        SetVelocity({ 0, -max_velocity, GetVelocity().z });
    }
}
void Player::move(double dt)
{
    if ((Dimension::Top == dimension.GetDimension()))
    {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::D))
        {
            SetVelocity({ max_velocity, 0, GetVelocity().z });
        }
        else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A))
        {
            SetVelocity({ -max_velocity, 0, GetVelocity().z });
        }
        else if (Engine::GetInput().KeyDown(CS230::Input::Keys::W))
        {
            SetVelocity({ 0, max_velocity, GetVelocity().z });
        }
        else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S))
        {
            SetVelocity({ 0, -max_velocity, GetVelocity().z });
        }
    }
    else
    {
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::D))
        {
            SetVelocity({ max_velocity, 0, GetVelocity().z });
        }
        else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A))
        {
            SetVelocity({ -max_velocity, 0, GetVelocity().z });
        }
    }
}

void Player::State_Jumping::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Jumping));
    player->SetVelocity({ player->GetVelocity().x, player->GetVelocity().y, Player::jump_velocity*0.1 });
    player->standing_on = nullptr;
}
void Player::State_Jumping::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->UpdateVelocity({ 0, 0, 1 * dt });// -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue()
    player->update_x_velocity(dt);
}
void Player::State_Jumping::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::W) == false) {
        player->change_state(&player->state_falling);
        player->SetVelocity({ player->GetVelocity().x, 0, 0 });
    }
    else if (player->GetVelocity().z <= 0) {
        player->change_state(&player->state_falling);
    }
}

void Player::State_Idle::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (player->dimension.GetDimension() == Dimension::Side) {
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
    }
    else{
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::TopIdle));
    }
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
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::W) && Dimension::Top == player->dimension.GetDimension()) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::S) && Dimension::Top == player->dimension.GetDimension()) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W)&& Dimension::Side ==player->dimension.GetDimension()) {
        player->change_state(&player->state_jumping);
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Left_Shift) && Dimension::Top == player->dimension.GetDimension())
    {
        player->change_state(&player->state_dashing);
    }
}

void Player::State_Falling::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (player->dimension.GetDimension() == Dimension::Side) {
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Falling));
    }
    else {
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::TopFalling));
    }
}
void Player::State_Falling::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->UpdateVelocity({ 0, 0, -Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue()*0.005 });//-Engine::GetGameStateManager().GetGSComponent<Gravity>()->GetValue()
    player->update_x_velocity(dt);
}
void Player::State_Falling::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    //later, make floor and make collsion to get out of this state
    if (player->standing_on != nullptr)
    {
        player->SetVelocity({ player->GetVelocity().x, player->GetVelocity().y, 0 });
        //player->SetPosition({ player->GetPosition().x, player->GetPosition().y, player->floor });
        if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
            player->change_state(&player->state_running);
            player->SetVelocity({ player->GetVelocity().x, player->GetVelocity().y, 0 });
        }
        else if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
            player->change_state(&player->state_running);
            player->SetVelocity({ player->GetVelocity().x, player->GetVelocity().y, 0 });
        }
        else
        {
            player->change_state(&player->state_idle);
            player->SetVelocity({ 0, player->GetVelocity().y, 0 });
        }
    }
    
}


void Player::State_Walking::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    if (player->GetVelocity().x <= 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Left) && player->GetScale().x > 0)
    {
        player->SetScale({ -player->GetScale().x, player->GetScale().y });
    }
    else if (player->GetVelocity().x >= 0 && Engine::GetInput().KeyDown(CS230::Input::Keys::Right) && player->GetScale().x < 0)
    {
        player->SetScale({ -player->GetScale().x, player->GetScale().y });
    }
    if (player->dimension.GetDimension() == Dimension::Side) {
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Walking));
    }
    else {
        player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::TopWalking));
    }
}
void Player::State_Walking::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    player->move(dt);
    
    //std::cout << "Updating Walking" << std::endl;
}
void Player::State_Walking::CheckExit(GameObject* object) {
    //std::cout << "Check Exit Walking" << std::endl;
    Player* player = static_cast<Player*>(object);

    bool isMovingX = (Engine::GetInput().KeyDown(CS230::Input::Keys::D) && player->GetVelocity().x > 0) ||
        (Engine::GetInput().KeyDown(CS230::Input::Keys::A) && player->GetVelocity().x < 0);

    bool isMovingY = (Engine::GetInput().KeyDown(CS230::Input::Keys::W) && player->GetVelocity().y > 0) ||
        (Engine::GetInput().KeyDown(CS230::Input::Keys::S) && player->GetVelocity().y < 0);

    if (!isMovingX&& !isMovingY) {
        player->SetVelocity({ 0, 0, player->GetVelocity().z });
        player->change_state(&player->state_idle);
    }
    else if (Dimension::Top == player->dimension.GetDimension()) {
        if (!isMovingY && !isMovingX)
        {
            player->SetVelocity({ 0, 0, player->GetVelocity().z });
            player->change_state(&player->state_idle);
        }
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::W) && Dimension::Side == player->dimension.GetDimension()) {
        player->change_state(&player->state_jumping);
    }

    if (player->standing_on != nullptr && !player->standing_on->IsCollidingWith(player)) {
        player->standing_on = nullptr;
        player->change_state(&player->state_falling);
    }
}
void Player::State_Dashing::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::TopDashing));
    player->SetVelocity({ dash_velocity, player->GetVelocity().y, player->GetVelocity().z });
}
void Player::State_Dashing::Update(GameObject* object, double dt) {
    Player* player = static_cast<Player*>(object);
    //check time
}
void Player::State_Dashing::CheckExit(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    //if(time ended)
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::A)) {
        player->change_state(&player->state_running);
    }
    else if (Engine::GetInput().KeyDown(CS230::Input::Keys::D)) {
        player->change_state(&player->state_running);
    }
    else
    {
        player->change_state(&player->state_idle);
    }
    
}


void Player::State_Interacting::Enter(GameObject* object) {
    Player* player = static_cast<Player*>(object);
    player->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Idle));
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
    {

        if (current_state == &state_falling) {
            if (player_rect.High() > other_rect.High()) {
                standing_on = other_object;
                SetPosition({ GetPosition().x, GetPosition().y, other_rect.High() });
                current_state->CheckExit(this);
                return;
            }
        }
        if (dimension.GetDimension() == Dimension::Side)
        {
            if (player_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ (other_rect.Left() - player_rect.Right()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - player_rect.Left()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
        }
        else
        {
            double left_right = std::min(abs(player_rect.Left() - other_rect.Right()), abs(other_rect.Left() - player_rect.Right()));
            double top_bottom = std::min(abs(player_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - player_rect.Bottom()));
            if (left_right < top_bottom)
            {
                if (player_rect.Left() < other_rect.Left()) {
                    UpdatePosition(Math::vec3{ (other_rect.Left() - player_rect.Right()), 0.0, 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
                else {
                    UpdatePosition(Math::vec3{ (other_rect.Right() - player_rect.Left()), 0.0, 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
            }
            else
            {
                if (player_rect.Top() < other_rect.Top()) {
                    UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - player_rect.Top()), 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
                else {
                    UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - player_rect.Bottom()), 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
            }
        }
        break;
    }
    case GameObjectTypes::Wall: 
    {
        if (current_state == &state_falling) {
            if (player_rect.High() > other_rect.High()) {
                SetPosition({ GetPosition().x, GetPosition().y, other_rect.High() });
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
        if (dimension.GetDimension() == Dimension::Side)
        {
            if (player_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ (other_rect.Left() - player_rect.Right()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - player_rect.Left()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
        }
        else
        {
            double left_right = std::min(abs(player_rect.Left() - other_rect.Right()), abs(other_rect.Left() - player_rect.Right()));
            double top_bottom = std::min(abs(player_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - player_rect.Bottom()));
            if (left_right < top_bottom)
            {
                if (player_rect.Left() < other_rect.Left()) {
                    UpdatePosition(Math::vec3{ (other_rect.Left() - player_rect.Right()), 0.0, 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
                else {
                    UpdatePosition(Math::vec3{ (other_rect.Right() - player_rect.Left()), 0.0, 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
            }
            else
            {
                if (player_rect.Top() < other_rect.Top()) {
                    UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - player_rect.Top()), 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
                else {
                    UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - player_rect.Bottom()), 0.0 });
                    SetVelocity({ 0, 0, GetVelocity().z });
                }
            }
        }
        break;
    }
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
        if (current_state == &state_falling) {
            if (player_rect.High() > other_rect.High()) {
                SetPosition({ GetPosition().x, GetPosition().y, other_rect.High() });
                standing_on = other_object;
                current_state->CheckExit(this);
                return;
            }
        }
        break;
    }
    }
}
/*
void Player::Draw(Math::TransformationMatrix camera_matrix) {

    //GetGOComponent<CS230::Sprite>()->Draw(camera_matrix * GetMatrix());
    //GetGOComponent<CS230::Sprite>()->Draw(camera_matrix * matrix.ChangeDimension(GetMatrix(), dimension.GetDimension()));
    //sprite->Draw(camera_matrix * matrix.ChangeDimension(GetMatrix(), dimension.GetDimension()));
}*/