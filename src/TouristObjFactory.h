#pragma once

#include "Settlement.h"
#include "TouristObject.h"

namespace TouristObjFactory {

enum TObject { CW, EP, F, GH, L, R, Unknown };

struct TObjInfo {
    TObject type;
    std::size_t dataLength;
};

TObjInfo strToTObjInfo(const std::string& str);

std::vector<std::string> getSingleTObj(std::vector<std::string>& touristObjData);

TouristObject* createFromInput(const std::string& type, int id);

TouristObject* ChildObjFactory(std::vector<std::string>& touristObjData);

} // namespace TouristObjFactory