#include <thread>

#include "catch.hpp"
#include "../timer.hpp"

TEST_CASE("Test timer", "[tests][running]") {

    SECTION("Start and stop method") {
        timer t;
        t.start();
        REQUIRE(t.get_running());
        t.stop();
        REQUIRE_FALSE(t.get_running());
    }

    SECTION("Elapsed seconds") {
        timer t;
        t.start();
        auto mls = 10000;
        std::chrono::milliseconds timespan(mls);
        std::this_thread::sleep_for(timespan);
        REQUIRE(t.elapsed_seconds() == 10);
        t.stop();
        REQUIRE(t.elapsed_seconds() == 10);
    }

    SECTION("Elapsed minutes") {
        timer t;
        t.start();
        auto mls = 60000;
        std::chrono::milliseconds timespan(mls);
        std::this_thread::sleep_for(timespan);
        REQUIRE(t.elapsed_minutes() == 1);
        t.stop();
        REQUIRE(t.elapsed_minutes() == 1);
    }

    SECTION("Get minutes and seconds") {
        timer t;
        t.start();
        auto mls = 61000;
        std::chrono::milliseconds timespan(mls);
        std::this_thread::sleep_for(timespan);
        t.stop();
        REQUIRE(t.elapsed_minutes() == 1);
        REQUIRE(t.get_seconds() == 1);
    }
}