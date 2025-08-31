#pragma once
#include "Block.hpp"

#include <string>
#include <vector>

class MassifFile {
public:
    MassifFile() = delete;
    explicit MassifFile(std::string fileName) :
            _fileName(std::move(fileName)) {};

    std::vector<Block> parse();

    [[nodiscard]] const std::string& name() const {
        return _fileName;
    }

private:
    std::string _fileName;
};
