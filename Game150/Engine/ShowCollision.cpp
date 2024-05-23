#pragma once
#include "ShowCollision.h"
#include "Input.h"
#include "Engine.h"
CS230::ShowCollision::ShowCollision() : enabled(true) {}

void CS230::ShowCollision::Update(double dt) {
    if (Engine::GetInput().KeyJustReleased(CS230::Input::Keys::Tab) == true) {
        enabled = !enabled;
    }
}

bool CS230::ShowCollision::Enabled() {
    return enabled;
}
