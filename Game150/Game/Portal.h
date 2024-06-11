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
};

class Portal2 : public CS230::GameObject {
public:
    Portal2(Math::vec3 position, int potal_num);
    std::string TypeName() override { return "Portal2"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Portal2; }

    int PortalNumber();
private:
    int portal_num;
};