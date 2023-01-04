#include "timer.hpp"

void timer::start() {
    start_time = std::chrono::steady_clock::now();
    is_running = true;
}

void timer::stop() {
    end_time = std::chrono::steady_clock::now();
    is_running = false;
}

int timer::elapsed_milliseconds() {
    std::chrono::time_point<std::chrono::steady_clock> end_t;

    if (is_running) {
        end_t = std::chrono::steady_clock::now();
    } else {
        end_t = end_time;
    }

    return std::chrono::duration_cast<std::chrono::milliseconds>(end_t - start_time).count();
}

int timer::elapsed_seconds() {
    return elapsed_milliseconds() / 1000;
}

int timer::elapsed_minutes() {
    return elapsed_seconds() / 60;
}


int timer::get_seconds() {
    return elapsed_seconds() - elapsed_minutes() * 60;
}

bool timer::get_running() const {
    return is_running;
}