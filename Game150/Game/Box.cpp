#include "Box.h"
#include "../Engine/Collision.h"

Box::Box(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Box.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

void Box::Update(double dt) {
    GameObject::Update(dt);
    /*
    Math::cube box_cube = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

    if (GetPosition().x < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + box_cube.Size().x / 2) {
        UpdatePosition({ -box_cube.Left(), 0, 0 });
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    if (GetPosition().x + box_cube.Size().x / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x) {
        UpdatePosition({ Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().x + Engine::GetWindow().GetSize().x - box_cube.Right() , 0, 0 });
        SetVelocity({ 0, GetVelocity().y, GetVelocity().z });
    }
    if (GetPosition().y < Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + box_cube.Size().y / 2) {
        UpdatePosition({ 0, -box_cube.Bottom(), 0 });
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
    }
    if (GetPosition().y + box_cube.Size().y / 2 > Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y) {
        UpdatePosition({ 0 , Engine::GetGameStateManager().GetGSComponent<CS230::Camera>()->GetPosition().y + Engine::GetWindow().GetSize().y - box_cube.Top(), 0 });
        SetVelocity({ GetVelocity().x, 0, GetVelocity().z });
    }*/
}
void Box::ResolveCollision(GameObject* other_object) 
{
    if (other_object->Type() == GameObjectTypes::Wall) {
        Math::cube box_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

        double left_right = std::min(abs(box_rect.Left() - other_rect.Right()), abs(other_rect.Left() - box_rect.Right()));
        double top_bottom = std::min(abs(box_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - box_rect.Bottom()));

        if (left_right < top_bottom) {
            if (box_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ (other_rect.Left() - box_rect.Right()), 0.0, 0.0 });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - box_rect.Left()), 0.0, 0.0 });
            }
            SetVelocity({ 0, 0, GetVelocity().z });
        }
        else {
            if (box_rect.Top() < other_rect.Top()) {
                UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - box_rect.Top()), 0.0 });
            }
            else {
                UpdatePosition(Math::vec3{ 0.0, (other_rect.Top() - box_rect.Bottom()), 0.0 });
            }
            SetVelocity({ 0, 0, GetVelocity().z });
        }

    }
    else if (other_object->Type() == GameObjectTypes::Player || other_object->Type() == GameObjectTypes::Box) {
        Engine::GetLogger().LogDebug("Box collision");
        Math::cube box_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

        double left_right = std::min(abs(box_rect.Left() - other_rect.Right()), abs(other_rect.Left() - box_rect.Right()));
        double top_bottom = std::min(abs(box_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - box_rect.Bottom()));

        if (left_right < top_bottom) {
            if (box_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ (other_rect.Left() - box_rect.Right()), 0.0, 0.0 });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - box_rect.Left()), 0.0, 0.0 });
            }
        }
        else {
            if (box_rect.Top() < other_rect.Top()) {
                UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - box_rect.Top()), 0.0 });
            }
            else {
                UpdatePosition(Math::vec3{ 0.0, (other_rect.Top() - box_rect.Bottom()), 0.0 });
            }
        }
    }


}
bool Box::WallCheck()
{
    return near_wall;
}

bool Box::CanCollideWith(GameObjectTypes)
{
    return true;
}

void Box::Side::Enter(GameObject* object) {
    Box* box = static_cast<Box*>(object);
    box->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Box::Side::Update(GameObject* object, double dt) {
    Box* box = static_cast<Box*>(object);
    //check time
}
void Box::Side::CheckExit(GameObject* object) {
    Box* box = static_cast<Box*>(object);
    if (Dimension::Top == box->dimension.GetDimension())
    {
        box->change_state(&box->top);
    }

}

void Box::Top::Enter(GameObject* object) {
    Box* box = static_cast<Box*>(object);
    box->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Box::Top::Update(GameObject* object, double dt) {
    Box* box = static_cast<Box*>(object);
    //check time
}
void Box::Top::CheckExit(GameObject* object) {
    Box* box = static_cast<Box*>(object);
    if (Dimension::Side == box->dimension.GetDimension())
    {
        box->change_state(&box->side);
    }

}