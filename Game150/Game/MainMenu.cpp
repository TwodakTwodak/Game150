#include "../Engine/Engine.h"
#include "States.h"
#include "MainMenu.h"
MainMenu::MainMenu() {
}

void MainMenu::Load()
{
    counter = 0;
    texture = Engine::GetTextureManager().Load("Assets/DigiPen.png");
}


void MainMenu::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 2) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Map));
    }
    counter += dt;
}

void MainMenu::Unload()
{
}


void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
}

