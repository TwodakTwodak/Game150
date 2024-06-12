#include "Exit.h"
#include "..\Engine\ComponentManager.h"
#include "..\Engine\Collision.h"
Exit::Exit(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Exit.spt", this));
    change_state(&side);
    current_state->Enter(this);
}

void Exit::GoToState() {
    Engine::GetGameStateManager().SetNextGameState(to_state);
}
void Exit::Side::Enter(GameObject* object) {
    Exit* exit = static_cast<Exit*>(object);
    exit->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Side));
}
void Exit::Side::Update(GameObject* object, double dt) {
    Exit* exit = static_cast<Exit*>(object);
    //check time
}
void Exit::Side::CheckExit(GameObject* object) {
    Exit* exit = static_cast<Exit*>(object);
    if (Dimension::Top == exit->dimension.GetDimension())
    {
        exit->change_state(&exit->top);
    }

}

void Exit::Top::Enter(GameObject* object) {
    Exit* exit = static_cast<Exit*>(object);
    exit->GetGOComponent<CS230::Sprite>()->PlayAnimation(static_cast<int>(Animations::Top));
}
void Exit::Top::Update(GameObject* object, double dt) {
    Exit* exit = static_cast<Exit*>(object);
    //check time
}
void Exit::Top::CheckExit(GameObject* object) {
    Exit* exit = static_cast<Exit*>(object);
    if (Dimension::Side == exit->dimension.GetDimension())
    {
        exit->change_state(&exit->side);
    }

}