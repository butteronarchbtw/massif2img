#include "Extension.hpp"

#include <unordered_map>

std::string Extension::to_extension(Ext e) {
    const std::unordered_map<Ext, std::string> map = {
        {Ext::PDF, ".pdf"},
        {Ext::CSV, ".csv"},
        {Ext::PY, ".py"},
    };

    return map.at(e);
}

std::string Extension::with_ext(const std::string& fileName, Ext e) {
    return fileName + to_extension(e);
}
