#include "window.hpp"
#include "timer.hpp"
#include <iostream>
#include <chrono>
#include <utility>

Window::Window(std::ostream &outputStream, size_t width, size_t height) :
        outputStream(outputStream),
        width(width),
        height(height) {}


void Window::redraw(std::vector<p_field> player_area, timer timer, int coins, int lives) {
    std::stringstream ss;
    ss << timer.elapsed_minutes() << ":" << timer.get_seconds();
    time = ss.str();

    render_window(std::move(player_area));

    render_header(coins, lives);
}

void Window::redrawWIN(bool is_win) {
    if (is_win)
        outputStream << COLOR_WIN << "\n\r   !!! VYHRAL !!!   \n" << ANSI_COLOR_RESET;
    else
        outputStream << COLOR_DRAW << "\n\r   === PROHRAL ===   \n" << ANSI_COLOR_RESET;
}

void Window::render_header(int coins, int lives) {
    std::stringstream ss;
    ss << COLOR_GREEN << " SCORE: " << ANSI_COLOR_RESET;
    ss << COLOR_RED << "   LIVES: " << lives << ANSI_COLOR_RESET;
    ss << COLOR_YELLOW << "   COINS: " << coins << ANSI_COLOR_RESET;
    ss << "   TIME: " << time;

    text = ss.str();
}

void Window::render_window(std::vector<p_field> player_area) {
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
    outputStream << buffer.str() << std::endl;;
}