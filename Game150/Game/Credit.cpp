#include "Credit.h"
#include "../Engine/Engine.h"
#include "raylib.h" 
#include "States.h"
Credit::Credit() : backgroundMusic{}
{
    States currentState = static_cast<States>(Engine::GetGameStateManager().GetCurrentGameState());
    if (currentState == States::Credit) {
        InitAudioDevice();
    }
    goup = 0;
}

void Credit::Load()
{
    backgroundMusic = LoadMusicStream("Assets/B.mp3");
    PlayMusicStream(backgroundMusic);

    textures.push_back(Engine::GetTextureManager().Load("Assets/EndingCredit/Slide1.png"));
    textures.push_back(Engine::GetTextureManager().Load("Assets/EndingCredit/Slide2.png"));
    textures.push_back(Engine::GetTextureManager().Load("Assets/EndingCredit/Slide3.png"));
    textures.push_back(Engine::GetTextureManager().Load("Assets/EndingCredit/Slide4.png"));
    textures.push_back(Engine::GetTextureManager().Load("Assets/EndingCredit/Slide5.png"));
}

void Credit::Unload()
{
    UnloadMusicStream(backgroundMusic);

    textures.clear();
    goup = 0;
}

void Credit::Update(double dt)
{
    if (Engine::GetInput().KeyDown(CS230::Input::Keys::Left_Shift)) {
        goup += dt * 1000;
    }
    else {
        goup += dt * 100;
    }

    if (goup >= 4700) {
        Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::MainMenu));
    }
    UpdateMusicStream(backgroundMusic);
   
}

void Credit::Draw()
{
    Engine::GetWindow().Clear(0x0);
    for (int i = 0; i < textures.size(); ++i) {
        textures[i]->Draw(Math::TranslationMatrix(Math::vec2{ 160, 90 - 900 * i + goup }));
    }
  
}