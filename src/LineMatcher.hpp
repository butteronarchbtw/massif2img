#pragma once

#include "Snapshot.hpp"

#include <functional>
#include <string>

class LineMatcher {
public:
    LineMatcher() = delete;
    LineMatcher(std::string line, Snapshot& s) :
            _line(std::move(line)), _s(s) {};

    [[nodiscard]] bool matchSnapshotValues();
    [[nodiscard]] bool matchSnapshot(size_t& i);

private:
    std::string _line;
    Snapshot&   _s;

    bool _numberMatch(const std::string& lh, const std::function<void(size_t)>& set);
    bool _peakMatch();
};
