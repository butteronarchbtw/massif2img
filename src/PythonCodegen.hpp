#pragma once

#include "Ax.hpp"
#include "BlockAnalyzer.hpp"
#include "CSV.hpp"

#include <array>
#include <fstream>

class PythonCodegen {
public:
    PythonCodegen(CSV csv, BlockAnalyzer an) :
            _csv(std::move(csv)), _an(std::move(an)) {};
    void generateScript(const std::string& scriptFile, const std::string& outputFile);

private:
    static constexpr size_t StepCount = 5;

    CSV           _csv;
    BlockAnalyzer _an;
    std::ofstream _stream;

    static std::array<uint64_t, StepCount>    yTicks(uint64_t peak);
    static std::array<std::string, StepCount> yTickLabels(const std::array<uint64_t, StepCount>& yTicks);

    void _generateImports();
    void _generateLoadCSV();
    void _generatePlot(const Ax& ax, uint64_t peak);
    void _generateStackPlot(const Ax& ax);
    void _generateHeapPlot(const Ax& ax);
    void _generateSave(const std::string& to);
};
