#include "window.hpp"
#include "timer.hpp"
#include <iostream>
#include <chrono>
#include <utility>

window::window(std::ostream &os, size_t width, size_t height) :
        os(os),
        width(width),
        height(height) {}

void window::redraw(std::vector<p_field> player_area, timer timer, int coins, int lives, bool pause) {
    std::stringstream ss;
    ss << timer.elapsed_minutes() << ":" << timer.get_seconds();
    time = ss.str();
    render_header(coins, lives, pause);
    render_window(std::move(player_area));
}

void window::redrawWIN(bool is_win) {
    std::stringstream ss;
    if (is_win) {
        ss << COLOR_WIN << "\n\r   !!! VYHRAL !!!   \n" << ANSI_COLOR_RESET;
    } else {
        ss << COLOR_DRAW << "\n\r   === PROHRAL ===   \n" << ANSI_COLOR_RESET;
    }
    os << ss.str() << std::endl;
}

void window::render_header(int coins, int lives, bool pause) {
    std::stringstream ss;
    ss << COLOR_RED << "   LIVES: " << lives << ANSI_COLOR_RESET;
    ss << COLOR_YELLOW << "   COINS: " << coins << ANSI_COLOR_RESET;
    ss << "   TIME: " << time;
    ss << COLOR_BLUE << "   PAUSE: " << (pause ? "ON" : "OFF") << ANSI_COLOR_RESET;
    text = ss.str();
}

void window::render_window(std::vector<p_field> player_area) {
    std::stringstream buffer;
    buffer << ANSI_CLEAR << ANSI_COLOR_RESET;
    buffer << "\r";

    buffer << " ";
    for (size_t i = 0; i < width + 2; ++i)
        buffer << "-";
    buffer << std::endl;

    for (size_t j = 0; j < height; ++j) {
        buffer << "\r |";
        for (size_t i = 0; i < width; ++i) {
            switch (player_area[j * width + i]) {
                case nothing:
                    buffer << " ";
                    break;
                case earth:
                    buffer << BKG_GREEN << " " << ANSI_COLOR_RESET;
                    break;
                case mario:
                    buffer << COLOR_BLUE << "O" << ANSI_COLOR_RESET;
                    break;
                case enemy:
                    buffer << COLOR_RED << "*" << ANSI_COLOR_RESET;
                    break;
                case coin:
                    buffer << COLOR_YELLOW << "o" << ANSI_COLOR_RESET;
                    break;
                default:
                    break;
            }
        }
        buffer << "|";
        buffer << std::endl;
    }

    buffer << " ";
    for (size_t i = 0; i < width + 2; ++i)
        buffer << "-";
    buffer << std::endl;

    buffer << "\r" << std::noskipws << text;
    os << buffer.str() << std::endl;
}