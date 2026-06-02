#include "FileManager.h"
#include <sstream>

namespace FileManager {

void createFile(std::string fileName) {
    std::ofstream output(fileName);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to create a file");
    }

    output.close();
}

std::vector<std::string> removeDelimAndTokenize(const std::string& input) {
    std::vector<std::string> output;
    std::istringstream stream(input);
    std::string currToken;

    while (std::getline(stream, currToken, '|')) {
        output.push_back(currToken);
    }

    return output;
}

void loadFile(std::string fileName) {
    std::ifstream input(fileName);
    if (!input.is_open()) {
        throw std::runtime_error("Failed to open a file for reading");
    }

    // extarct all of the info needed to make a valid settlement
    // then pass the rest to a factory to generate valid tourst obj children to fill the vector in
    // settlement

    input.close();
}

void saveFile(std::string fileName) {
    std::ofstream output(fileName);
    if (!output.is_open()) {
        throw std::runtime_error("Failed to create a file");
    }
    
    output.close();
}

} // namespace FileManager