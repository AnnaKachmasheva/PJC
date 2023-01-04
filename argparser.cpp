#include "argparser.hpp"

program_arguments arg_parser::parse_program_arguments(int argc, char *argv[]) {
    auto parsedProgramArguments = program_arguments{ARG_COINS_DEFAULT, ARG_ENEMIES_DEFAULT, ARG_LIVES_DEFAULT};
    for (int i = 1; i < argc; i += 2) {
        int tmp;
        if (std::strlen(argv[i]) > 1)
            switch (argv[i][1]) {
                case 'c':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-coins")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= ARG_COINS_MIN && tmp <= ARG_COINS_MAX)
                        parsedProgramArguments.coins = tmp;
                    break;
                case 'e':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-enums")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= ARG_ENEMIES_MIN && tmp <= ARG_ENEMIES_MAX)
                        parsedProgramArguments.enemies = tmp;
                    break;
                case 'l':
                    if ((std::strlen(argv[i]) <= 2 || !std::strcmp(argv[i], "-lives")) &&
                        str2int(&tmp, argv[i + 1]) >= 0 && tmp >= ARG_LIVES_MIN && tmp <= ARG_LIVES_MAX)
                        parsedProgramArguments.lives = tmp;
                    break;
                default:
                    break;
            }
    }
    return parsedProgramArguments;
}

int arg_parser::str2int(int *res, const char *str) {
    try {
        *res = std::stoi(str);
    } catch (const std::invalid_argument &e) {
        return -1;
    } catch (const std::out_of_range &e) {
        return -2;
    }
    return 0;
}

void set_raw(bool set) {
    if (set) {
        system("stty raw");  // enable raw
    } else {
        system("stty -raw"); // disable raw
    }
}