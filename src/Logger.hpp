#pragma once

#include <cstdint>
#include <format>
#include <iostream>
#include <string>
#include <string_view>

class Logger {
public:
    template<typename... Args>
    static void debug([[maybe_unused]] const std::string_view& fmt, [[maybe_unused]] Args... args) {
#ifndef NDEBUG
        _format(LogType::DEBUG, fmt, args...);
#endif
    }

    template<typename... Args>
    static void error(const std::string_view& fmt, Args... args) {
        _format(LogType::ERROR, fmt, args...);
    }

private:
    enum class LogType : uint8_t {
        DEBUG,
        ERROR,
    };

    static std::string _getLabel(LogType type);

    template<typename... Args>
    static void _format(LogType type, const std::string_view& fmt, Args... args) {
        std::cerr << _getLabel(type) << " " << std::vformat(fmt, std::make_format_args(args...)) << std::endl;
    }
};
