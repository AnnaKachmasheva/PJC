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

#define PERIOD_COUNTER 400
#define DEFAULT_WIDTH 60
#define DEFAULT_HEIGHT 10

class mario_game {
public:

    /*
    * Konstruktor tridy mario_game
    */
    explicit mario_game(int coins, int enemies, int lives) : quit(false),
                                                             width(DEFAULT_WIDTH),
                                                             height(DEFAULT_HEIGHT),
                                                             all_coins(coins),
                                                             all_enemies(enemies),
                                                             all_lives(lives){

        player_position = DEFAULT_WIDTH * (DEFAULT_HEIGHT - 2);
        timer.start();

        // init game map
        for (size_t row = 0; row < height; ++row) {
            for (size_t column = 0; column < width; ++column) {
                if (row == (height - 4) && column == 2) {
                    playing_area.push_back(coin);
                } else if (row == (height - 3) && column == 4) {
                    playing_area.push_back(enemy);
                } else if (row == (height - 1)) {
                    playing_area.push_back(earth);
                } else {
                    playing_area.push_back(nothing);
                }
            }
        }
        playing_area[player_position] = mario;

        win = std::make_unique<Window>(std::cout, width, height);
        win->redraw(playing_area, timer, cur_coins, all_lives);

        //todo remove it
        point = std::make_pair(0, 0);
    }

    /*
    * Destruktor tridy mario_game
    */
    ~mario_game() {
        control();
    }

    /*
     * Kontrola existenci vyhry nebo prohry
     * - hráč prohral, pokud ztratil všechny své zivoty
     * - hráč vyrohral, pokud nasbiral vsechny mince
     */
    void control() {
        if (all_lives == 0) {
            set_quit(true);

            win->redrawWIN(false);
        } else if (cur_coins == all_coins) {
            set_quit(true);

            win->redrawWIN(true);
        }
    }

    /*
     * Zkontroluje, zda se postava pohnula
     *
     */
    void move() {
        if (is_up) {
            is_up = false;

            if ((player_position - width) >= 0) {
                if (playing_area[player_position - width] == earth) {
                    return;
                } else if (playing_area[player_position - width] == coin) {
                    cur_coins = cur_coins + 1;
                } else if (playing_area[player_position - width] == enemy) {
                    all_enemies = all_enemies - 1;
                    all_lives = all_lives - 1;
                }

                this->playing_area[player_position] = nothing;
                player_position = player_position - width;
                this->playing_area[player_position] = mario;
            }
        }

        if (is_down) {
            is_down = false;

            if ((player_position + width) < playing_area.size()) {
                if (playing_area[player_position + width] == earth) {
                    return;
                } else if (playing_area[player_position + width] == coin) {
                    cur_coins = cur_coins + 1;
                } else if (playing_area[player_position + width] == enemy) {
                    all_enemies = all_enemies - 1;
                    all_lives = all_lives - 1;
                }

                this->playing_area[player_position] = nothing;
                player_position = player_position + width;
                this->playing_area[player_position] = mario;
            }
        }

        if (is_left) {
            is_left = false;

            size_t next_position = (player_position + 1) % width;

            if ((next_position - 1) >= 0) {
                if (playing_area[player_position - 1] == earth) {
                    return;
                } else if (playing_area[player_position - 1] == coin) {
                    cur_coins = cur_coins + 1;
                } else if (playing_area[player_position - 1] == enemy) {
                    all_enemies = all_enemies - 1;
                    all_lives = all_lives - 1;
                }

                this->playing_area[player_position] = nothing;
                player_position = player_position - 1;
                this->playing_area[player_position] = mario;
            }
        }

        if (is_right) {
            is_right = false;

            size_t next_position = (player_position + 1) % width;

            if((next_position + 1) >= width) {
                all_lives = 0;
            } else {
                if (playing_area[player_position + 1] == earth) {
                    return;
                } else if (playing_area[player_position * width + 1] == coin) {
                    cur_coins = cur_coins + 1;
                } else if (playing_area[player_position * width + 1] == enemy) {
                    all_enemies = all_enemies - 1;
                    all_lives = all_lives - 1;
                }

                this->playing_area[player_position] = nothing;
                player_position = player_position + 1;
                this->playing_area[player_position] = mario;
            }
        }
    }

    void output_area() {
        std::unique_lock<std::mutex> lg(mutex);
        cvar.wait(lg);
        win->redraw(playing_area, timer, cur_coins, all_lives);
    }

    void compute() {
        std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_COUNTER));

        // nepretrzity pohyb doprava a dolu
        is_right = true;
        is_down = true;

        move();

        std::unique_lock<std::mutex> lg(mutex);
        cvar.notify_all();
    }

    /**
     * w - UP(y++)
     * a - LEFT(x--)
     * d - RIGHT(x++)
     */
    void input() {
        std::unique_lock<std::mutex> lg(mutex);
        lg.unlock();
        if (quit)
            return;
        char c;
        std::cin >> c;

//        std::cout << "\n";

        if (c == 'w') {
            is_up = true;
            cvar.notify_one();
        } else if (c == 'a') {
            is_left = true;
            cvar.notify_one();
        } else if (c == 'd') {
            is_right = true;
            cvar.notify_one();
        } else if (c == 'q') {
            set_quit(true);
            cvar.notify_one();
        }
    }

    bool get_quit() const {
        return quit;
    }

    void set_quit(const bool qq) {
        quit = qq;
    }

private:
    bool quit;                          // je konec hry?

    std::unique_ptr<Window> win;
    size_t width, height;               // rozmery hraci plochy, pocet znacek v rade pro vyhru
    std::vector<p_field> playing_area;  // hraci plocha
    std::pair<size_t, size_t> point;    // aktualne zadane souradnice znacky

    int all_coins, all_enemies, all_lives;
    bool is_up = false, is_left = false, is_right = false, is_down = false;

    timer timer;                          // casovac
    int cur_coins = 0;                    // aktualni hrac
    size_t player_position;

    std::mutex mutex;
    std::condition_variable cvar;
};

int main(int argc, char *argv[]) {
    auto computeThread = [](mario_game &game) {
        bool q = false;
        while (!q) {
            game.compute();
            q = game.get_quit();
        }
    };

    auto outputThread = [](mario_game &game) {
        bool q = false;
        while (!q) {
            game.output_area();
            q = game.get_quit();
        }
    };

    auto inputThread = [](mario_game &game) {
        bool q = false;
        while (!q) {
            game.input();
            q = game.get_quit();
        }
    };

    set_raw(true);

    auto param = arg_parser::parse_program_arguments(argc, argv);
    mario_game PP(param.coins, param.enemies, param.lives);
    std::thread t1(computeThread, std::ref(PP));
    std::thread t2(outputThread, std::ref(PP));
    std::thread t3(inputThread, std::ref(PP));

    t1.join();
    t2.join();
    t3.join();
    set_raw(false);

    return 0;
}