#include "Lever.h"
#include "../Engine/Collision.h"
Lever::Lever(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Lever.spt", this));
    is_pressing = false;
}
bool Lever::CanCollideWith(GameObjectTypes)
{
    return true;
}
bool Lever::HasBeenPressed() { return is_pressing; }
void Lever::Pressed() { is_pressing = true; }