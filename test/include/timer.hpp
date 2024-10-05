#ifndef TIMER_HPP
#define TIMER_HPP

#include <functional>

class Timer
{
public:
    Timer() = default;
    ~Timer() = default;

    void restart();

	void set_wait_time(double val);

	void set_one_shot(bool flag);

	void set_on_timeout(std::function<void()> on_timeout);

	void pause();

	void resume();

	void on_update(double delta);

private:
    double pass_time = 0;
    double wait_time = 0;
    bool paused = false;
    bool shotted = false;
    bool one_shot = false;
    std::function<void()> on_timeout;
};

#endif // TIMER_HPP