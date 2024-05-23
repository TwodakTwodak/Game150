#pragma once
#include "..\Engine\Component.h"
namespace CS230 {
    class Timer : public CS230::Component {
    public:
        Timer(double time_remaining);
        void Set(double time_remaining);
        void Update(double dt) override;
        void Reset();
        double Remaining();
        int RemainingInt();
        bool TickTock();
    private:
        double timer;
        double timer_max;
        bool pendulum;
    };
}


