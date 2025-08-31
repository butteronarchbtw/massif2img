#pragma once

#include "Block.hpp"
#include "Logger.hpp"
#include "MassifFile.hpp"

#include <cstdint>
#include <vector>

class BlockAnalyzer {
public:
    explicit BlockAnalyzer(std::string fileName) :
            _file(MassifFile(std::move(fileName))) {
        _blocks = _file.parse();
        Logger::debug("read {} blocks", _blocks.size());
    }

    [[nodiscard]] std::vector<size_t>   x() const;
    [[nodiscard]] std::vector<uint64_t> heap() const;
    [[nodiscard]] std::vector<uint64_t> heapExtra() const;
    [[nodiscard]] std::vector<uint64_t> stacks() const;
    [[nodiscard]] uint64_t              heapPeak() const;
    [[nodiscard]] uint64_t              stacksPeak() const;
    [[nodiscard]] bool                  plotStacks() const;

    [[nodiscard]] const MassifFile& file() const {
        return _file;
    }

    [[nodiscard]] const std::vector<Block>& blocks() const {
        return _blocks;
    }

private:
    std::vector<Block> _blocks;
    MassifFile         _file;
};
