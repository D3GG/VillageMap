#include "FileManager.h"
#include "TouristObjFactory.h"

#include <sstream>

namespace FileManager {

void createFile(std::string fileName) {
    std::ofstream output(fileName);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to create a file");
    }

    output.close();
}

std::vector<std::string> removeDelimAndTokenize(const std::string& input,
                                                std::vector<std::string>& settlementData) {
    std::vector<std::string> touristObjData;
    std::istringstream stream(input);
    std::string currToken;

    std::size_t index = 0;
    while (std::getline(stream, currToken, '|')) {
        if (index < 5) {
            if (currToken == "Settlement") {
                index++;
                continue;
            }
            settlementData.push_back(currToken);
        }

        touristObjData.push_back(currToken);
    }

    return touristObjData;
}

Settlement loadFile(std::string fileName) {
    std::ifstream input(fileName);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open a file for reading");
    }
    std::string line;
    std::getline(input, line);

    std::vector<std::string> settlementData;
    std::vector<std::string> touristObjData = removeDelimAndTokenize(line, settlementData);
    Settlement newSettlement(settlementData.at(0), settlementData.at(1),
                             std::stoi(settlementData.at(2)), settlementData.at(3));

    while (!touristObjData.empty()) {
        newSettlement.addObject(TouristObjFactory::ChildObjFactory(touristObjData));
    }

    input.close();
}

void saveFile(std::string fileName, Settlement settlement) {
    std::ofstream output(fileName);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to create a file");
    }

    output << settlement.serialize();

    output.close();
}

} // namespace FileManager