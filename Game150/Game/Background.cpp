/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Background.cpp
Project:    CS230 Engine
Author:     Huiuk Jang
Created:    May 1, 2024
*/
#pragma once
#include "Background.h"
#include "../Engine/Engine.h"
#include "Map.h"

void Background::Add(const std::filesystem::path& texture_path, double speed) {
    backgrounds.push_back(ParallaxLayer{ Engine::GetTextureManager().Load(texture_path), speed });
}

void Background::Draw(CS230::Camera& camera) {
    for (int i = 0; i < backgrounds.size(); i++)
    {
        double scaledOffsetX = -camera.GetPosition().x * backgrounds[i].speed;
        object_matrix = Math::TranslationMatrix(Math::vec2{ scaledOffsetX, camera.GetPosition().y });
        backgrounds[i].texture->Draw(object_matrix);
    }
}

Math::ivec2 Background::GetSize()
{
    return backgrounds[backgrounds.size() - 1].texture->GetSize();
}
void Background::Unload()
{
    backgrounds.clear();
}
