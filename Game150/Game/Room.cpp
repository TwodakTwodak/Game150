#include "Room.h"

Room::Room(Math::vec3 position) : GameObject(position)
{
    AddGOComponent(new CS230::Sprite("Assets/Room.spt", this));
    change_state(&side);
    current_state->Enter(this);
}
