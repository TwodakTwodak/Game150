#pragma once
#include "../Engine/GameStateManager.h"
#include "../Engine/GameObjectManager.h"
#include "raylib.h" 

class MainMenu : public CS230::GameState {
public:
    MainMenu();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "MainMenu";
    }
private:
    double counter = 0;
    double flick = 0;
    int index;
    double space;
    CS230::Texture* texture;
    CS230::Texture* select;
    CS230::Texture* arrow;
    Music backgroundMusic1;

};