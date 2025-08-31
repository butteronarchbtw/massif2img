#pragma once

#include "Block.hpp"

#include <string>
#include <utility>
#include <vector>

class CSV {
public:
    CSV() = delete;
    explicit CSV(std::string fileName) :
            _fileName(std::move(fileName)) {}

    void                             writeBlocks(const std::vector<Block>& blocks);
    [[nodiscard]] const std::string& fileName() const { return _fileName; }

private:
    const std::string _fileName;
};
