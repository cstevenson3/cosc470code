#include "Contours.hpp"

namespace Contours {
    using std::string;
    using std::vector;
    using std::pair;

    namespace {
        uint64_t findLowestXVal(const vector<glm::vec3>& points, Contour contour)
        {
            double lowestXVal = std::numeric_limits<double>::infinity();
            uint64_t lowestIndex = 0;
            for (uint64_t i=0;i < contour.size(); i++) {
                if (points[contour[i]].x < lowestXVal) {
                    lowestIndex = i;
                    lowestXVal = points[contour[i]].x;
                }
            }

            return lowestIndex;
        }

        uint64_t findClosestIndex(const vector<glm::vec3>& points, glm::vec3 point, Contour contour)
        {
            float shortestDist = std::numeric_limits<float>::infinity();
            uint64_t closest = 0;
            for (uint64_t i = 0; i < contour.size(); i++) {
                float distance = glm::distance(point, points[contour[i]]);
                if (distance < shortestDist) {
                    closest = i;
                    shortestDist = distance;
                }
            }

            return closest;
        }

        // Loads test contours in alternative format.
        vector<vector<glm::vec3>> loadContoursAlt(const std::string& filename,
                ReconstructionConfig::Configuration config, int sliceNum)
        {
            vector<vector<glm::vec3>> contourList;

            const double contourHeight = 30.0f * sliceNum;  // Hard-coded value.

            std::ifstream inputFile;
            inputFile.open(filename.c_str(), std::ios::in);
            if (!inputFile) {
                throw std::invalid_argument("File: " + filename + " does not exist");
            }

            for(int numPoints; inputFile >> numPoints; ) {
                vector<glm::vec3> contour;
                for (int i = 0; i < numPoints; i++) {
                    double originX, originY;
                    inputFile >> originX >> originY;
                    std::cout << "x: " << originX << ", y: " << originY << "\n";
                    glm::vec3 current{originX, contourHeight, originY};

                    contour.emplace_back(current);
                }

                if (contour.size() > config.contour.minSize && contour.size() < config.contour.maxSize) {
                    contourList.emplace_back(contour);
                }

                std::cout << numPoints << " points\n";
                std::cout << contourList.size() << " contours\n";
            }

            return contourList;
        }

        // Loads real contours.
        vector<vector<glm::vec3>> loadContoursFromReal(const std::string& filename,
                ReconstructionConfig::Configuration config, int sliceNum)
        {
            vector<vector<glm::vec3>> contourList;

            // This makes assumptions about what the offsets correspond to.
            const double xOffset[] = {1, 1, 0, -1, -1, -1, 0, 1};
            const double yOffset[] = {0, 1, 1, 1, 0, -1, -1, -1};

            const double pixelSpacing = config.contour.scaling;
            const double contourHeight = config.slices.height * sliceNum;

            std::ifstream inputFile;
            inputFile.open(filename.c_str(), std::ios::in);
            if (!inputFile){
                throw std::invalid_argument("File: "+ filename + " does not exist");
            }

            int numContours;
            inputFile >> numContours;

            for (int i = 0; i < numContours ; i++){
                // Current contour.
                vector<glm::vec3> contour;
                int contourSize;
                inputFile >> contourSize;

                double originX, originY;
                inputFile >> originX >> originY;

                // Set the initial x and y values.
                double xCurrent = (originX) * pixelSpacing;
                double yCurrent = (originY) * pixelSpacing;

                // Skipping the first value as the last value is the same.
                for (auto j = 2; j < contourSize; j++){
                    gsl::index offset;
                    inputFile >> offset;
                    xCurrent += gsl::at(xOffset, offset) * pixelSpacing;
                    yCurrent += gsl::at(yOffset, offset) * pixelSpacing;

                    const glm::vec3 current{xCurrent, contourHeight, yCurrent};
                    contour.emplace_back(current);
                }

                if (contour.size() > config.contour.minSize && contour.size() < config.contour.maxSize) {
                    contourList.emplace_back(contour);
                }
            }

            inputFile.close(); // close the input file

            return contourList;
        }

        vector<vector<glm::vec3>> loadContoursNew(const std::string& filename,
                                                  ReconstructionConfig::Configuration config, int sliceNum) {
            vector<vector<glm::vec3>> contourList;

            // This makes assumptions about what the offsets correspond to.
            const double xOffset[] = {1, 1, 0, -1, -1, -1, 0, 1};
            const double yOffset[] = {0, 1, 1, 1, 0, -1, -1, -1};

            const double pixelSpacing = config.contour.scaling;
            const double contourHeight = config.slices.height * sliceNum;

            std::ifstream inputFile;
            inputFile.open(filename.c_str(), std::ios::in);
            if (!inputFile){
                throw std::invalid_argument("File: "+ filename + " does not exist");
            }

            // Just process the old contour num that is unused.
            int oldNum;
            inputFile >> oldNum;

            int contourSize;
            inputFile >> contourSize;
            while (contourSize > 0) {
                vector<glm::vec3> contour;
                double originX, originY;
                inputFile >> originX >> originY;

                // Set the initial x and y values.
                double xCurrent = (originX) * pixelSpacing;
                double yCurrent = (originY) * pixelSpacing;

                // Skipping the first value as the last value is the same.
                for (auto j = 2; j < contourSize; j++){
                    gsl::index offset;
                    inputFile >> offset;

                    if (offset < 0 ) {
                        std::cout << "Contour num: " << sliceNum << "\n";
                        throw ReconstructionErrors::ContourProcessingError();
                    }
                    xCurrent += gsl::at(xOffset, offset) * pixelSpacing;
                    yCurrent += gsl::at(yOffset, offset) * pixelSpacing;
                    const glm::vec3 current{xCurrent, contourHeight, yCurrent};
                    contour.emplace_back(current);
                }

                if (contour.size() > config.contour.minSize && contour.size() < config.contour.maxSize) {
                    contourList.emplace_back(contour);
                }

                inputFile >> contourSize;
            }


            inputFile.close(); // close the input file

            return contourList;
        }

        bool checkContoursWithinExpectedSize(const Contour& c1, const Contour& c2) {
            auto c1size = static_cast<float>(c1.size());
            auto c2size = static_cast<float>(c2.size());

            auto ratio = c1size / c2size;

            float upperThreshold = 10.0;
            float lowerThreshold = 0.0;

            return (ratio > lowerThreshold && ratio < upperThreshold);
        }
    }  // namespace.

    namespace Extremities {
        float maxDistanceFromCentroid(const vector<glm::vec3>& points, const Contour& contour)
        {
            auto centroid = computeCentroid(points, contour);
            float maxDistance = -std::numeric_limits<float>::infinity();

            for (auto pointIndex: contour) {
                auto distance = glm::distance(centroid, points[pointIndex]);
                if (distance > maxDistance) {
                    maxDistance = distance;
                }
            }

            return maxDistance;
        }
    }  // namespace Extremities.

    vector<Contour> findContoursWithinRange(const vector<glm::vec3>& points, const Contour& contour, vector<Contour> toMatch)
    {
        vector<Contour> matched;

        if (toMatch.empty()) {
            throw NotImplemented();
        }

        auto centroid = computeCentroid(points, contour);

        for (auto& neighbour : toMatch) {
            auto neighbourCentroid = computeCentroid(points, neighbour);
            float maxDistance = Extremities::maxDistanceFromCentroid(points, contour) +
                                Extremities::maxDistanceFromCentroid(points, neighbour);
            if (PointUtil::pointDistanceWithinThreshold2d(centroid, neighbourCentroid, maxDistance)){
                if (checkContoursWithinExpectedSize(contour, neighbour)) {
                    matched.emplace_back(neighbour);
                }
            }
        }

        return matched;
    }

    vector<uint64_t> findContourIndicesWithinRange(const vector<glm::vec3>& points,
            const Contour& contour,
            vector<Contour> toMatch)
    {
        vector<uint64_t> matched;

        if(toMatch.empty()){
            throw NotImplemented();
        }

        auto centroid = computeCentroid(points, contour);

        for (uint64_t i = 0; i < toMatch.size(); i++) {
            auto neighbourCentroid = computeCentroid(points, toMatch[i]);
            float maxDistance = Extremities::maxDistanceFromCentroid(points, contour) +
                                Extremities::maxDistanceFromCentroid(points, toMatch[i]) * 1.2f;
            if (PointUtil::pointDistanceWithinThreshold2d(centroid, neighbourCentroid, maxDistance)){
                if (checkContoursWithinExpectedSize(contour, toMatch[i])) {
                    matched.emplace_back(i);
                }
            }
        }

        return matched;
    }

    Contour findClosestContour(const vector<glm::vec3>& points, Contour contour, vector<Contour> toMatch)
    {
        if (toMatch.empty()) {
            throw NotImplemented();
        }

        float closest = std::numeric_limits<float>::infinity();
        auto sourceCentroid = computeCentroid(points, std::move(contour));
        Contour closestContour;

        for (auto& neighbour : toMatch) {
            auto distance = glm::distance(computeCentroid(points, neighbour), sourceCentroid);
            if (distance < closest) {
                closest = distance;
                closestContour = neighbour;
            }
        }

        return closestContour;
    }


    glm::vec3 computeCentroid(const vector<glm::vec3>& points, Contour contour)
    {
        glm::vec3 centroid{0.0, 0.0, 0.0};

        for (auto pointIndex : contour) {
            centroid += points[pointIndex];
        }

        if (contour.empty()) {
            std::cout << "Returning 0 vector for empty contour centroid computation.\n";
        } else {
            centroid /= contour.size();
        }

        return centroid;
    }

    //
    pair<uint64_t, uint64_t> findLowestXIndices(const vector<glm::vec3>& points, Contour c1, Contour c2)
    {
        uint64_t c1Lowest = findLowestXVal(points, c1);
        uint64_t c2Lowest = findLowestXVal(points, c2);

        return std::make_pair(c1Lowest, c2Lowest);
    }


    pair<uint64_t, uint64_t> findClosestIndices(const vector<glm::vec3>& points, Contour c1, Contour c2)
    {
        float shortestDist = std::numeric_limits<float>::infinity();
        pair<uint64_t, uint64_t> closestPair = std::make_pair(0, 0);

        for (uint64_t i = 0; i < c1.size(); i++) {
            auto closest = findClosestIndex(points, points[c1[i]], c2);
            float distance = glm::distance(points[c1[i]], points[c2[closest]]);
            if (distance < shortestDist) {
                closestPair = std::make_pair(i, closest);
                shortestDist = distance;
            }
        }

        return closestPair;
    }

    pair<uint64_t, uint64_t> findOmitIndices(const vector<glm::vec3>& points, Contour c1, Contour c2)
    {
        auto closest = findClosestIndices(points, c1, c2);
        auto globalIndexPair = std::make_pair(c1[closest.first], c2[closest.second]);

        return globalIndexPair;
    }

    pair<uint64_t, uint64_t> findNextIndices(const vector<glm::vec3>& points, Contour c1, Contour c2)
    {
        auto closest = findClosestIndices(points, c1, c2);
        auto globalIndexPair = std::make_pair(c1[closest.first+1], c2[closest.second+1]);

        return globalIndexPair;
    }

    Contour reorderContourFrom(const Contour& contour, uint64_t index)
    {
        Contour reordered;

        for (uint64_t i = index; i < contour.size(); i++) {
            reordered.emplace_back(contour[i]);
        }

        for (uint64_t j = 0; j <= index && j < contour.size(); j++){
            reordered.emplace_back(contour[j]);
        }

        return reordered;
    }


    // Expects the point to be formatted as "x y z" eg "0.0 1.0 3.0".
    glm::vec3 getPointCommaSeparated(string pointStr) {
        boost::trim(pointStr);
        vector<string> substrings;
        boost::split(substrings, pointStr, boost::is_any_of(","));

        if (substrings.size() != 3) {
            throw ReconstructionErrors::PointParsingError();
        }

        auto x = std::stof(substrings[0]);
        auto y = std::stof(substrings[1]);
        auto z = std::stof(substrings[2]);

        return glm::vec3{x, y, z};
    }

    vector<glm::vec3> loadContour(string contourStr) {
        boost::trim(contourStr);
        vector<string> substrings;
        boost::split(substrings, contourStr, boost::is_any_of("\t "));

        std::vector<glm::vec3> newContour;
        for (auto& point: substrings) {
            if (!(std::all_of(contourStr.begin(), contourStr.end(), isspace))) {
                auto currentPoint = getPointCommaSeparated(point);
                newContour.emplace_back(currentPoint);
            }
        }

        return newContour;
    }

    vector<vector<glm::vec3>> loadContourList(string line) {
        boost::trim(line);
        vector<string> substrings;
        boost::split(substrings, line, boost::is_any_of(";"));

        vector<vector<glm::vec3>> contourList;
        for (auto& contourStr : substrings) {
            auto newContour = loadContour(contourStr);
            if (!newContour.empty()) {
                contourList.emplace_back(newContour);
            }
        }

        return contourList;
    }

    Stack processContours(vector<vector<vector<glm::vec3>>> rawData) {
        Stack contourStack;

        std::vector<ContourList> contours;
        uint64_t index = 0;
        for (auto& contourList : rawData) {
            ContourList currentContourList;
            for (auto& contour : contourList) {
                Contour currentContour;
                for (auto point : contour) {
                    contourStack.points.emplace_back(point);
                    currentContour.emplace_back(index);
                    index++;
                }
                currentContourList.emplace_back(currentContour);
            }
            contourStack.contours.emplace_back(currentContourList);
        }

        return contourStack;
    }


    Stack loadRealFormatted(ReconstructionConfig::Configuration config)
    {
        std::vector<std::vector<std::vector<glm::vec3>>> contourStackData;

        for (unsigned int i = config.slices.min; i < config.slices.max; i++){
            std::stringstream extension(std::ios_base::in | std::ios_base::out);
            extension << std::setw(3) << std::setfill('0') << i;
            string currentFile = config.filePrefix + extension.str() + ".txt";
            auto rawContours = loadContoursFromReal(currentFile, config, i);
            contourStackData.emplace_back(rawContours);
        }

        Stack contourStack = processContours(contourStackData);
        return contourStack;
    }


    Stack loadRealNewFormat(ReconstructionConfig::Configuration config)
    {
        std::vector<std::vector<std::vector<glm::vec3>>> contourStackData;
        for (unsigned int i = config.slices.min; i < config.slices.max; i++) {
            std::stringstream extension(std::ios_base::in | std::ios_base::out);
            extension << std::setw(3) << std::setfill('0') << i;
            string currentFile = config.filePrefix + extension.str() + ".txt";
            auto rawContours = loadContoursNew(currentFile, config, i);
            contourStackData.emplace_back(rawContours);
        }

        Stack contourStack = processContours(contourStackData);
        return contourStack;
    }


    // Expects points with values space separated.
    // A empty line denotes end of contour. Two denotes end of slice(contour list).
    Stack loadWhitepaceFormatted(const string& filename) {
        std::vector<std::vector<std::vector<glm::vec3>>> contourStackData;
        std::ifstream inputFile(filename, std::ios_base::in);
        if (!inputFile.good()){
            throw std::invalid_argument("File: "+ filename + " does not exist");
        }

        string line;
        while (getline(inputFile, line)) {
            if (!(std::all_of(line.begin(), line.end(), isspace))) {
                auto rawContours = loadContourList(line);
                contourStackData.emplace_back(rawContours);
            }
        }
        Stack contourStack = processContours(contourStackData);
        return processContours(contourStackData);
    }

    Stack loadAltTestFormat(ReconstructionConfig::Configuration config)
    {
        std::vector<std::vector<std::vector<glm::vec3>>> contourStackData;

        for (unsigned int i = config.slices.min; i < config.slices.max; i++){
            std::stringstream extension(std::ios_base::in | std::ios_base::out);
            extension << i;
            string currentFile = config.filePrefix + extension.str() + ".txt";
            auto rawContours = loadContoursAlt(currentFile, config, i);
            contourStackData.emplace_back(rawContours);
        }

        Stack contourStack = processContours(contourStackData);
        return contourStack;
    }

    Contour mergeContours(const vector<glm::vec3>& points, const Contour& c1, const Contour& c2)
    {
        Contour merged;

        auto closest = findClosestIndices(points, c1, c2);

        Contour reordered1 = reorderContourFrom(c1, closest.first);
        Contour reordered2 = reorderContourFrom(c2, closest.second);

        merged.insert(merged.end(), reordered1.begin(), reordered1.end() );
        merged.insert(merged.end(), reordered2.begin(), reordered2.end() );

        return merged;
    }

    std::string Stack::toString()
    {
        std::string stackString{"Number of points: "};
        stackString += std::to_string(points.size());
        stackString += "\nNumber of contour lists: ";
        stackString += std::to_string(contours.size());
        stackString += '\n';

        return stackString;
    }
}  // namespace Contours.