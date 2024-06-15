#include "Box.h"
#include "Map.h"
#include "../Engine/Collision.h"
#include "Player.h"
#include "Portal.h"

Box::Box(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Box.spt", this));
    change_state(&side);
    portal_available = true;
    current_state->Enter(this);
    
}

void Box::Update(double dt) {
    GameObject::Update(dt);
}
void Box::ResolveCollision(GameObject* other_object)
{
    if (other_object->Type() == GameObjectTypes::Wall) {
        Math::cube box_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        if (dimension.GetDimension() == Dimension::Side)
        {
            if (box_rect.Left() < other_rect.Left()) {
                UpdatePosition(Math::vec3{ -(box_rect.Right() - other_rect.Left()), 0.0, 0.0 });
            }
            else {
                UpdatePosition(Math::vec3{ (other_rect.Right() - box_rect.Left()), 0.0, 0.0 });
            }
        }
        else
        {
            double left_right = std::min(abs(box_rect.Left() - other_rect.Right()), abs(other_rect.Left() - box_rect.Right()));
            double top_bottom = std::min(abs(box_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - box_rect.Bottom()));

            if (left_right < top_bottom)
            {
                if (box_rect.Left() < other_rect.Left()) {
                    UpdatePosition(Math::vec3{ -(box_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                }
                else {
                    UpdatePosition(Math::vec3{ (other_rect.Right() - box_rect.Left()), 0.0, 0.0 });
                }
            }
            else
            {
                if (box_rect.Top() < other_rect.Top()) {
                    UpdatePosition(Math::vec3{ 0.0, -(box_rect.Top() - other_rect.Bottom()), 0.0 });

                }
                else {
                    UpdatePosition(Math::vec3{ 0.0, (other_rect.Top() - box_rect.Bottom()), 0.0 });
                }
            }
        }

        SetVelocity({ 0, 0, GetVelocity().z });
    }
    else if (other_object->Type()==GameObjectTypes::Player)
    {
        Math::cube box_rect = GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        Math::cube other_rect = other_object->GetGOComponent<CS230::CubeCollision>()->WorldBoundary();
        if (!(static_cast<Player*>(other_object)->StandingOn() == this || static_cast<Player*>(other_object)->StandingOn() == nullptr))
        {
            if (dimension.GetDimension() == Dimension::Side)
            {
                if (box_rect.Left() > other_rect.Left()) {

                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (box_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
                else {
                    static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (box_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                    static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                }
            }
            else
            {
                double left_right = std::min(abs(box_rect.Left() - other_rect.Right()), abs(other_rect.Left() - box_rect.Right()));
                double top_bottom = std::min(abs(box_rect.Top() - other_rect.Bottom()), abs(other_rect.Top() - box_rect.Bottom()));
                if (left_right < top_bottom)
                {
                    if (box_rect.Left() > other_rect.Left()) {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (box_rect.Left() - other_rect.Right()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });

                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ (box_rect.Right() - other_rect.Left()), 0.0, 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
                else
                {
                    if (box_rect.Top() > other_rect.Top()) {

                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0,(box_rect.Bottom() - other_rect.Top()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                    else {
                        static_cast<Player*>(other_object)->UpdatePosition(Math::vec3{ 0.0, (box_rect.Top() - other_rect.Bottom()), 0.0 });
                        static_cast<Player*>(other_object)->SetVelocity({ 0, 0, static_cast<Player*>(other_object)->GetVelocity().z });
                    }
                }
            }
        }
    }
    else if (other_object->Type() == GameObjectTypes::Portal1) {
        is_portal_available = false;
        if (portal_available) {
            portal_available = false;
            Math::vec3 loc = Engine::GetGameStateManager().GetGSComponent<Map>()->GivePortal2()[static_cast<Portal1*>(other_object)->PortalNumber()].GetLocation();
            SetPosition({ loc.x , loc.y + 60, loc.z + 66 });
            SetVelocity({ 0, 0, 0 });
            Engine::GetLogger().LogEvent("Box teleported to: " + std::to_string(loc.x) + ", " + std::to_string(loc.y) + ", " + std::to_string(loc.z));  // 디버깅용 출력
        }
        std::cout << static_cast<Portal1*>(other_object)->PortalNumber() << std::endl;
    }
    else if (other_object->Type() == GameObjectTypes::Portal2) {
        is_portal_available = false;
        Engine::GetLogger().LogEvent("Collision with Portal2 detected."); // 디버깅용 출력
        if (portal_available) {
            Engine::GetLogger().LogEvent("Portal is available."); // 디버깅용 출력
            portal_available = false;
            int portalNumber = static_cast<Portal2*>(other_object)->PortalNumber();
            Engine::GetLogger().LogEvent("Portal2 number: " + std::to_string(portalNumber)); // 디버깅용 출력
            Math::vec3 loc = Engine::GetGameStateManager().GetGSComponent<Map>()->GivePortal1()[portalNumber].GetLocation();
            Engine::GetLogger().LogEvent("Portal1 location: " + std::to_string(loc.x) + ", " + std::to_string(loc.y) + ", " + std::to_string(loc.z)); // 디버깅용 출력
            SetPosition({ loc.x + 190, loc.y + 60, loc.z + 66 });
            SetVelocity({ 0, 0, 0 });
            Engine::GetLogger().LogEvent("Box teleported to: " + std::to_string(loc.x) + ", " + std::to_string(loc.y) + ", " + std::to_string(loc.z)); // 디버깅용 출력
        }
        std::cout << static_cast<Portal2*>(other_object)->PortalNumber() << std::endl;
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
