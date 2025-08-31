#pragma once

#include <cstdint>

class Snapshot {
public:
    void                   setTime(uint64_t time) { _time = time; }
    [[nodiscard]] uint64_t time() const { return _time; }

    void                   setHeap(uint64_t heap) { _heap = heap; }
    [[nodiscard]] uint64_t heap() const { return _heap; }

    void                   setHeapExtra(uint64_t heapExtra) { _heapExtra = heapExtra; }
    [[nodiscard]] uint64_t heapExtra() const { return _heapExtra; }

    void                   setStacks(uint64_t stacks) { _stacks = stacks; }
    [[nodiscard]] uint64_t stacks() const { return _stacks; }

    void               setPeak() { _peak = true; }
    [[nodiscard]] bool peak() const { return _peak; }

private:
    uint64_t _time      = 0;
    uint64_t _heap      = 0;
    uint64_t _heapExtra = 0;
    uint64_t _stacks    = 0;
    bool     _peak      = false;
};
