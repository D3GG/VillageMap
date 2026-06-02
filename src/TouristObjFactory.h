#pragma once

#include "Settlement.h"
#include "TouristObject.h"

namespace TouristObjFactory {

enum TObject { CW, EP, F, GH, L, R, Unknown };

TObject strToTObj(const std::string& str);

std::vector<std::string> getSingleTObj(std::vector<std::string>& touristObjData);

TouristObject* ChildObjFactory(std::vector<std::string> touristObjData);

} // namespace TouristObjFactory