#include "Portal.h"
#include "..\Engine\ComponentManager.h"
#include "..\Engine\Collision.h"
Portal1::Portal1(Math::vec3 position, int portal_num) : CS230::GameObject(position){
    AddGOComponent(new CS230::Sprite("Assets/Portal1.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

int Portal1::PortalNumber() {
    return portal_num;
}

Portal2::Portal2(Math::vec3 position, int portal_num) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Portal.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

int Portal2::PortalNumber() {
    return portal_num;
}

void Portal1::Side::Enter(GameObject* object) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    portal1->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Portal1::Side::Update(GameObject* object, double dt) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    //check time
}
void Portal1::Side::CheckExit(GameObject* object) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    if (Dimension::Top == portal1->dimension.GetDimension())
    {
        portal1->change_state(&portal1->top);
    }

}

void Portal1::Top::Enter(GameObject* object) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    portal1->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Portal1::Top::Update(GameObject* object, double dt) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    //check time
}
void Portal1::Top::CheckExit(GameObject* object) {
    Portal1* portal1 = static_cast<Portal1*>(object);
    if (Dimension::Side == portal1->dimension.GetDimension())
    {
        portal1->change_state(&portal1->side);
    }
}



void Portal2::Side::Enter(GameObject* object) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    portal2->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Portal2::Side::Update(GameObject* object, double dt) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    //check time
}
void Portal2::Side::CheckExit(GameObject* object) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    if (Dimension::Top == portal2->dimension.GetDimension())
    {
        portal2->change_state(&portal2->top);
    }

}

void Portal2::Top::Enter(GameObject* object) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    portal2->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Portal2::Top::Update(GameObject* object, double dt) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    //check time
}
void Portal2::Top::CheckExit(GameObject* object) {
    Portal2* portal2 = static_cast<Portal2*>(object);
    if (Dimension::Side == portal2->dimension.GetDimension())
    {
        portal2->change_state(&portal2->side);
    }

}