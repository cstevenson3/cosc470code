#include "ReconstructionConfig.hpp"

using std::cout;
using std::cin;
using std::string;

namespace ReconstructionConfig {

    Configuration configurecli()
    {
        Configuration config;
        config.dataFormat = inputDataFormat();
        config.filePrefix = inputFilenamePrefix();
        if (config.dataFormat == DataFormat::whiteSpaceFormatted) {
            return config;
        }
        config.contour.minSize = inputMinContourSize();
        config.contour.maxSize = inputMaxContourSize();
        config.contour.scaling = 0.625; // Hardcoded value.
        config.slices.min = inputMinSlices();
        config.slices.max = inputMaxSlices();
        config.slices.height = 1.25;  // Hardcoded value.
        return config;
    }

    DataFormat inputDataFormat()
    {
        std::string dataFormatStr;
        cout << "Input data format (\"real\", \"new\", \"alttest\", or \"test\")\n";
        cin >> dataFormatStr;
        if (dataFormatStr == "real") {
            return DataFormat::realContourFormatted;
        }
        if (dataFormatStr == "test") {
            return DataFormat::whiteSpaceFormatted;
        }
        if (dataFormatStr == "new") {
            return DataFormat::realNewFormat;
        }
        if (dataFormatStr == "alttest") {
            return DataFormat::altTestFormat;
        }
        cout << "Unknown data format provided. Defaulting to test format";
        return DataFormat::whiteSpaceFormatted;
    }

// Gets a user to input a number of minimum slice indices. Returns this number.
    unsigned int inputMinSlices()
    {
        unsigned int minSlices;
        cout << "Enter min slice indices: ";
        cin >> minSlices;
        return minSlices;
    }

// Gets a user to input a number of maximum slice indices. Returns this number.
    unsigned int inputMaxSlices()
    {
        unsigned int maxSlices;
        cout << "Enter max slice indices: ";
        cin >> maxSlices;
        return maxSlices;
    }

// Gets a user to input the minimum contour size to process. Returns this number.
    unsigned int inputMinContourSize()
    {
        unsigned int minContourSize;
        cout << "Enter min contour size: ";
        cin >> minContourSize;
        return minContourSize;
    }

// Gets a user to input the maximum contour size to process. Returns this number.
    unsigned int inputMaxContourSize()
    {
        unsigned int maxContourSize;
        cout << "Enter max contour size: ";
        cin >> maxContourSize;
        return maxContourSize;
    }

// Gets a file prefix. Processing expects files with prefix and slice index as the filename.
    string inputFilenamePrefix()
    {
        string filePrefix;
        cout << "Enter filename (or just prefix for split data): ";
        cin >> filePrefix;
        return filePrefix;
    }
}  // namespace ReconstructionConfig.