#include "Trampoline.h"
#include "../Engine/Collision.h"
#include "Box.h"
#include "Player.h"
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


TrampolineFloor::TrampolineFloor(Math::vec3 position) : CS230::GameObject(position) {

    AddGOComponent(new CS230::Sprite("Assets/Horizon_Platform.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

void TrampolineFloor::Side::Enter(GameObject* object) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    flatfloor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void TrampolineFloor::Side::Update(GameObject* object, double dt) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    //check time
}
void TrampolineFloor::Side::CheckExit(GameObject* object) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    if (Dimension::Top == flatfloor->dimension.GetDimension())
    {
        flatfloor->change_state(&flatfloor->top);
    }
}

void TrampolineFloor::Top::Enter(GameObject* object) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    flatfloor->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void TrampolineFloor::Top::Update(GameObject* object, double dt) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    //check time
}
void TrampolineFloor::Top::CheckExit(GameObject* object) {
    TrampolineFloor* flatfloor = static_cast<TrampolineFloor*>(object);
    if (Dimension::Side == flatfloor->dimension.GetDimension())
    {
        flatfloor->change_state(&flatfloor->side);
    }
}

bool TrampolineFloor::CanCollideWith(GameObjectTypes)
{
    return true;
}
void TrampolineFloor::ResolveCollision(GameObject* other_object)
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