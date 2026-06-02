#include "FileManager.h"

#include "TouristObjFactory.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace FileManager {

void createFile(const std::string& fileName) {
    std::ofstream output(fileName);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to create file: " + fileName);
    }
}

std::vector<std::string> removeDelimAndTokenize(const std::string& input,
                                                std::vector<std::string>& settlementData) {
    std::vector<std::string> touristObjData;
    std::istringstream stream(input);
    std::string currToken;
    std::size_t index = 0;

    while (std::getline(stream, currToken, '|')) {
        if (index == 0) {
            if (currToken != "Settlement") {
                throw std::runtime_error("Invalid file format. Expected Settlement marker.");
            }

            index++;
            continue;
        }

        if (index <= 4) {
            settlementData.push_back(currToken);
            index++;
            continue;
        }

        touristObjData.push_back(currToken);
        index++;
    }

    return touristObjData;
}

std::unique_ptr<Settlement> loadFile(const std::string& fileName) {
    std::ifstream input(fileName);

    if (!input.is_open()) {
        throw std::runtime_error("Failed to open file for reading: " + fileName);
    }

    std::string line;
    std::getline(input, line);

    if (line.empty()) {
        throw std::runtime_error("File is empty.");
    }

    std::vector<std::string> settlementData;
    std::vector<std::string> touristObjData = removeDelimAndTokenize(line, settlementData);

    if (settlementData.size() != 4) {
        throw std::runtime_error("Invalid settlement data.");
    }

    auto newSettlement =
        std::make_unique<Settlement>(settlementData.at(0), settlementData.at(1),
                                     std::stoi(settlementData.at(2)), settlementData.at(3));

    while (!touristObjData.empty()) {
        TouristObject* object = TouristObjFactory::ChildObjFactory(touristObjData);
        newSettlement->addObject(object);
    }

    return newSettlement;
}

void saveFile(const std::string& fileName, const Settlement& settlement) {
    std::ofstream output(fileName);

    if (!output.is_open()) {
        throw std::runtime_error("Failed to open file for writing: " + fileName);
    }

    output << settlement.serialize();
}

} // namespace FileManager