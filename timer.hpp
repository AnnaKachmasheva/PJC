#ifndef MARIO_TIMER_H
#define MARIO_TIMER_H

#include <chrono>

class timer {
public:

    /**
     * Start casovace od ted
     */
    void start();

    /**
     * Stop timer
     */
    void stop();

    /**
     * Vypocita rozdil mezi casem zahajeni a casem ukonceni
     * Pokud není casovac zastaven, pak je cas ukonceni aktuilni cas
     *
     * @return pocet milisekund, ktere uplynuly od zacatku casovace
     */
    int elapsed_milliseconds();

    /**
     *
     * @return pocet sekund, ktere uplynuly od zacatku casovace
     */
    int elapsed_seconds();

    /**
     *
     * @return pocet minut, ktere uplynuly od zacatku casovace
     */
    int elapsed_minutes();

    /**
     *
     * @return počet sekund od začátku nové minuty
     */
    int get_seconds();

    /**
     *
     * @return is_running
     */
    bool get_running() const;

private:
    std::chrono::time_point<std::chrono::steady_clock> start_time;  // cas spusteni casovace
    std::chrono::time_point<std::chrono::steady_clock> end_time;    // cas na konci spusteni casovace

    bool is_running = false;                                        // časovač neni pozastaven?
};

#endif //MARIO_TIMER_H