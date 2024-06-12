#include "../Engine/Engine.h"
#include "States.h"
#include "MainMenu.h"
#include "../Engine/Sprite.h"
#include "raylib.h" 

MainMenu::MainMenu() : backgroundMusic1{} {
    InitAudioDevice();
}

void MainMenu::Load()
{
    backgroundMusic1 = LoadMusicStream("Assets/A.mp3");
   PlayMusicStream(backgroundMusic1);


    index = 0;
    counter = 0;
    space = 0;
    select = Engine::GetTextureManager().Load("Assets/Select.png");
    texture = Engine::GetTextureManager().Load("Assets/Menu.png");
    arrow = Engine::GetTextureManager().Load("Assets/Arrow.png");
}


void MainMenu::Update([[maybe_unused]] double dt) {
    Engine::GetLogger().LogDebug(std::to_string(index));
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Right)) {
        ++index;
        if (index >= 3) {
            index = 0;
        }
    }
    else if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Left)) {
        --index;
        if (index <= -1) {
            index = 2;
        }
    }

    //Checking press for state
    if (Engine::GetInput().KeyJustPressed(CS230::Input::Keys::Enter)) {
        if (index == 0) {
            Engine::GetGameStateManager().SetNextGameState(static_cast<int>(States::Map));
        }
        else if (index == 1) {
        }
        else if (index == 2) {
            Engine::GetGameStateManager().ClearNextGameState();
        }
    }

    counter += dt;
    if (counter >= 0.1) {
        space -= 1599;
        counter = 0;
        if (space <= -1599 * 5) {
            space = 0;
        }
    }
    //seems picture is staying at left 0,0
    //Able to make shake picture!

    UpdateMusicStream(backgroundMusic1);

}

void MainMenu::Unload()
{
    texture = nullptr;
    select = nullptr;
   UnloadMusicStream(backgroundMusic1);


}


void MainMenu::Draw() {
    Engine::GetWindow().Clear(UINT_MAX);
    texture->Draw(Math::TranslationMatrix(Math::vec2{space, 0}));
    select->Draw(Math::TranslationMatrix(Math::vec2{397 * 3, 140}), Math::ivec2{index * 375, 0}, Math::ivec2{375, 99});
    arrow->Draw(Math::TranslationMatrix(Math::vec2{ 397 * 3 - 100, 140 }));
}

