/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.cpp
Project:    CS230 Engine
Author:     Huiuk Jang
Created:    May 1, 2024
*/
#include "Collision.h"
#include "ShowCollision.h"
CS230::GameObject::GameObject(Math::vec3 position) :
    GameObject(position, 0, { 1, 1 })
{
    current_state = &state_none;
    current_state->Enter(this);
}

CS230::GameObject::GameObject(Math::vec3 position, double rotation, Math::vec2 scale) :
    velocity({ 0,0, 0 }),
    position(position),
    scale(scale),
    rotation(rotation),
    current_state(&state_none)
{}
//Lets Change
void CS230::GameObject::Draw(Math::TransformationMatrix camera_matrix) {
    Sprite* sprite = GetGOComponent<Sprite>();
    if (sprite != nullptr) {
        sprite->Draw(GetMatrix() ); //camera_matrix * //GetMatrix());//matrix.ChangeDimension(GetMatrix(), dimension.GetDimension())
        //sprite->Draw(camera_matrix * matrix.ChangeDimension(GetMatrix(), dimension.GetDimension()));
        /*
        std::cout << "\n" << std::endl;
        std::cout << GetMatrix()[0][0]<< " "<< GetMatrix()[1][0]<<" "<< GetMatrix()[2][0]<< " " << GetMatrix()[3][0] << std::endl;
        std::cout << GetMatrix()[0][1] << " " << GetMatrix()[1][1] << " " << GetMatrix()[2][1] << " " << GetMatrix()[3][1] << std::endl;
        std::cout << GetMatrix()[0][2] << " " << GetMatrix()[1][2] << " " << GetMatrix()[2][2] << " " << GetMatrix()[3][2] << std::endl;
        std::cout << GetMatrix()[0][3] << " " << GetMatrix()[1][3] << " " << GetMatrix()[2][3] << " " << GetMatrix()[3][3] << std::endl;
        std::cout << "\n" << std::endl;
        
        std::cout << "\n" << std::endl;
        std::cout << camera_matrix[0][0] << " " << camera_matrix[1][0] << " " << camera_matrix[2][0] << " " << camera_matrix[3][0] << std::endl;
        std::cout << camera_matrix[0][1] << " " << camera_matrix[1][1] << " " << camera_matrix[2][1] << " " << camera_matrix[3][1] << std::endl;
        std::cout << camera_matrix[0][2] << " " << camera_matrix[1][2] << " " << camera_matrix[2][2] << " " << camera_matrix[3][2] << std::endl;
        std::cout << camera_matrix[0][3] << " " << camera_matrix[1][3] << " " << camera_matrix[2][3] << " " << camera_matrix[3][3] << std::endl;
        std::cout << "\n" << std::endl;
        */
    }
    /*
    CubeCollision* cubecollision = GetGOComponent<CubeCollision>();
    ShowCollision* showcollision = Engine::GetGameStateManager().GetGSComponent<ShowCollision>();
    if (showcollision != nullptr && showcollision->Enabled())
    {
        if (cubecollision != nullptr) {
            cubecollision->Draw(camera_matrix);
        }
    }

    Collision* collision = GetGOComponent<Collision>();
    if (collision != nullptr && Engine::GetGameStateManager().GetGSComponent<CS230::ShowCollision>()->Enabled()) {
        collision->Draw(camera_matrix);
    }
    */
}


const Math::TransformationMatrix& CS230::GameObject::GetMatrix() {
    if (matrix_outdated)
    {
        object_matrix = Math::TranslationMatrix(position) * Math::RotationMatrix(rotation);// * Math::ScaleMatrix(scale);
        matrix_outdated = false;
    }

    return object_matrix;
}//Rotation Matrix error

const Math::vec3& CS230::GameObject::GetPosition() const
{
    return position;
}
const Math::vec3& CS230::GameObject::GetVelocity() const
{
    return velocity;
}
const Math::vec2& CS230::GameObject::GetScale() const
{
    return scale;
}
double CS230::GameObject::GetRotation() const
{
    return rotation;
}



void CS230::GameObject::SetPosition(Math::vec3 new_position) {
    position = new_position;
    matrix_outdated = true;
}

void CS230::GameObject::UpdatePosition(Math::vec3 delta) {
    position += delta;
    matrix_outdated = true;
}

void CS230::GameObject::SetVelocity(Math::vec3 new_velocity)
{
    velocity = new_velocity;
    matrix_outdated = true;
}
void CS230::GameObject::UpdateVelocity(Math::vec3 delta)
{
    velocity += delta;
    matrix_outdated = true;
}
void CS230::GameObject::SetScale(Math::vec2 new_scale)
{
    scale = new_scale;
    matrix_outdated = true;
}
void CS230::GameObject::UpdateScale(Math::vec2 delta)
{
    scale += delta;
    matrix_outdated = true;
}
void CS230::GameObject::SetRotation(double new_rotation)
{
    rotation = new_rotation;
    matrix_outdated = true;
}
void CS230::GameObject::UpdateRotation(double delta)
{
    rotation += delta;
    matrix_outdated = true;
}

void CS230::GameObject::Update(double dt) {
    current_state->Update(this, dt);
    if (velocity.x != 0 || velocity.y != 0) {
        UpdatePosition(velocity * dt);
    }
    UpdateGOComponents(dt);
    current_state->CheckExit(this);
}

void CS230::GameObject::change_state(State* new_state) {
    current_state = new_state;
    current_state->Enter(this);
}


bool CS230::GameObject::IsCollidingWith(GameObject* other_object) {
    Collision* collider = GetGOComponent<Collision>();
    return collider != nullptr && collider->IsCollidingWith(other_object);
}

bool CS230::GameObject::CanCollideWith(GameObjectTypes other_object_type) {
    return false;
}
