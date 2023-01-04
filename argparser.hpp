#ifndef MARIO_ARG_PARSER_H
#define MARIO_ARG_PARSER_H

#include <iostream>
#include <string>
#include <cstring>

#define ARG_COINS_DEFAULT 10
#define ARG_COINS_MIN 0
#define ARG_COINS_MAX 100

#define ARG_ENEMIES_DEFAULT 10
#define ARG_ENEMIES_MIN 0
#define ARG_ENEMIES_MAX 100

#define ARG_LIVES_DEFAULT 5
#define ARG_LIVES_MIN 0
#define ARG_LIVES_MAX 100

/*
 * Nastaveni a zruseni raw modu terminalu
 */
void set_raw(bool set);

/*
 * Struktura parametru a nastaveni programu
 */
struct program_arguments {
    int coins, enemies, lives;
};

class arg_parser {
public:

    /*
     * Parsovani argumentu programu:
     *  -c (-coins)   celkovy pocet minci
     *  -e (-enemies) celkovy pocet neprateli
     *  -l (-lives)   celkovy pocet zivotu
     */
    static program_arguments parse_program_arguments(int argc, char *argv[]);

private:

    /*
     * Prevod retezce na cele cislo
     */
    static int str2int(int *res, const char *str);
};

#endif //MARIO_ARG_PARSER_H