#include "Exit.h"
#include "..\Engine\ComponentManager.h"
#include "..\Engine\Collision.h"
Exit::Exit(Math::vec3 position) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Exit.spt", this));
}

void Exit::GoToState() {
    Engine::GetGameStateManager().SetNextGameState(to_state);
}
