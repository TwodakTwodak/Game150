#pragma once
#include "../Engine/GameStateManager.h"
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
    CS230::Texture* texture;
};