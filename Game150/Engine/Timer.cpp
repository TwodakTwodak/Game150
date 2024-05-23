#include "timer.h"
#include "Engine.h"

CS230::Timer::Timer(double time_remaining) : timer_max(time_remaining), timer(time_remaining) 
{
    pendulum = false;
}
void CS230::Timer::Set(double time_remaining)
{
    timer_max = time_remaining;
}
void CS230::Timer::Update(double dt)
{
    timer -= dt;
    pendulum = !pendulum;
}
void CS230::Timer::Reset()
{
    timer = timer_max;
}
double CS230::Timer::Remaining()
{
    return timer;
}
int CS230::Timer::RemainingInt()
{
    return timer;
}
bool CS230::Timer::TickTock()
{
    return pendulum;
}
