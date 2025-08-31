#include "CSV.hpp"

#include <fstream>

void CSV::writeBlocks(const std::vector<Block>& blocks) {
    std::ofstream outFile = std::ofstream(_fileName);

    outFile << "id,heap,heap_extra,stacks,peak\n";
    for(const Block& block : blocks) {
        const Snapshot& snap = block.snapshot();

        outFile << block.id() << ',';
        outFile << snap.heap() << ',';
        outFile << snap.heapExtra() << ',';
        outFile << snap.stacks() << ',';
        outFile << std::boolalpha << snap.peak();
        outFile << '\n';
    }
    outFile.close();
}
