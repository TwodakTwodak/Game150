#include "Room.h"

Room::Room(Math::vec3 position, int index) : GameObject(position)
{
    if (index == 1) {
        AddGOComponent(new CS230::Sprite("Assets/Room1.spt", this));
    }
    else if(index == 2) {
        AddGOComponent(new CS230::Sprite("Assets/Room2.spt", this));
    }
    else if (index == 3) {
        AddGOComponent(new CS230::Sprite("Assets/Room3.spt", this));
    }
    else if (index == 4) {
        AddGOComponent(new CS230::Sprite("Assets/Room4.spt", this));
    }
    else if (index == 5) {
        AddGOComponent(new CS230::Sprite("Assets/Room5.spt", this));
    }
    else if (index == 6) {
        AddGOComponent(new CS230::Sprite("Assets/Room6.spt", this));
    }
    else if (index == 7) {
        AddGOComponent(new CS230::Sprite("Assets/Room7.spt", this));
    }
    change_state(&side);
    current_state->Enter(this);
}


void Room::Side::Enter(GameObject* object) {
    Room* room = static_cast<Room*>(object);
    room->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Room::Side::Update(GameObject* object, double dt) {
    Room* room = static_cast<Room*>(object);
    //check time
}
void Room::Side::CheckExit(GameObject* object) {
    Room* room = static_cast<Room*>(object);
    if (Dimension::Top == room->dimension.GetDimension())
    {
        room->change_state(&room->top);
    }

}

void Room::Top::Enter(GameObject* object) {
    Room* room = static_cast<Room*>(object);
    room->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Room::Top::Update(GameObject* object, double dt) {
    Room* room = static_cast<Room*>(object);
    //check time
}
void Room::Top::CheckExit(GameObject* object) {
    Room* room = static_cast<Room*>(object);
    if (Dimension::Side == room->dimension.GetDimension())
    {
        room->change_state(&room->side);
    }

}