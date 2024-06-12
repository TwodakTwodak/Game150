#include "Trampoline.h"
#include "../Engine/Collision.h"
Trampoline::Trampoline(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Trampoline.spt", this));
    change_state(&side);
    current_state->Enter(this);
}
bool Trampoline::CanCollideWith(GameObjectTypes)
{
    return true;
}
void Trampoline::Side::Enter(GameObject* object) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    trampoline->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Trampoline::Side::Update(GameObject* object, double dt) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    //check time
}
void Trampoline::Side::CheckExit(GameObject* object) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    if (Dimension::Top == trampoline->dimension.GetDimension())
    {
        trampoline->change_state(&trampoline->top);
    }

}

void Trampoline::Top::Enter(GameObject* object) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    trampoline->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Trampoline::Top::Update(GameObject* object, double dt) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    //check time
}
void Trampoline::Top::CheckExit(GameObject* object) {
    Trampoline* trampoline = static_cast<Trampoline*>(object);
    if (Dimension::Side == trampoline->dimension.GetDimension())
    {
        trampoline->change_state(&trampoline->side);
    }

}