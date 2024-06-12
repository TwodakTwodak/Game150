#pragma once
#include "..\Engine\GameObjectManager.h"
#include "GameObjectTypes.h"
class Portal1 : public CS230::GameObject {
public:
    Portal1(Math::vec3 position, int potal_num);
    std::string TypeName() override { return "Portal1"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal1; }

    int PortalNumber();
private:
    int portal_num;
    CurrentDimension dimension;
    enum class Animations {
        Side,
        Top
    };
    class Side : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Portal1 Side"; }
    };

    Side side;

    class Top : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Portal1 Top"; }
    };

    Top top;
};

class Portal2 : public CS230::GameObject {
public:
    Portal2(Math::vec3 position, int potal_num);
    std::string TypeName() override { return "Portal2"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal2; }

    int PortalNumber();
private:
    int portal_num;
    CurrentDimension dimension;
    enum class Animations {
        Side,
        Top
    };
    class Side : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Portal2 Side"; }
    };

    Side side;

    class Top : public State {
    public:
        virtual void Enter(GameObject* object) override;
        virtual void Update(GameObject* object, double dt) override;
        virtual void CheckExit(GameObject* object) override;
        std::string GetName() override { return "Portal2 Top"; }
    };

    Top top;
};