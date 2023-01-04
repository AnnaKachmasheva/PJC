#include <thread>
#include <condition_variable>
#include "argparser.hpp"
#include "mario_game.hpp"

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