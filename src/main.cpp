#include "BlockAnalyzer.hpp"
#include "CSV.hpp"
#include "Extension.hpp"
#include "Logger.hpp"
#include "PythonCodegen.hpp"

int main(int argc, const char** argv) {
    if(argc <= 1) {
        Logger::error("not enough arguments supplied");
        return 1;
    }

    std::string fileName = argv[1];

    BlockAnalyzer an(fileName);

    Logger::debug("peakHeap is {}", an.heapPeak());

    CSV csv(WITH_EXT(fileName, CSV));
    csv.writeBlocks(an.blocks());

    std::string   pythonFileName = WITH_EXT(fileName, PY);
    std::string   outputFileName = WITH_EXT(fileName, PDF);
    PythonCodegen py(csv, an);
    py.generateScript(pythonFileName, outputFileName);

    return 0;
}
