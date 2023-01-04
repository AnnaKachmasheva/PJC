#include "mario_game.hpp"

mario_game::mario_game() : quit(false),
                           pause(true),
                           width(DEFAULT_WIDTH),
                           height(DEFAULT_HEIGHT),
                           all_coins(ARG_COINS_DEFAULT),
                           all_enemies(ARG_ENEMIES_DEFAULT),
                           all_lives(ARG_LIVES_DEFAULT) {
    player_position = DEFAULT_WIDTH * (DEFAULT_HEIGHT - 2);

    // init game map
    for (size_t row = 0; row < height; ++row) {
        for (size_t column = 0; column < width; ++column) {
            if (row == (height - 1)) {
                playing_area.push_back(earth);
            } else {
                playing_area.push_back(nothing);
            }
        }
    }
    playing_area[player_position] = mario;

    std::vector<size_t> enemies_vec = get_positions(0, DEFAULT_WIDTH * (DEFAULT_HEIGHT - 1), all_enemies);
    for (auto en: enemies_vec) {
        playing_area[en] = enemy;
    }

    std::vector<size_t> coins_vec = get_positions(0, DEFAULT_WIDTH * (DEFAULT_HEIGHT - 1), all_coins);
    for (auto co: coins_vec) {
        playing_area[co] = coin;
    }

    //init game window
    win = std::make_unique<window>(std::cout, width, height);
    win->redraw(playing_area, timer, cur_coins, all_lives, pause);
}

mario_game::mario_game(int coins, int enemies, int lives) : mario_game() {
    all_coins = coins;
    all_enemies= enemies;
    all_lives = lives;
}

std::vector<size_t> mario_game::get_positions(size_t min, size_t max, size_t count) {
    std::vector<size_t> positions;
    size_t c = count;
    while (c > 0) {
        positions.push_back(get_random_position(min, max));
        c--;
    }
    return positions;
}

size_t mario_game::get_random_position(size_t min, size_t max) {
    return rand() % (max - min + 1) + min;
}


mario_game::~mario_game() {
    control();
}

void mario_game::control() {
    if (all_lives == 0) {
        set_quit(true);

        win->redrawWIN(false);
    } else if (cur_coins == all_coins) {
        set_quit(true);

        win->redrawWIN(true);
    }
}

void mario_game::move() {
    if (is_left) {
        is_left = false;

        size_t next_position = (player_position - 1) % width;

        if ((next_position - 1) >= 0) {
            if (playing_area[player_position - 1] == earth) {
                return;
            } else if (playing_area[player_position - 1] == coin) {
                plus_coin();
            } else if (playing_area[player_position - 1] == enemy) {
                all_enemies = all_enemies - 1;
                minus_live();
            }

            this->playing_area[player_position] = nothing;
            player_position = player_position - 1;
            this->playing_area[player_position] = mario;
        }
    }

    if (is_right) {
        is_right = false;

        size_t next_position = (player_position + 1) % width;

        if ((next_position + 1) >= width) {
            all_lives = 0;
        } else {
            if (playing_area[player_position + 1] == earth) {
                return;
            } else if (playing_area[player_position * width + 1] == coin) {
                plus_coin();
            } else if (playing_area[player_position * width + 1] == enemy) {
                all_enemies = all_enemies - 1;
                minus_live();
            }

            this->playing_area[player_position] = nothing;
            player_position = player_position + 1;
            this->playing_area[player_position] = mario;
        }
    }

    if (is_up) {
        is_up = false;

        if ((player_position - width) >= 0) {
            if (playing_area[player_position - width] == earth) {
                return;
            } else if (playing_area[player_position - width] == coin) {
                plus_coin();
            } else if (playing_area[player_position - width] == enemy) {
                all_enemies = all_enemies - 1;
                minus_live();
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
                plus_coin();
            } else if (playing_area[player_position + width] == enemy) {
                all_enemies = all_enemies - 1;
                minus_live();
            }

            this->playing_area[player_position] = nothing;
            player_position = player_position + width;
            this->playing_area[player_position] = mario;
        }
    }
}

void mario_game::output_area() {
    std::unique_lock<std::mutex> lg(mutex);
    cvar.wait(lg);
    if (!get_pause() && !quit)
        win->redraw(playing_area, timer, cur_coins, all_lives, pause);
}

void mario_game::compute() {
    std::this_thread::sleep_for(std::chrono::milliseconds(PERIOD_COUNTER));

    // nepretrzity pohyb doprava a dolu
    if (!get_pause()) {
        if (!timer.get_running()) {
            timer.start();
        }

        is_right = true;
        is_down = true;

        move();
    }

    std::unique_lock<std::mutex> lg(mutex);
    cvar.notify_all();
}

void mario_game::input() {
    std::unique_lock<std::mutex> lg(mutex);
    lg.unlock();

    if (quit)
        return;

    char c;
    std::cin >> c;

    if (c == 'w') {
        is_up = true;
        move();
        cvar.notify_one();
    } else if (c == 'a') {
        is_left = true;
        move();
        cvar.notify_one();
    } else if (c == 'd') {
        is_right = true;
        move();
        cvar.notify_one();
    } else if (c == 'q') {
        set_quit(true);
        cvar.notify_one();
    } else if (c == 'r') {
        set_pause(false);
        cvar.notify_one();
    } else if (c == 'p') {
        set_pause(true);
        cvar.notify_one();
    }
}

bool mario_game::get_quit() const {
    return quit;
}

void mario_game::set_quit(bool qq) {
    quit = qq;
}

bool mario_game::get_pause() const {
    return pause;
}

void mario_game::set_pause(bool pp) {
    pause = pp;
}

int mario_game::get_coins() const {
    return cur_coins;
}

void mario_game::plus_coin() {
    cur_coins++;
}

int mario_game::get_lives() const {
    return all_lives;
}

void mario_game::minus_live() {
    all_lives--;

    if (all_lives < 0)
        all_lives = 0;
}
