#pragma once

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"
#include "../Engine/Dimension.h"
class Logo : public CS230::GameState {
public:
    Logo();
    void Load() override;
    void Unload() override;
    void Update([[maybe_unused]] double dt) override;
    void Draw() override;

    std::string GetName() override {
        return "Logo";
    }
private:
    double counter = 0;
    CS230::Texture* texture;
};