#pragma once

#include "Settlement.h"

#include <memory>
#include <string>
#include <vector>

namespace FileManager {

void createFile(const std::string& fileName);

std::vector<std::string> removeDelimAndTokenize(const std::string& input,
                                                std::vector<std::string>& settlementData);

std::unique_ptr<Settlement> loadFile(const std::string& fileName);

void saveFile(const std::string& fileName, const Settlement& settlement);

} // namespace FileManager