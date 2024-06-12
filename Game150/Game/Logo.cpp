#include "../Engine/Engine.h"
#include "States.h"
#include "Logo.h"
Logo::Logo() {
}

void Logo::Load()
{
    counter = 0;
    texture = Engine::GetTextureManager().Load("Assets/Logo.png");
}


void Logo::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(counter));
    if (counter >= 2) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    counter += dt;
}

void Logo::Unload()
{
}


void Logo::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix({ (Engine::GetWindow().GetSize() - texture->GetSize()) / 2.0 }));
}


