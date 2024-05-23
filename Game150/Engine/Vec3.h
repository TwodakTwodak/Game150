/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Vec3.h
Project:    Gam150 Engine
Author:     Huiuk Jang
Created:    April 10, 2024
*/

#pragma once
#include <limits>

namespace Math {
    struct vec3 {
        double x{ 0.0 };
        double y{ 0.0 };
        double z{ 0.0 };

        vec3() = default;
        vec3(double x, double y, double z) : x(x), y(y), z(z) {}

        bool operator==(const vec3& v);
        bool operator!=(const vec3& v);

        vec3 operator+(const vec3& v);
        vec3& operator+=(const vec3& v);

        vec3 operator-(const vec3& v);
        vec3& operator-=(const vec3& v);

        vec3 operator*(double scale);
        vec3& operator*=(double scale);

        vec3 operator/(double divisor);
        vec3& operator/=(double divisor);

        vec3 operator-();

    };

    vec3 operator*(double scale, const vec3& v);

    struct ivec3 {
        int x{ 0 };
        int y{ 0 };
        int z{ 0 };

        ivec3() = default;
        ivec3(int x, int y, int z) : x(x), y(y), z(z) {};
        explicit operator vec3() {
            return vec3{ static_cast<double>(x),static_cast<double>(y), static_cast<double>(z) };
        }

        bool operator==(const ivec3& v);
        bool operator!=(const ivec3& v);

        ivec3 operator+(const ivec3& v);
        ivec3& operator+=(const ivec3& v);

        ivec3 operator-(const ivec3& v);
        ivec3& operator-=(const ivec3& v);

        ivec3 operator*(int scale);
        ivec3& operator*=(int scale);

        ivec3 operator/(int divisor);
        ivec3& operator/=(int divisor);

        ivec3 operator-();

        vec3 operator*(double scale);
        vec3 operator/(double divisor);

    };


}
