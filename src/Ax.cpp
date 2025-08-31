#include "Ax.hpp"

#include <format>

std::string Ax::plot(const std::string& x, const std::string& y, const std::string& label) const {
    return std::format("{}.plot({}, {}, label='{}')\n", _name, x, y, label);
}

std::string Ax::yticks(const std::string& ticks, const std::string& labels) const {
    return std::format("{}.{}({}, {})\n", _name, _multiplot ? "set_yticks" : "yticks", ticks, labels);
}

std::string Ax::xlabel(const std::string& label) const {
    return std::format("{}.{}('{}')\n", _name, _multiplot ? "set_xlabel" : "xlabel", label);
}

std::string Ax::ylabel(const std::string& label) const {
    return std::format("{}.{}('{}')\n", _name, _multiplot ? "set_ylabel" : "ylabel", label);
}

std::string Ax::legend() const {
    return std::format("{}.legend()\n", _name);
}

std::string Ax::title(const std::string& title) const {
    return std::format("{}.{}('{}')\n", _name, _multiplot ? "set_title" : "title", title);
}
