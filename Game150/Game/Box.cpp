#include "Box.h"
#include "../Engine/Collision.h"
Box::Box(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Box.spt", this));
}
