#ifndef MARIO_MARIO_GAME_HPP
#define MARIO_MARIO_GAME_HPP

#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <future>
#include <condition_variable>
#include <vector>
#include "window.hpp"
#include "argparser.hpp"
#include "timer.hpp"

#define PERIOD_COUNTER 180
#define DEFAULT_WIDTH 60
#define DEFAULT_HEIGHT 10

class mario_game {
public:

    /*
    * Konstruktor tridy mario_game
    */
    mario_game();

    /*
    * Konstruktor tridy mario_game
    */
    mario_game(int coins, int enemies, int lives);

    /*
    * Destruktor tridy mario_game
    */
    ~mario_game();

    std::vector<size_t> get_positions(size_t min, size_t max, size_t count);

    size_t get_random_position(size_t min, size_t max);

    /*
     * Kontrola existenci vyhry nebo prohry:
     * - hráč prohral, pokud ztratil všechny své zivoty
     * - hráč vyhral, pokud nasbiral vsechny mince
     */
    void control();

    /*
     * Zkontroluje, zda se postava pohnula
     */
    void move();


    //getters and setters

    void output_area();

    void compute();

    void input();

    bool get_quit() const;

    void set_quit(bool qq);

    bool get_pause() const;

    void set_pause(bool pp);

    int get_coins() const;

    void plus_coin();

    int get_lives() const;

    void minus_live();

    std::vector<p_field> get_playing_area() const;

private:
    bool quit = false;                          // je konec hry?
    bool pause = true;                          // hra pozastavena?

    std::unique_ptr<window> win;                                            // hraci okenko
    size_t width, height;                                                   // rozmery hraci plochy
    std::vector<p_field> playing_area;                                      // hraci plocha
    int all_coins, all_enemies, all_lives;                                  // pocet minci/nepriteli, zivotu
    bool is_up = false, is_left = false, is_right = false, is_down = false; // pohyb
    timer timer;                                                            // casovac
    int cur_coins = 0;                                                      // aktualni pocet minci hrace
    size_t player_position;                                                 // pozice hrace na hraci plose

    std::mutex mutex;
    std::condition_variable cvar;
};

#endif //MARIO_MARIO_GAME_HPP