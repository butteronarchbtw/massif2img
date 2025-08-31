#pragma once

#include "Snapshot.hpp"

#include <cstddef>

class Block {
public:
    explicit Block(size_t id) :
            _id(id) {}
    void                          setSnapshot(const Snapshot& s) { _s = s; }
    [[nodiscard]] const Snapshot& snapshot() const { return _s; }

    [[nodiscard]] size_t id() const { return _id; }

private:
    size_t   _id;
    Snapshot _s;
};
