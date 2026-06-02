#include "TouristObjFactory.h"
#include "CraftWorkshop.h"
#include "EcoPath.h"
#include "Festival.h"
#include "GuestHouse.h"
#include "Landmark.h"
#include "Restaurant.h"

#include <stdexcept>

namespace TouristObjFactory {

TObjInfo strToTObjInfo(const std::string& str) {
    if (str == "CraftWorkshop") {
        return {CW, 8};
    }
    if (str == "EcoPath") {
        return {EP, 9};
    }
    if (str == "Festival") {
        return {F, 9};
    }
    if (str == "GuestHouse") {
        return {GH, 9};
    }
    if (str == "Landmark") {
        return {L, 8};
    }
    if (str == "Restaurant") {
        return {R, 8};
    }

    return {Unknown, 0};
}

std::vector<std::string> getSingleTObj(std::vector<std::string>& touristObjData) {
    std::vector<std::string> singleObjData;
    std::vector<std::string> leftOverData;
    TObjInfo info = strToTObjInfo(touristObjData.at(0));

    if (touristObjData.size() < info.dataLength)
        throw std::invalid_argument("something something");

    for (std::size_t i = 0; i < touristObjData.size(); i++) {
        if (i < info.dataLength) {
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
    switch (strToTObjInfo(singleObjData.at(0)).type) {
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
                "Invalid amount of data for Landmark Child. Expected size: 8, Actual Size: " +
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