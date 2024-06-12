/*
Copyright (C) 2023 DigiPen Institute of Technology
Reproduction or distribution of this file or its contents without
prior written consent is prohibited
File Name:  GameObject.h
Project:    CS230 Engine
Author:     Jonathan Holmes
Created:    March 8, 2023
*/

#pragma once
#include "Sprite.h"
#include "Cube.h"
#include "ComponentManager.h"
#include "Dimension.h"
namespace Math { class TransformationMatrix; }
enum class GameObjectTypes;

namespace CS230 {
    class Component;

    class GameObject {
        friend class Sprite;
    public:
        GameObject(Math::vec3 position);
        GameObject(Math::vec3 position, double rotation, Math::vec2 scale);
        virtual ~GameObject() {}

        virtual GameObjectTypes Type() = 0;
        virtual std::string TypeName() = 0;
        bool IsCollidingWith(GameObject* other_object);
        virtual bool CanCollideWith(GameObjectTypes other_object_type);

        virtual void Update(double dt);
        virtual void Draw(Math::TransformationMatrix camera_matrix);

        const Math::TransformationMatrix& GetMatrix();
        const Math::vec3& GetPosition() const;
        const Math::vec3& GetVelocity() const;
        const Math::vec2& GetScale() const;
        double GetRotation() const;

        void SetPosition(Math::vec3 new_position);
        void UpdatePosition(Math::vec3 delta);
        void SetVelocity(Math::vec3 new_velocity);
        template<typename T>
        T* GetGOComponent() {
            return componentmanager.GetComponent<T>();
        }
        virtual void ResolveCollision(GameObject* other_object) { };


    protected:
        //void SetPosition(Math::vec2 new_position);
        
        
        void UpdateVelocity(Math::vec3 delta);
        void SetScale(Math::vec2 new_scale);
        void UpdateScale(Math::vec2 delta);
        void SetRotation(double new_rotation);
        void UpdateRotation(double delta);


        class State {
        public:
            virtual void Enter(GameObject* object) = 0;
            virtual void Update(GameObject* object, double dt) = 0;
            virtual void CheckExit(GameObject* object) = 0;
            virtual std::string GetName() = 0;
        };
        State* current_state;
        void change_state(State* new_state);

        void AddGOComponent(Component* component) {
            componentmanager.AddComponent(component);
        }
        template<typename T>
        void RemoveGOComponent() {
            componentmanager.RemoveComponent<T>();
        }
        void ClearGOComponents() {
            componentmanager.Clear();
        }
        void UpdateGOComponents(double dt) {
            componentmanager.UpdateAll(dt);
        }
        
    private:
        Math::TransformationMatrix object_matrix;

        double rotation;
        Math::vec2 scale;
        Math::vec3 position;
        Math::vec3 velocity;

        class State_None : public State {
        public:
            void Enter(GameObject*) override {}
            void Update(GameObject*, double) override {}
            void CheckExit(GameObject*) override {}
            std::string GetName() { return ""; }
        };
        State_None state_none;

        bool matrix_outdated = true;

        ComponentManager componentmanager;
        CurrentDimension dimension;
        Math::TransformationMatrix matrix;
    };
}
