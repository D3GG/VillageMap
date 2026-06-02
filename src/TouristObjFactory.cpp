#include "TouristObjFactory.h"
#include "CraftWorkshop.h"
#include "EcoPath.h"
#include "Festival.h"
#include "GuestHouse.h"
#include "Landmark.h"
#include "Restaurant.h"

#include <stdexcept>

namespace TouristObjFactory {

TObject strToTObj(const std::string& str) {
    if (str == "CraftWorkshop") {
        return CW;
    }
    if (str == "EcoPath") {
        return EP;
    }
    if (str == "Festival") {
        return F;
    }
    if (str == "GuestHouse") {
        return GH;
    }
    if (str == "Landmark") {
        return L;
    }
    if (str == "Restaurant") {
        return R;
    }

    return Unknown;
}

std::vector<std::string> getSingleTObj(std::vector<std::string>& touristObjData) {
    std::vector<std::string> singleObjData;
    std::vector<std::string> leftOverData;
    bool finishedExtractingData = false;

    for (std::size_t i = 0; i < touristObjData.size(); i++) {
        if (i == 0 && strToTObj(touristObjData.at(i)) != Unknown) {
            singleObjData.push_back(touristObjData.at(i));
            continue;
        }
        if (strToTObj(touristObjData.at(i)) != Unknown && finishedExtractingData == false) {
            finishedExtractingData = true;
            leftOverData.push_back(touristObjData.at(i));
            continue;
        }
        if (finishedExtractingData == false) {
            singleObjData.push_back(touristObjData.at(i));
            continue;
        }

        leftOverData.push_back(touristObjData.at(i));
    }

    touristObjData = leftOverData;
    return singleObjData;
}

TouristObject* ChildObjFactory(std::vector<std::string>& touristObjData) {

    std::vector<std::string> singleObjData = getSingleTObj(touristObjData);
    switch (strToTObj(singleObjData.at(0))) {
    case CW:
        if (singleObjData.size() != 8)
            throw std::invalid_argument(
                "Invalid amount of data for CraftWorkshop Child. Expected size: 8, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new CraftWorkshop(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                                 singleObjData.at(3), std::stod(singleObjData.at(4)),
                                 std::stod(singleObjData.at(5)), singleObjData.at(6),
                                 std::stoi(singleObjData.at(7)) != 0);
        break;
    case EP:
        if (singleObjData.size() != 9)
            throw std::invalid_argument(
                "Invalid amount of data for EcoPath Child. Expected size: 9, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new EcoPath(std::stoi(singleObjData.at(1)), singleObjData.at(2), singleObjData.at(3),
                           std::stod(singleObjData.at(4)), std::stod(singleObjData.at(5)),
                           std::stod(singleObjData.at(6)), singleObjData.at(7),
                           std::stod(singleObjData.at(8)));
        break;
    case F:
        if (singleObjData.size() != 9)
            throw std::invalid_argument(
                "Invalid amount of data for Festival Child. Expected size: 9, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new Festival(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                            singleObjData.at(3), std::stod(singleObjData.at(4)),
                            std::stod(singleObjData.at(5)), singleObjData.at(6),
                            singleObjData.at(7), std::stoi(singleObjData.at(8)) != 0);
        break;
    case GH:
        if (singleObjData.size() != 9)
            throw std::invalid_argument(
                "Invalid amount of data for GuestHouse Child. Expected size: 9, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new GuestHouse(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                              singleObjData.at(3), std::stod(singleObjData.at(4)),
                              std::stod(singleObjData.at(5)), std::stoi(singleObjData.at(6)),
                              std::stod(singleObjData.at(7)), std::stoi(singleObjData.at(8)) != 0);
        break;
    case L:
        if (singleObjData.size() != 8)
            throw std::invalid_argument(
                "Invalid amount of data for NA Child. Expected size: 8, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new Landmark(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                            singleObjData.at(3), std::stod(singleObjData.at(4)),
                            std::stod(singleObjData.at(5)), singleObjData.at(6),
                            std::stoi(singleObjData.at(7)) != 0);
        break;
    case R:
        if (singleObjData.size() != 8)
            throw std::invalid_argument(
                "Invalid amount of data for Restaurant Child. Expected size: 8, Actual Size: " +
                std::to_string(singleObjData.size()));
        return new Restaurant(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                              singleObjData.at(3), std::stod(singleObjData.at(4)),
                              std::stod(singleObjData.at(5)), singleObjData.at(6),
                              std::stoi(singleObjData.at(7)) != 0);
        break;

    default:
        throw std::invalid_argument("Unsupported tourist object type");
        break;
    }
}

} // namespace TouristObjFactory