#pragma once
#include "..\Engine\GameObjectManager.h"
#include "GameObjectTypes.h"
class Exit : public CS230::GameObject {
public:
    Exit(Math::vec3 position);
    std::string TypeName() override { return "Exit"; }
    virtual GameObjectTypes Type() override { return GameObjectTypes::Exit; }

    void GoToState();
private:
    int to_state;
};
