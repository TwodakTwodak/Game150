#include "Button.h"
#include "../Engine/Collision.h"
Button::Button(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Button.spt", this));
    change_state(&side);
    current_state->Enter(this);
}
bool Button::CanCollideWith(GameObjectTypes)
{
    return true;
}
void Button::Side::Enter(GameObject* object) {
    Button* button = static_cast<Button*>(object);
    button->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Button::Side::Update(GameObject* object, double dt) {
    Button* button = static_cast<Button*>(object);
    //check time
}
void Button::Side::CheckExit(GameObject* object) {
    Button* button = static_cast<Button*>(object);
    if (Dimension::Top == button->dimension.GetDimension())
    {
        button->change_state(&button->top);
    }

}

void Button::Top::Enter(GameObject* object) {
    Button* button = static_cast<Button*>(object);
    button->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Button::Top::Update(GameObject* object, double dt) {
    Button* button = static_cast<Button*>(object);
    //check time
}
void Button::Top::CheckExit(GameObject* object) {
    Button* button = static_cast<Button*>(object);
    if (Dimension::Side == button->dimension.GetDimension())
    {
        button->change_state(&button->side);
    }

}