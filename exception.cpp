#include "exception.hpp"

excpt::excpt(std::string s) : text(std::move(s)) {}