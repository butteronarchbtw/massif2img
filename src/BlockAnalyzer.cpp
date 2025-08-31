#include "BlockAnalyzer.hpp"

#include <algorithm>

template<typename Func>
static auto mapBlocks(const std::vector<Block>& from, Func extractValue) {
    using T = decltype(extractValue(std::declval<Block>()));
    std::vector<T> to;
    std::transform(from.cbegin(), from.cend(), std::back_inserter(to),
        extractValue);
    return to;
}

std::vector<size_t> BlockAnalyzer::x() const {
    return mapBlocks(_blocks, [](const Block& b) { return b.id(); });
}

std::vector<uint64_t> BlockAnalyzer::heap() const {
    return mapBlocks(_blocks, [](const Block& b) { return b.snapshot().heap(); });
}

std::vector<uint64_t> BlockAnalyzer::heapExtra() const {
    return mapBlocks(_blocks, [](const Block& b) { return b.snapshot().heapExtra(); });
}

std::vector<uint64_t> BlockAnalyzer::stacks() const {
    return mapBlocks(_blocks, [](const Block& b) { return b.snapshot().stacks(); });
}

uint64_t BlockAnalyzer::heapPeak() const {
    return std::ranges::find_if(_blocks, [](const Block& x) {
        return x.snapshot().peak();
    })->snapshot()
        .heap();
}

uint64_t BlockAnalyzer::stacksPeak() const {
    const auto& s = stacks();
    return *std::ranges::max_element(s);
}

bool BlockAnalyzer::plotStacks() const {
    const auto& s = stacks();
    return std::ranges::any_of(s, [](const uint64_t x) { return x != 0; });
}
