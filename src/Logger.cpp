#define RESET "\e[m"
#define BOLD  "\e[1m"

#define COLOR(n) "\e[38;5;" #n "m"
#define RED      COLOR(1)
#define GREEN    COLOR(2)

#define IN_BOLD_BRACKETS(text) BOLD "[" text RESET BOLD "]" RESET

#include "Logger.hpp"

#include <cstdarg>
#include <unordered_map>

std::string Logger::_getLabel(LogType type) {
    const std::unordered_map<LogType, std::string> map = {
        {LogType::DEBUG, IN_BOLD_BRACKETS(GREEN "debug")},
        {LogType::ERROR, IN_BOLD_BRACKETS(RED "error")},
    };

    return map.at(type);
}
