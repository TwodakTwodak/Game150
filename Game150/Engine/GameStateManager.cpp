/* Copyright ... */

#include "GameStateManager.h"
#include "Engine.h"

CS230::GameStateManager::GameStateManager() :
    current_gamestate(nullptr),
    next_gamestate(nullptr),
    status(Status::STARTING)
{
}

void CS230::GameStateManager::AddGameState(GameState& gamestate) {
    //Your Code
    gamestates.push_back(&gamestate);
}

void CS230::GameStateManager::SetNextGameState(int index) {
    //Your Code
    next_gamestate = gamestates[index];
}

void CS230::GameStateManager::ReloadState() {
    //Your Code
    status = Status::UNLOADING;
}

void CS230::GameStateManager::ClearNextGameState() {
    //Your Code
    next_gamestate = nullptr;
}

bool CS230::GameStateManager::HasGameEnded() {
    return status == Status::EXIT;
}
void CS230::GameStateManager::ReloadGameState() {
    status = Status::LOADING;
}


void CS230::GameStateManager::Update(double dt) {
    switch (status) {
    case Status::STARTING:
        //Your Code
        //didn't did gamestates vector with AddGameState();
        //Engine::GetLogger().LogEvent("Starting " + current_gamestate->GetName());
        
        if (gamestates.size() < 1)
        {
            status = Status::STOPPING;
        }
        else
        {
            next_gamestate = gamestates[0];
            status = Status::LOADING;
        }
        break;
    case Status::LOADING:
        current_gamestate = next_gamestate;
        Engine::GetLogger().LogEvent("Load " + current_gamestate->GetName());
        current_gamestate->Load();
        Engine::GetLogger().LogEvent("Load Complete");
        status = Status::UPDATING;
        break;
    case Status::UPDATING:
        //Your Code
        if (current_gamestate != next_gamestate)
        {
            //SetNextGameState();
            status = Status::UNLOADING;
            Engine::GetTextureManager().Unload();
        }
        else
        {
            current_gamestate->Update(dt);
            current_gamestate->Draw();
        }
        break;
    case Status::UNLOADING:
        //Your Code
        Engine::GetLogger().LogEvent("Unload " + current_gamestate->GetName());
        current_gamestate->Unload();
        Engine::GetLogger().LogEvent("Unload Complete");
        status = Status::LOADING;
        if (next_gamestate == nullptr)
        {
            status = Status::STOPPING;
        }
        break;
    case Status::STOPPING:
        //Your Code
        status = Status::EXIT;
        break;
    case Status::EXIT:
        break;
    }
}
