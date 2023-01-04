#ifndef MARIO_WINDOW_H
#define MARIO_WINDOW_H

#include <sstream>
#include <vector>
#include <chrono>
#include "timer.hpp"

#define ANSI_CLEAR "\x1B[2J\x1B[H"                  // mazani terminalu
#define ANSI_COLOR_RESET "\x1B[m"                   // reset barev
#define COLOR_RED   "\x1B[91m"                      // cervena barva
#define COLOR_GREEN "\x1B[92m"                      // zelena barva
#define COLOR_YELLOW "\x1b[33m"                     // zluta barva
#define COLOR_BLUE "\x1b[34m"                       // modra barva

#define BKG_GREEN   "\x1b[102m"                                  // zelene pozadi
#define COLOR_WIN   "\x1B[48;5;52m\x1B[38;5;208m"                // oranzova barva na hnedem pozadi pro vypis viteze
#define COLOR_DRAW  "\x1B[48;5;17m\x1B[38;5;75m"                 // blede modra barva na modrem pozadi pro vypis viteze

enum p_field {
    nothing,
    mario,
    earth,
    enemy,
    coin
};

class window {
public:

    /*
     * Konstruktor tridy
     */
    explicit window(std::ostream &outputStream, size_t width, size_t height);

    ~window() { outputStream << "Konec\n"; };
    /*
     * Prekresleni hraciho pole
     *
     * player_area - hraci pole
     * timer - casovac
     * coins - mince
     * lives
     */
    void redraw(std::vector<p_field> player_area, timer timer, int coins, int lives, bool pause);

    /*
     * Priprava textu nad hracim polem
     */
    void render_header(int coins, int lives);

    /*
     * Priprava textu pod hracim polem
     */
    void render_footer(bool pause);

    /*
     * Prekresleni hraciho pole
     */
    void render_window(std::vector<p_field> player_area);

    /*
     * Vypis informaci o vyslednem stavy hry - vyhre a remize
     */
    void redrawWIN(bool is_win);

private:
    std::ostream &outputStream;     // odkaz na vystupni proud (std::cout)
    std::string text;               // text vypisovany pod hraci plochou
    std::string time;               // text o uplynulem case
    size_t width, height;           // rozmery hraci plochy
};

#endif //MARIO_WINDOW_H
