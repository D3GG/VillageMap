#pragma once

#include "Settlement.h"
#include <fstream>

namespace FileManager {

void createFile(std::string fileName);

std::vector<std::string> removeDelimAndTokenize(const std::string& input);
void loadFile(std::string fileName);

void saveFile(std::string fileName);

}