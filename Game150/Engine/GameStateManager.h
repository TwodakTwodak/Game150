#pragma once
#include "GameState.h"
#include <vector>
#include "../Game/States.h"

namespace CS230 {
    class GameStateManager {
    public:
        GameStateManager();

        void Update(double dt);

        void AddGameState(GameState& gamestate);
        void SetNextGameState(int index);
        void ClearNextGameState();
        void ReloadState();
        bool HasGameEnded();
        void ReloadGameState();
        //int GetGameStateManager();//return?
        template<typename T>
        T* GetGSComponent() { return current_gamestate->GetGSComponent<T>(); }
        States GetCurrentGameState() const {
            return currentState;
        }
    private:
        enum class Status {
            STARTING,
            LOADING,
            UPDATING,
            UNLOADING,
            STOPPING,
            EXIT
        };

        Status status;
        std::vector<GameState*> gamestates;
        GameState* current_gamestate;
        GameState* next_gamestate;
        States currentState;

    };
}