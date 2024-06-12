#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "raylib.h" 
class Credit : public CS230::GameState {
public:
    Credit();
    void Load() override;
    void Unload() override;
    void Update([[maybe_unused]] double dt) override;
    void Draw() override;

    std::string GetName() override {
        return "Credit";
    }
private:
    double goup = 0;
    std::vector<CS230::Texture*> textures;
    Music backgroundMusic;
};