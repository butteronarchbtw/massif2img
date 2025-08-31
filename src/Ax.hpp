#pragma once

#include <string>

class Ax {
public:
    Ax(std::string name, bool multi) :
            _name(std::move(name)), _multiplot(multi) {};

    [[nodiscard]] std::string plot(const std::string& x, const std::string& y, const std::string& label) const;

    [[nodiscard]] std::string yticks(const std::string& ticks, const std::string& labels) const;

    [[nodiscard]] std::string xlabel(const std::string& label) const;

    [[nodiscard]] std::string ylabel(const std::string& label) const;

    [[nodiscard]] std::string legend() const;

    [[nodiscard]] std::string title(const std::string& title) const;

private:
    std::string _name;
    bool        _multiplot = false;
};
