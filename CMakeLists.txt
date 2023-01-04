cmake_minimum_required(VERSION 3.5)
project(Mario LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(core-files
        window.cpp
        window.hpp
        argparser.cpp
        argparser.hpp
        timer.hpp
        timer.cpp
        exception.hpp
        exception.cpp)

add_executable(Mario
        main.cpp
        ${core-files})

set(main-test
        tests/tests-main.cpp)

add_executable(tests
        ${main-test}
        tests/timer-test.cpp
        ${core-files})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(Mario Threads::Threads)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    target_compile_options(Mario PRIVATE -Wall -Wextra -Wunreachable-code -Wpedantic)
endif ()
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    target_compile_options(Mario PRIVATE /W4)
endif ()


if (${CMAKE_VERSION} VERSION_GREATER 3.5)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Mario)
endif ()

enable_testing()
add_test(NAME timer COMMAND tests)