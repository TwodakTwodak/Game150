/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Camera.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Matrix.h"
#include "Component.h"
#include "Vec3.h"
#include "Cube.h"

namespace CS230 {
    class Camera : public Component{
    public:
        Camera(Math::cube player_zone);
        void SetPosition(Math::vec3 new_position);
        const Math::vec3& GetPosition() const;
        void SetLimit(Math::icube new_limit);
        void Update(const Math::vec3& player_position);
        Math::TransformationMatrix GetMatrix();
    private:
        Math::icube limit;
        Math::vec3 position;
        Math::cube player_zone;
    };
}
