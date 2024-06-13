#include "Wall.h"
#include "../Engine/Collision.h"
#include "Box.h"
#include "Player.h"
Wall::Wall(Math::vec3 position) : CS230::GameObject(position) {

    AddGOComponent(new CS230::Sprite("Assets/Wall.spt", this));
    change_state(&side);
    current_state->Enter(this);
}


Outskirts::Outskirts(Math::vec3 position, int size) : CS230::GameObject(position) {


    switch (size) {
    case 1:
    {
        AddGOComponent(new CS230::Sprite("Assets/outskirts1.spt", this));
        break;
    }
    case 2:
    {
        AddGOComponent(new CS230::Sprite("Assets/outskirts2.spt", this));
        break;
    }
    }
}

void Outskirts::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Player)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        if (!(static_cast<Player*>(other_object)->StandingOn() == this || static_cast<Player*>(other_object)->StandingOn() == nullptr))
        {
            if (dimension.GetDimension() == Dimension::Side)
            {
                if (wall_rect.Left() > other_rect.Left()) {

                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
                double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
                if (left_right < top_bottom)
                {
                    if (wall_rect.Left() > other_rect.Left()) {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });

                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
                else
                {
                    if (wall_rect.Top() > other_rect.Top()) {

                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(wall_rect.Bottom() - other_rect.Top()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (wall_rect.Top() - other_rect.Bottom()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
            }
        }

    }
    if (other_object->Type() == GameObjectTypes::Box)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

        if (dimension.GetDimension() == Dimension::Side)
        {
            if (wall_rect.Left() < other_rect.Left()) {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
            else {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
        }
        else
        {
            double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
            double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
            if (left_right < top_bottom)
            {
                if (wall_rect.Left() < other_rect.Left()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                if (wall_rect.Top() < other_rect.Top()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - wall_rect.Top()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - wall_rect.Bottom()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
        }
    }
}


Floor::Floor(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Floor.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

void Floor::ResolveCollision(GameObject* other_object)
{
}

void Floor::Side::Enter(GameObject* object) {
    Floor* floor = static_cast<Floor*>(object);
    floor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Floor::Side::Update(GameObject* object, double dt) {
    Floor* floor = static_cast<Floor*>(object);
    //check time
}
void Floor::Side::CheckExit(GameObject* object) {
    Floor* floor = static_cast<Floor*>(object);
    if (Dimension::Top == floor->dimension.GetDimension())
    {
        floor->change_state(&floor->top);
    }
}

void Floor::Top::Enter(GameObject* object) {
    Floor* floor = static_cast<Floor*>(object);
    floor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Floor::Top::Update(GameObject* object, double dt) {
    Floor* floor = static_cast<Floor*>(object);
    //check time
}
void Floor::Top::CheckExit(GameObject* object) {
    Floor* floor = static_cast<Floor*>(object);
    if (Dimension::Side == floor->dimension.GetDimension())
    {
        floor->change_state(&floor->side);
    }
}

void Wall::Side::Enter(GameObject* object) {
    Wall* wall = static_cast<Wall*>(object);
    wall->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Wall::Side::Update(GameObject* object, double dt) {
    Wall* wall = static_cast<Wall*>(object);
    //check time
}
void Wall::Side::CheckExit(GameObject* object) {
    Wall* wall = static_cast<Wall*>(object);
    if (Dimension::Top == wall->dimension.GetDimension())
    {
        wall->change_state(&wall->top);
    }

}

void Wall::Top::Enter(GameObject* object) {
    Wall* wall = static_cast<Wall*>(object);
    wall->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Wall::Top::Update(GameObject* object, double dt) {
    Wall* wall = static_cast<Wall*>(object);
    //check time
}
void Wall::Top::CheckExit(GameObject* object) {
    Wall* wall = static_cast<Wall*>(object);
    if (Dimension::Side == wall->dimension.GetDimension())
    {
        wall->change_state(&wall->side);
    }

}

bool Wall::CanCollideWith(GameObjectTypes)
{
    return collision_on;
}
void Wall::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Player)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        if (!(static_cast<Player*>(other_object)->StandingOn() == this || static_cast<Player*>(other_object)->StandingOn() == nullptr))
        {
            if (dimension.GetDimension() == Dimension::Side)
            {
                if (wall_rect.Left() > other_rect.Left()) {

                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
                double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
                if (left_right < top_bottom)
                {
                    if (wall_rect.Left() > other_rect.Left()) {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });

                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
                else
                {
                    if (wall_rect.Top() > other_rect.Top()) {

                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(wall_rect.Bottom() - other_rect.Top()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (wall_rect.Top() - other_rect.Bottom()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
            }
        }

    }
    if (other_object->Type() == GameObjectTypes::Box)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

        if (dimension.GetDimension() == Dimension::Side)
        {
            if (wall_rect.Left() < other_rect.Left()) {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
            else {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
        }
        else
        {
            double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
            double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
            if (left_right < top_bottom)
            {
                if (wall_rect.Left() < other_rect.Left()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                if (wall_rect.Top() < other_rect.Top()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - wall_rect.Top()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - wall_rect.Bottom()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
        }
    }
}

FlatFloor::FlatFloor(Math::vec3 position) : CS230::GameObject(position) {

    AddGOComponent(new CS230::Sprite("Assets/Horizon_Platform.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

void FlatFloor::Side::Enter(GameObject* object) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    flatfloor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void FlatFloor::Side::Update(GameObject* object, double dt) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    //check time
}
void FlatFloor::Side::CheckExit(GameObject* object) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    if (Dimension::Top == flatfloor->dimension.GetDimension())
    {
        flatfloor->change_state(&flatfloor->top);
    }
}

void FlatFloor::Top::Enter(GameObject* object) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    flatfloor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void FlatFloor::Top::Update(GameObject* object, double dt) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    //check time
}
void FlatFloor::Top::CheckExit(GameObject* object) {
    FlatFloor* flatfloor = static_cast<FlatFloor*>(object);
    if (Dimension::Side == flatfloor->dimension.GetDimension())
    {
        flatfloor->change_state(&flatfloor->side);
    }
}

bool FlatFloor::CanCollideWith(GameObjectTypes)
{
    return true;
}
void FlatFloor::ResolveCollision(GameObject* other_object)
{

    if (other_object->Type() == GameObjectTypes::Player)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        if (!(static_cast<Player*>(other_object)->StandingOn() == this || static_cast<Player*>(other_object)->StandingOn() == nullptr))
        {
            if (dimension.GetDimension() == Dimension::Side)
            {
                if (wall_rect.Left() > other_rect.Left()) {

                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
                double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
                if (left_right < top_bottom)
                {
                    if (wall_rect.Left() > other_rect.Left()) {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });

                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (wall_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
                else
                {
                    if (wall_rect.Top() > other_rect.Top()) {

                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(wall_rect.Bottom() - other_rect.Top()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (wall_rect.Top() - other_rect.Bottom()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
            }
        }

    }
    if (other_object->Type() == GameObjectTypes::Box)
    {
        Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

        if (dimension.GetDimension() == Dimension::Side)
        {
            if (wall_rect.Left() < other_rect.Left()) {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
            else {
                static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
            }
        }
        else
        {
            double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
            double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
            if (left_right < top_bottom)
            {
                if (wall_rect.Left() < other_rect.Left()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                if (wall_rect.Top() < other_rect.Top()) {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - wall_rect.Top()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Box*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - wall_rect.Bottom()), 0.0 });
                    static_cast<Box*>(other_object)->SetVelocity({ 0, 0, static_cast<Box*>(other_object)->GetVelocity().z });
                }
            }
        }
    }
}