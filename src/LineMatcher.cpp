#include "LineMatcher.hpp"

#include "Logger.hpp"

#include <cstddef>
#include <stdexcept>
#include <string>

bool LineMatcher::_numberMatch(const std::string& lhs,
    const std::function<void(size_t)>&            set) {
    size_t equals = _line.find('=');
    if(equals == std::string::npos) {
        return false;
    }
    try {
        std::string before = _line.substr(0, equals);
        Logger::debug("got before {}", before);
        if(before != lhs) {
            return false;
        }
    } catch(std::out_of_range&) {
        return false;
    }
    try {
        std::string value = _line.substr(equals + 1);
        Logger::debug("value is {}", value);
        size_t val = static_cast<size_t>(std::stoul(value));
        set(val);
    } catch(std::out_of_range&) {
        Logger::debug("no = or right number found");
        return false;
    } catch(std::invalid_argument&) {
        Logger::debug("is not a number");
        return false;
    }
    return true;
}

bool LineMatcher::_peakMatch() {
    size_t equals = _line.find('=');
    if(equals == std::string::npos) {
        return false;
    }
    try {
        std::string after = _line.substr(equals + 1);
        if(after != "peak") {
            return false;
        }
    } catch(std::out_of_range&) {
        Logger::debug("no = found");
        return false;
    }
    try {
        std::string before = _line.substr(0, equals);
        if(before != "heap_tree") {
            return false;
        }
    } catch(std::out_of_range&) {
        Logger::debug("no heap_tree found");
        return false;
    }
    _s.setPeak();
    return true;
}

bool LineMatcher::matchSnapshotValues() {
    bool matches = false;
    matches |=
        _numberMatch("time", [&](uint64_t time) { _s.setTime(time); });
    matches |=
        _numberMatch("mem_heap_B", [&](uint64_t heap) { _s.setHeap(heap); });
    matches |= _numberMatch("mem_heap_extra_B", [&](uint64_t heapExtra) {
        _s.setHeapExtra(heapExtra);
    });
    matches |= _numberMatch("mem_stacks_B", [&](uint64_t stacks) { _s.setStacks(stacks); });
    matches |= _peakMatch();
    return matches;
}

bool LineMatcher::matchSnapshot(size_t& i) {
    bool match = _numberMatch("snapshot", [&](size_t r) { i = r; });
    if(match)
        Logger::debug("Matched snapshot {}", i);
    return match;
}
