#pragma once
#include "ComponentManager.h"
#include "Rect.h"
#include "Cube.h"
#include "Matrix.h"
#include "GameObjectManager.h"
#include "Dimension.h"
namespace Math {
    class TransformationMatrix;
}

namespace CS230 {
    class GameObject;
    class Collision : public Component {
    public:
        virtual bool IsCollidingWith(GameObject* other_object) = 0;
        virtual void Draw(Math::TransformationMatrix display_matrix) = 0;
    };
    class CubeCollision : public Collision {
    public:
        CubeCollision(Math::icube boundary, GameObject* object);
        bool IsCollidingWith(GameObject* other_object) override;
        void Draw(Math::TransformationMatrix display_matrix);
        Math::cube WorldBoundary();
    private:
        GameObject* object;
        Math::icube boundary;
        CurrentDimension dimension;
    };

    

}
