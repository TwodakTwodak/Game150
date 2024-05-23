/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  Rect.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Vec3.h"
#include <cmath>

namespace Math {
    struct [[nodiscard]] cube {
        Math::vec3 point_1{ 0.0, 0.0, 0.0 };
        Math::vec3 point_2{ 0.0, 0.0, 0.0 };
        double Left() const noexcept {
            return std::min(point_1.x, point_2.x);
        }
        double Right() const noexcept {
            return std::max(point_1.x, point_2.x);
        }
        double Top() const noexcept {
            return std::max(point_1.y, point_2.y);
        }
        double Bottom() const noexcept {
            return std::min(point_1.y, point_2.y);
        }
        double High()const noexcept {
            return std::max(point_1.z, point_2.z);
        }
        double Low()const noexcept {
            return std::min(point_1.z, point_2.z);
        }
        vec3 Size() const noexcept {
            /*return {
                //using abs beacuse of flip (use scale -1!)
                //Dont need to think about rotation part!
                //Beacuse we will not rotate cube while playing game!
                top_front.x - bottom_behind.x,
                top_front.y - bottom_behind.y,
                top_front.z - bottom_behind.z
            };*/
            return {
                Right() - Left(),
                Top() - Bottom(),
                High() - Low()
            };
        }
    };
    struct [[nodiscard]] icube {
        Math::ivec3 point_1{ 0, 0, 0 };
        Math::ivec3 point_2{ 0, 0, 0 };
        int Left() const noexcept {
            return std::min(point_1.x, point_2.x);
        }
        int Right() const noexcept {
            return std::max(point_1.x, point_2.x);
        }
        int Top() const noexcept {
            return std::max(point_1.y, point_2.y);
        }
        int Bottom() const noexcept {
            return std::min(point_1.y, point_2.y);
        }
        int High()const noexcept {
            return std::max(point_1.z, point_2.z);
        }
        int Low()const noexcept {
            return std::min(point_1.z, point_2.z);
        }
        ivec3 Size() const noexcept {
            return {
                Right() - Left(),
                Top() - Bottom(),
                High() - Low()
            };
        }
    };
}