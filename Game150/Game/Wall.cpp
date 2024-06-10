#include "Wall.h"
#include "../Engine/Collision.h"
Wall::Wall(Math::vec3 position, int size) : CS230::GameObject(position) {
    
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
    default:
    {
        AddGOComponent(new CS230::Sprite("Assets/Wall.spt", this));
        break;
    }
    }
}

void Wall::ResolveCollision(GameObject* other_object)
{
    Math::cube wall_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
    Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();

    if (dimension.GetDimension() == Dimension::Side)
    {
        if (wall_rect.Left() < other_rect.Left()) {
            UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
            SetVelocity({ 0, 0, GetVelocity().z });
        }
        else {
            UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
            SetVelocity({ 0, 0, GetVelocity().z });
        }
    }
    else
    {
        double left_right = std::min(abs(wall_rect.Left() - other_rect.Right()), abs(other_rect.Left() - wall_rect.Right()));
        double top_bottom = std::min(abs(wall_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - wall_rect.Bottom()));
        if (left_right < top_bottom)
        {
            if (wall_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ (other_rect.Left() - wall_rect.Right()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - wall_rect.Left()), 0.0, 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
        }
        else
        {
            if (wall_rect.Top() < other_rect.Top()) {
                UpdatePosition(Math::vec3{ 0.0, (other_rect.Bottom() - wall_rect.Top()), 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
            else {
                UpdatePosition(Math::vec3{ 0.0,(other_rect.Top() - wall_rect.Bottom()), 0.0 });
                SetVelocity({ 0, 0, GetVelocity().z });
            }
        }
    }
}