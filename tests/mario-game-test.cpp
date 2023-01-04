#include <thread>

#include "catch.hpp"
#include "../mario_game.hpp"

TEST_CASE("Test mario game") {

    SECTION("Konstruktor test") {
        mario_game game;
        REQUIRE(game.get_lives() == ARG_LIVES_DEFAULT);
        REQUIRE(game.get_coins() == 0);
        REQUIRE(game.get_pause());
        REQUIRE_FALSE(game.get_quit());
    }

    SECTION("Method get_random_position test") {
        mario_game game;
        size_t min = 0;
        size_t max = 100;
        size_t random_position = game.get_random_position(min, max);
        REQUIRE(random_position > min);
        REQUIRE(random_position < max);
    }

    SECTION("Method control test, prohral") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        REQUIRE(game.get_lives() == init_count_live);
        while (init_count_live > 0) {
            game.minus_live();
            init_count_live--;
        }
        REQUIRE(game.get_lives() == 0);
        game.minus_live();
        REQUIRE(game.get_lives() == 0);
    }

    SECTION("Method control test, vyhral") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        REQUIRE(game.get_lives() == init_count_live);
        REQUIRE(game.get_lives() > 0);
        game.set_quit(true);
        REQUIRE(game.get_lives() > 0);
    }

    SECTION("Method plus_coin test") {
        mario_game game;
        REQUIRE(game.get_coins() == 0);
        game.plus_coin();
        REQUIRE(game.get_coins() == 1);
        game.plus_coin();
        game.plus_coin();
        game.plus_coin();
        REQUIRE(game.get_coins() == 4);
    }

    SECTION("Method minus_live test") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        REQUIRE(game.get_lives() == init_count_live);
        while (init_count_live > 0) {
            init_count_live--;
            game.minus_live();
            REQUIRE(game.get_lives() == init_count_live);
        }
        game.minus_live();
        REQUIRE(game.get_lives() == 0);
    }


}