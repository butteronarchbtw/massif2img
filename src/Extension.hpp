#pragma once

#define WITH_EXT(file, ext) Extension::with_ext(file, Ext::ext)

#include <cstdint>
#include <string>

enum class Ext : uint8_t {
    PDF,
    SVG,
    CSV,
    PY
};

class Extension {
public:
    static std::string with_ext(const std::string& fileName, Ext e);

private:
    static std::string to_extension(Ext e);
};
