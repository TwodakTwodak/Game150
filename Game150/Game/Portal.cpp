#include "Portal.h"
#include "..\Engine\ComponentManager.h"
#include "..\Engine\Collision.h"
Portal1::Portal1(Math::vec3 position, int potal_num) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Portal1.spt", this));
}

int Portal1::PortalNumber() {
    return portal_num;
}

Portal2::Portal2(Math::vec3 position, int potal_num) : CS230::GameObject(position) {
    AddGOComponent(new CS230::Sprite("Assets/Portal2.spt", this));
}

int Portal2::PortalNumber() {
    return portal_num;
}