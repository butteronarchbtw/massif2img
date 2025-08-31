#include "PythonCodegen.hpp"

#include "Logger.hpp"

#include <algorithm>
#include <cmath>
#include <sstream>

void PythonCodegen::_generateImports() {
    _stream << "import pandas as pd\n";
    _stream << "import matplotlib.pyplot as plt\n";
}

void PythonCodegen::_generateLoadCSV() {
    _stream << "df = pd.read_csv('" << _csv.fileName() << "')\n";
}

template<typename T>
static std::string pythonArray(const T& v, bool quoted = false) {
    std::stringstream ss;

    ss << "[";

    auto begin     = v.cbegin();
    auto end       = v.cend();
    auto wrapValue = [&ss, quoted](const auto& value) {
        if(quoted)
            ss << "'";
        ss << value;
        if(quoted)
            ss << "'";
    };

    wrapValue(*begin++);

    for(; begin != end; ++begin) {
        ss << ", ";
        wrapValue(*begin);
    }

    ss << "]";
    return ss.str();
}

std::array<uint64_t, PythonCodegen::StepCount> PythonCodegen::yTicks(uint64_t peak) {
    uint64_t                        tenth     = uint64_t(std::pow(10, std::floor(std::log10(peak))));
    uint64_t                        yTicksMax = uint64_t(std::ceil(double(peak) / double(tenth))) * tenth;
    const size_t                    stepCount = 5;
    const uint64_t                  step      = yTicksMax / stepCount;
    std::array<uint64_t, StepCount> yTicks;
    uint64_t                        init = 0;
    std::ranges::generate(yTicks, [init, step]() mutable {
        uint64_t t = init;
        init += step;
        return t;
    });

    return yTicks;
}

std::array<std::string, PythonCodegen::StepCount> PythonCodegen::yTickLabels(const std::array<uint64_t, PythonCodegen::StepCount>& yTicks) {
    std::array<std::string, PythonCodegen::StepCount> yTickLabels;
    for(size_t i = 0; i < yTicks.size(); ++i) {
        const auto&      tick  = yTicks.at(i);
        constexpr size_t gsize = 1e9;
        constexpr size_t msize = 1e6;
        constexpr size_t ksize = 1e3;

        std::stringstream ss;
        if(tick >= gsize) {
            ss << (double(tick) / gsize) << " G";
        } else if(tick >= msize) {
            ss << (double(tick) / msize) << " M";
        } else if(tick >= ksize) {
            ss << (double(tick) / ksize) << " K";
        } else {
            ss << double(tick);
        }
        yTickLabels.at(i) = (ss.str());
    }
    return yTickLabels;
}

void PythonCodegen::_generatePlot(const Ax& ax, uint64_t peak) {

    auto ticks      = yTicks(peak);
    auto tickLabels = yTickLabels(ticks);
    _stream << "yticks = " << pythonArray(ticks) << "\n";
    _stream << "ytick_labels = " << pythonArray(tickLabels, true) << "\n";
    _stream << ax.yticks("yticks", "ytick_labels");

    _stream << ax.xlabel("Snapshot");
    _stream << ax.ylabel("Memory Usage [B]");

    _stream << ax.legend();
}

void PythonCodegen::_generateStackPlot(const Ax& ax) {
    _stream << "stacks = df.stacks\n";
    _stream << ax.title("Stack Memory Usage");
    _stream << ax.plot("x", "stacks", "Stacks");
    _generatePlot(ax, _an.stacksPeak());
}

void PythonCodegen::_generateHeapPlot(const Ax& ax) {
    _stream << "heap = df.heap\n";
    _stream << "heap_extra = df.heap_extra\n";
    _stream << ax.title("Heap Memory Usage");
    _stream << ax.plot("x", "heap", "Heap");
    _stream << ax.plot("x", "heap_extra", "Heap Extra");
    _generatePlot(ax, _an.heapPeak());
}

void PythonCodegen::_generateSave(const std::string& to) {
    _stream << "plt.tight_layout()\n";
    _stream << "plt.savefig('" << to << "')\n";
}

void PythonCodegen::generateScript(const std::string& scriptFile, const std::string& outputFile) {
    // FIXME: error handling
    _stream.open(scriptFile);
    _generateImports();
    _generateLoadCSV();
    _stream << "x = df.id\n";
    if(_an.plotStacks()) {
        Logger::debug("plotting stacks");
        _stream << "fig, axs = plt.subplots(2)\n";
        _generateHeapPlot(Ax("axs[0]", true));
        _generateStackPlot(Ax("axs[1]", true));
    } else {
        Logger::debug("not plotting stacks");
        _generateHeapPlot(Ax("plt", false));
    }
    _generateSave(outputFile);
    _stream.close();
}
