#include <thread>

#include "catch.hpp"
#include "../mario_game.hpp"

TEST_CASE("Test mario game", "[mario_game]") {

    SECTION("Konstruktor test") {
        mario_game game;
        REQUIRE(game.get_lives() == ARG_LIVES_DEFAULT);
        CHECK(game.get_coins() == 0);
        REQUIRE(game.get_pause());
        REQUIRE_FALSE(game.get_quit());
        int count_nothing = 0;
        int count_enemies = 0;
        int count_coins = 0;
        int count_earth = 0;
        int count_player = 0;
        for (auto p : game.get_playing_area()) {
            switch (p) {
                case nothing:
                    count_nothing++;
                    break;
                case earth:
                    count_earth++;
                    break;
                case enemy:
                    count_enemies++;
                    break;
                case mario:
                    count_player++;
                    break;
                case coin:
                    count_coins++;
                    break;
                default:
                    break;
            }
        }
        REQUIRE(count_player == 1);
        REQUIRE(count_enemies == ARG_ENEMIES_DEFAULT);
        REQUIRE(count_coins == ARG_COINS_DEFAULT);
        REQUIRE(count_earth == (DEFAULT_WIDTH - 1 + ARG_ENEMIES_DEFAULT * 3));
        REQUIRE(count_nothing == (game.get_playing_area().size() - count_coins - count_earth - count_player - count_enemies));
    }

    SECTION("Start, end game test") {
        mario_game game;
        REQUIRE(game.get_pause());
        game.set_quit(true);
        REQUIRE(game.get_quit());
    }

    SECTION("Method get_random_position test") {
        mario_game game;
        size_t min = 0;
        size_t max = 100;
        size_t random_position = game.get_random_position(min, max);
        CHECK(random_position > min);
        CHECK(random_position < max);
    }

    SECTION("Method control test, prohral") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        REQUIRE(game.get_lives() == init_count_live);
        while (init_count_live > 0) {
            game.minus_live();
            init_count_live--;
        }
        CHECK(game.get_lives() == 0);
        game.minus_live();
        CHECK(game.get_lives() == 0);
    }

    SECTION("Method control test, vyhral") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        CHECK(game.get_lives() == init_count_live);
        CHECK(game.get_lives() > 0);
        game.set_quit(true);
        CHECK(game.get_lives() > 0);
    }

    SECTION("Method plus_coin test") {
        mario_game game;
        CHECK(game.get_coins() == 0);
        game.plus_coin();
        CHECK(game.get_coins() == 1);
        game.plus_coin();
        game.plus_coin();
        game.plus_coin();
        CHECK(game.get_coins() == 4);
    }

    SECTION("Method plus_coin test, vyhral") {
        mario_game game;
        CHECK(game.get_coins() == 0);
        int coins = ARG_COINS_DEFAULT;
        while (coins > 0) {
            game.plus_coin();
            coins--;
        }
        CHECK(game.get_coins() == ARG_COINS_DEFAULT);
        REQUIRE(game.get_pause());
    }

    SECTION("Method minus_live test") {
        mario_game game;
        int init_count_live = ARG_LIVES_DEFAULT;
        CHECK(game.get_lives() == init_count_live);
        while (init_count_live > 0) {
            init_count_live--;
            game.minus_live();
            CHECK(game.get_lives() == init_count_live);
        }
        game.minus_live();
        CHECK(game.get_lives() == 0);
    }
}