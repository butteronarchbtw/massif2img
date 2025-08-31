#include "Block.hpp"
#include "MassifFile.hpp"
#include "Snapshot.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/generators/catch_generators.hpp>
#include <cctype>
#include <cstdint>

#define private public

#include "Extension.hpp"

TEST_CASE("Extension::EnumToString", "[Extension]") {
    CHECK(Extension::to_extension(Ext::PDF) == ".pdf");
    CHECK(Extension::to_extension(Ext::CSV) == ".csv");
    CHECK(Extension::to_extension(Ext::PY) == ".py");
}

TEST_CASE("Snaphot::Snapshot", "[Snapshot]") {
    Snapshot s;
    CHECK(s.time() == 0);
    CHECK(s.heap() == 0);
    CHECK(s.heapExtra() == 0);
    CHECK(s.stacks() == 0);
    CHECK(s.peak() == false);

    auto val = GENERATE(values<uint64_t>({0, 42, UINT64_MAX}));
    s.setTime(val);
    CHECK(s.time() == val);
    CHECK(s.heap() == 0);
    CHECK(s.heapExtra() == 0);
    CHECK(s.stacks() == 0);
    CHECK(s.peak() == false);
    s.setHeap(val);
    CHECK(s.time() == val);
    CHECK(s.heap() == val);
    CHECK(s.heapExtra() == 0);
    CHECK(s.stacks() == 0);
    CHECK(s.peak() == false);
    s.setHeapExtra(val);
    CHECK(s.time() == val);
    CHECK(s.heap() == val);
    CHECK(s.heapExtra() == val);
    CHECK(s.stacks() == 0);
    CHECK(s.peak() == false);
    s.setStacks(val);
    CHECK(s.time() == val);
    CHECK(s.heap() == val);
    CHECK(s.heapExtra() == val);
    CHECK(s.stacks() == val);
    CHECK(s.peak() == false);
    s.setPeak();
    CHECK(s.time() == val);
    CHECK(s.heap() == val);
    CHECK(s.heapExtra() == val);
    CHECK(s.stacks() == val);
    CHECK(s.peak() == true);

	constexpr size_t bID = 123;
	Block b(bID);
	const Snapshot& bs = b.snapshot();
    CHECK(bs.time() == 0);
    CHECK(bs.heap() == 0);
    CHECK(bs.heapExtra() == 0);
    CHECK(bs.stacks() == 0);
    CHECK(bs.peak() == false);
	b.setSnapshot(s);
    CHECK(bs.time() == val);
    CHECK(bs.heap() == val);
    CHECK(bs.heapExtra() == val);
    CHECK(bs.stacks() == val);
    CHECK(bs.peak() == true);
}

TEST_CASE("MassifFile::Parse", "[MassifFile]") {
	MassifFile file("massif.1.out");
	std::vector<Block> blocks = file.parse();
	CHECK(blocks.size() == 68);
	CHECK(blocks[0].snapshot().time() == 0);
	CHECK(blocks[0].snapshot().heap() == 0);
	CHECK(blocks[0].snapshot().heapExtra() == 0);
	CHECK(blocks[0].snapshot().stacks() == 0);
	CHECK(blocks[0].snapshot().peak() == false);

	CHECK(blocks[1].snapshot().time() == 38050747);
	CHECK(blocks[1].snapshot().heap() == 5304877);
	CHECK(blocks[1].snapshot().heapExtra() == 125891);
	CHECK(blocks[1].snapshot().stacks() == 74128);
	CHECK(blocks[1].snapshot().peak() == true);
}
