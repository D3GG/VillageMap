#include "TouristObjFactory.h"

#include "CraftWorkshop.h"
#include "EcoPath.h"
#include "Festival.h"
#include "GuestHouse.h"
#include "Landmark.h"
#include "Restaurant.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace TouristObjFactory {

namespace {

std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    return value;
}

std::string readRequiredLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string value;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input closed.");
        }

        if (!value.empty()) {
            return value;
        }

        std::cout << "Value cannot be empty.\n";
    }
}

int readInt(const std::string& prompt) {
    while (true) {
        std::string value = readRequiredLine(prompt);

        try {
            std::size_t processed = 0;
            int number = std::stoi(value, &processed);

            if (processed != value.size()) {
                throw std::invalid_argument("Invalid integer.");
            }

            return number;
        } catch (...) {
            std::cout << "Please enter a valid integer.\n";
        }
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        std::string value = readRequiredLine(prompt);

        try {
            std::size_t processed = 0;
            double number = std::stod(value, &processed);

            if (processed != value.size()) {
                throw std::invalid_argument("Invalid number.");
            }

            return number;
        } catch (...) {
            std::cout << "Please enter a valid number.\n";
        }
    }
}

double readRating(const std::string& prompt) {
    while (true) {
        double rating = readDouble(prompt);

        if (rating >= 0.0 && rating <= 5.0) {
            return rating;
        }

        std::cout << "Rating must be between 0 and 5.\n";
    }
}

bool readBool(const std::string& prompt) {
    while (true) {
        std::string value = toLower(readRequiredLine(prompt));

        if (value == "y" || value == "yes" || value == "1" || value == "true") {
            return true;
        }

        if (value == "n" || value == "no" || value == "0" || value == "false") {
            return false;
        }

        std::cout << "Please enter y/n.\n";
    }
}

struct CommonFields {
    int id;
    std::string name;
    std::string description;
    double rating;
    double price;
};

CommonFields readCommonFields(int id) {
    CommonFields fields;

    fields.id = id;
    std::cout << "ID: " << fields.id << '\n';

    fields.name = readRequiredLine("Name: ");
    fields.description = readRequiredLine("Description: ");
    fields.rating = readRating("Rating (0-5): ");
    fields.price = readDouble("Price: ");

    return fields;
}

} // namespace

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
    if (touristObjData.empty()) {
        throw std::invalid_argument("No tourist object data available.");
    }

    TObjInfo info = strToTObjInfo(touristObjData.at(0));

    if (info.type == Unknown) {
        throw std::invalid_argument("Unsupported tourist object type: " + touristObjData.at(0));
    }

    if (touristObjData.size() < info.dataLength) {
        throw std::invalid_argument("Invalid amount of tourist object data.");
    }

    std::vector<std::string> singleObjData;
    std::vector<std::string> leftOverData;

    for (std::size_t i = 0; i < touristObjData.size(); i++) {
        if (i < info.dataLength) {
            singleObjData.push_back(touristObjData.at(i));
        } else {
            leftOverData.push_back(touristObjData.at(i));
        }
    }

    touristObjData = leftOverData;

    return singleObjData;
}

TouristObject* ChildObjFactory(std::vector<std::string>& touristObjData) {
    std::vector<std::string> singleObjData = getSingleTObj(touristObjData);

    switch (strToTObjInfo(singleObjData.at(0)).type) {
    case CW:
        return new CraftWorkshop(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                                 singleObjData.at(3), std::stod(singleObjData.at(4)),
                                 std::stod(singleObjData.at(5)), singleObjData.at(6),
                                 std::stoi(singleObjData.at(7)) != 0);

    case EP:
        return new EcoPath(std::stoi(singleObjData.at(1)), singleObjData.at(2), singleObjData.at(3),
                           std::stod(singleObjData.at(4)), std::stod(singleObjData.at(5)),
                           std::stod(singleObjData.at(6)), singleObjData.at(7),
                           std::stod(singleObjData.at(8)));

    case F:
        return new Festival(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                            singleObjData.at(3), std::stod(singleObjData.at(4)),
                            std::stod(singleObjData.at(5)), singleObjData.at(6),
                            singleObjData.at(7), std::stoi(singleObjData.at(8)) != 0);

    case GH:
        return new GuestHouse(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                              singleObjData.at(3), std::stod(singleObjData.at(4)),
                              std::stod(singleObjData.at(5)), std::stoi(singleObjData.at(6)),
                              std::stod(singleObjData.at(7)), std::stoi(singleObjData.at(8)) != 0);

    case L:
        return new Landmark(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                            singleObjData.at(3), std::stod(singleObjData.at(4)),
                            std::stod(singleObjData.at(5)), singleObjData.at(6),
                            std::stoi(singleObjData.at(7)) != 0);

    case R:
        return new Restaurant(std::stoi(singleObjData.at(1)), singleObjData.at(2),
                              singleObjData.at(3), std::stod(singleObjData.at(4)),
                              std::stod(singleObjData.at(5)), singleObjData.at(6),
                              std::stoi(singleObjData.at(7)) != 0);

    default:
        throw std::invalid_argument("Unsupported tourist object type.");
    }
}

TouristObject* createFromInput(const std::string& type, int id) {
    std::string normalizedType = toLower(type);

    CommonFields fields = readCommonFields(id);

    if (normalizedType == "landmark") {
        std::string historicalPeriod = readRequiredLine("Historical period: ");
        bool hasGuide = readBool("Has guide? (y/n): ");

        return new Landmark(fields.id, fields.name, fields.description, fields.rating, fields.price,
                            historicalPeriod, hasGuide);
    }

    if (normalizedType == "restaurant") {
        std::string cuisineType = readRequiredLine("Cuisine type: ");
        bool hasLocalFood = readBool("Has local food? (y/n): ");

        return new Restaurant(fields.id, fields.name, fields.description, fields.rating,
                              fields.price, cuisineType, hasLocalFood);
    }

    if (normalizedType == "guesthouse" || normalizedType == "guest_house") {
        int capacity = readInt("Capacity: ");
        double pricePerNight = readDouble("Price per night: ");
        bool hasParking = readBool("Has parking? (y/n): ");

        return new GuestHouse(fields.id, fields.name, fields.description, fields.rating,
                              fields.price, capacity, pricePerNight, hasParking);
    }

    if (normalizedType == "ecopath" || normalizedType == "eco_path") {
        double length = readDouble("Length in km: ");
        std::string difficulty = readRequiredLine("Difficulty: ");
        double duration = readDouble("Duration in hours: ");

        return new EcoPath(fields.id, fields.name, fields.description, fields.rating, fields.price,
                           length, difficulty, duration);
    }

    if (normalizedType == "festival") {
        std::string date = readRequiredLine("Date: ");
        std::string theme = readRequiredLine("Theme: ");
        bool isAnnual = readBool("Is annual? (y/n): ");

        return new Festival(fields.id, fields.name, fields.description, fields.rating, fields.price,
                            date, theme, isAnnual);
    }

    if (normalizedType == "craftworkshop" || normalizedType == "craft_workshop") {
        std::string craftType = readRequiredLine("Craft type: ");
        bool hasDemonstration = readBool("Has demonstration? (y/n): ");

        return new CraftWorkshop(fields.id, fields.name, fields.description, fields.rating,
                                 fields.price, craftType, hasDemonstration);
    }

    throw std::invalid_argument(
        "Unknown type. Use: landmark, restaurant, guesthouse, ecopath, festival, craftworkshop.");
}

} // namespace TouristObjFactory