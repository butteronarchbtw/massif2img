#include "MassifFile.hpp"

#include "LineMatcher.hpp"
#include "Logger.hpp"

#include <format>
#include <fstream>
#include <stdexcept>

std::vector<Block> MassifFile::parse() {
    std::string   line;
    std::ifstream file(_fileName);
    if(file.fail()) {
        std::string msg = std::format("could not open file {}", _fileName);
        Logger::error(msg);
        throw std::runtime_error(msg);
    }
    std::vector<Block> blocks;
    Snapshot           s;
    while(std::getline(file, line)) {
        LineMatcher m(line, s);

        size_t i = 0;
        if(m.matchSnapshot(i)) {
            Logger::debug("== snapshot {}", i);
            blocks.emplace_back(i);
            s = Snapshot();
            continue;
        }

        if(blocks.empty())
            continue;

        if(m.matchSnapshotValues())
            blocks.back().setSnapshot(s);
    }
    file.close();
    return blocks;
}
