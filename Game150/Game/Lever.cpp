#include "Lever.h"
#include "../Engine/Collision.h"
Lever::Lever(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Lever.spt", this));
    is_pressing = false;
    change_state(&side);
    current_state->Enter(this);
}
bool Lever::CanCollideWith(GameObjectTypes)
{
    return true;
}
bool Lever::HasBeenPressed() { return is_pressing; }
void Lever::Pressed() { is_pressing = true; }

void Lever::Side::Enter(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    lever->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Lever::Side::Update(GameObject* object, double dt) {
    Lever* lever = static_cast<Lever*>(object);
    //check time
}
void Lever::Side::CheckExit(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    if (Dimension::Top == lever->dimension.GetDimension())
    {
        lever->change_state(&lever->top);
    }
    if (lever->is_pressing)
    {
        lever->change_state(&lever->work_side);
    }
}

void Lever::Top::Enter(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    lever->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Lever::Top::Update(GameObject* object, double dt) {
    Lever* lever = static_cast<Lever*>(object);
    //check time
}
void Lever::Top::CheckExit(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    if (Dimension::Side == lever->dimension.GetDimension())
    {
        lever->change_state(&lever->side);
    }
    if (lever->is_pressing)
    {
        lever->change_state(&lever->work_top);
    }
}


void Lever::Work_Side::Enter(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    lever->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::WorkSide));
}
void Lever::Work_Side::Update(GameObject* object, double dt) {
    Lever* lever = static_cast<Lever*>(object);
    //check time
}
void Lever::Work_Side::CheckExit(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    if (Dimension::Top == lever->dimension.GetDimension())
    {
        lever->change_state(&lever->work_top);
    }

}

void Lever::Work_Top::Enter(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    lever->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::WorkTop));
}
void Lever::Work_Top::Update(GameObject* object, double dt) {
    Lever* lever = static_cast<Lever*>(object);
    //check time
}
void Lever::Work_Top::CheckExit(GameObject* object) {
    Lever* lever = static_cast<Lever*>(object);
    if (Dimension::Side == lever->dimension.GetDimension())
    {
        lever->change_state(&lever->work_side);
    }

}