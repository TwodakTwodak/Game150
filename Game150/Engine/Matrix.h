/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Matrix.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec2.h"
#include "Vec3.h"
#include <cmath>
#include "Dimension.h"

namespace Math {
    class TransformationMatrix {
    public:
        TransformationMatrix();

        const double* operator[](int index) const { return matrix[index]; }
        TransformationMatrix operator * (TransformationMatrix m) const;
        TransformationMatrix& operator *= (TransformationMatrix m);
        Math::vec2 operator * (vec2 v) const;
        Math::vec3 operator * (vec3 v) const;
        void Reset();
        Math::vec2 DimensionMatrix(TransformationMatrix m, vec3 v);
    protected:
        double matrix[4][4];
    private:
        CurrentDimension dimension;
    };

    class TranslationMatrix : public TransformationMatrix {
    public:
        TranslationMatrix(ivec2 translate);
        TranslationMatrix(vec2 translate);
        TranslationMatrix(ivec3 translate);
        TranslationMatrix(vec3 translate);
    };
    class ScaleMatrix : public TransformationMatrix {
    public:
        ScaleMatrix(double scale);
        ScaleMatrix(vec2 scale);
        ScaleMatrix(vec3 scale);
    };


    class RotationMatrix : public TransformationMatrix {
    public:
        RotationMatrix(double theta);
    };


}
