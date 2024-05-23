/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.cpp
Project:    CS230 Engine
Author:     Huiuk Jang
Created:    May 1, 2024
*/
#include "Matrix.h"
#include "raylib.h"
#include "Engine.h"

Math::TransformationMatrix::TransformationMatrix()
{
    Reset();
}
Math::TranslationMatrix::TranslationMatrix(ivec2 translate)
{
    Reset();
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}
Math::TranslationMatrix::TranslationMatrix(vec2 translate)
{
    Reset();
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
}
Math::TranslationMatrix::TranslationMatrix(ivec3 translate)
{
    Reset();
    matrix[0][2] = translate.x;
    matrix[1][2] = translate.y;
    matrix[2][2] = translate.z;
}
Math::TranslationMatrix::TranslationMatrix(vec3 translate)
{
    Reset();
    matrix[0][3] = translate.x;
    matrix[1][3] = translate.y;
    matrix[2][3] = translate.z;
}

void Math::TransformationMatrix::Reset() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            matrix[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }
}


Math::TransformationMatrix Math::TransformationMatrix::operator * (TransformationMatrix m) const {
    TransformationMatrix result;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            result.matrix[i][j] = matrix[i][0] * m.matrix[0][j] +
                matrix[i][1] * m.matrix[1][j] +
                matrix[i][2] * m.matrix[2][j] +
                matrix[i][3] * m.matrix[3][j];
        }
    }

    return result;
}

Math::TransformationMatrix& Math::TransformationMatrix::operator *= (Math::TransformationMatrix m) {
    (*this) = (*this) * m;
    return (*this);
}

Math::vec2 Math::TransformationMatrix::operator * (vec2 v) const {
    Math::vec2 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2];
    return result;
}

Math::vec3 Math::TransformationMatrix::operator * (vec3 v) const {
    Math::vec3 result;
    result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
    result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
    result.z = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
    return result;
}



Math::ScaleMatrix::ScaleMatrix(double scale)
{
    matrix[0][0] = matrix[0][0] * scale;
    matrix[1][1] = matrix[1][1] * scale;
    matrix[2][2] = matrix[1][1] * scale;
}

Math::ScaleMatrix::ScaleMatrix(vec2 scale)
{
    matrix[0][0] = matrix[0][0] * scale.x;
    matrix[1][1] = matrix[1][1] * scale.y;
}
Math::ScaleMatrix::ScaleMatrix(vec3 scale)
{
    matrix[0][0] = matrix[0][0] * scale.x;
    matrix[1][1] = matrix[1][1] * scale.y;
    matrix[2][2] = matrix[2][2] * scale.z;
}
Math::RotationMatrix::RotationMatrix(double theta)
{
    matrix[0][0] = cos(theta);
    matrix[0][1] = sin(theta);
    matrix[1][0] = -sin(theta);
    matrix[1][1] =  cos(theta);
}
Math::vec2 Math::TransformationMatrix::DimensionMatrix(Math::TransformationMatrix m, Math::vec3 v)
{
    Math::vec2 result = { 0, 0 };
    if (dimension.GetDimension() == Dimension::Side)
    {
        result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
        result.y = matrix[1][0] * v.x + matrix[1][1] * v.y + matrix[1][2] * v.z + matrix[1][3];
    }
    else if (dimension.GetDimension() == Dimension::Top)
    {
        result.x = matrix[0][0] * v.x + matrix[0][1] * v.y + matrix[0][2] * v.z + matrix[0][3];
        result.y = matrix[2][0] * v.x + matrix[2][1] * v.y + matrix[2][2] * v.z + matrix[2][3];
    }
    else
    {
        Engine::GetLogger().LogError("Dimension Error - Check Texture.cpp");
    }
    
    
    return result;
}