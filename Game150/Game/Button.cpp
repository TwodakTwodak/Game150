#include "Button.h"
#include "../Engine/Collision.h"
Button::Button(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Button.spt", this));
}
bool Button::CanCollideWith(GameObjectTypes)
{
    return true;
}