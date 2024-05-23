/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Splash.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#ifndef SPLASH_H
#define SPLASH_H

#include "../Engine/GameState.h"
#include "../Engine/Texture.h"

class Splash : public CS230::GameState {
public:
    Splash();
    void Load() override;
    void Update([[maybe_unused]] double dt) override;
    void Unload() override;
    void Draw() override;

    std::string GetName() override {
        return "Splash";
    }

private:
    //Is this private or public?
    double counter = 0;
    CS230::Texture* texture;
};

//Why don't it work when i change driection of headerfile, why does it work after retyping.



#endif