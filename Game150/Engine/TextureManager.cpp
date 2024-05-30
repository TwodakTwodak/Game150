/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  TextureManager.cpp
Project:    CS230 Engine
Author:     Huiuk Jang
Created:    May 1, 2024
*/
#include "TextureManager.h"
#include "Engine.h"
#include "Texture.h"

CS230::Texture* CS230::TextureManager::Load(const std::filesystem::path& file_name)
{
    std::map<std::filesystem::path, Texture*>::iterator temp = textures.find(file_name);
    if (temp != textures.end())
    {
        //Engine::GetLogger().LogEvent("Already loaded");
        return temp->second;
    }
    else
    {
        Texture* texture = new Texture(file_name);
        textures[file_name] = texture;
        Engine::GetLogger().LogEvent("Texture loaded: " + file_name.string());
        return texture;
    }
}
void CS230::TextureManager::Unload()
{
    for (std::pair<const std::filesystem::path, CS230::Texture*> path : textures) {
        delete path.second;
    }
    textures.clear();
    Engine::GetLogger().LogEvent("Texture unloaded");
}

namespace {
    RenderTexture2D s_render_texture = {};
}

void CS230::TextureManager::StartRenderTextureMode(int width, int height) {
    s_render_texture = LoadRenderTexture(width, height);
    BeginTextureMode(s_render_texture);
    rlClearColor(0, 0, 0, 0);
    rlClearScreenBuffers();
}

CS230::Texture* CS230::TextureManager::EndRenderTextureMode() {
    EndTextureMode();
    const auto window_size = Engine::GetWindow().GetSize();
    rlSetFramebufferWidth(window_size.x);
    rlSetFramebufferHeight(window_size.y);
    rlUnloadFramebuffer(s_render_texture.id);
    const auto result = new Texture{ s_render_texture.texture };
    rendered_textures.push_back(result);
    return result;
}
