#include "application.h"

#include "CraftWorkshop.h"
#include "EcoPath.h"
#include "Festival.h"
#include "GuestHouse.h"
#include "Landmark.h"
#include "Restaurant.h"
#include "Settlement.h"
#include "TouristObject.h"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Application {

namespace {

const std::string FILE_MARKER = "VillageMapSettlementV1";

Interface::MenuStates currentState = Interface::Base;
std::unique_ptr<Settlement> currentSettlement = nullptr;
std::string currentFileName;

std::string trim(const std::string& value) {
    const std::string whitespace = " \t\n\r";

    std::size_t first = value.find_first_not_of(whitespace);
    if (first == std::string::npos) {
        return "";
    }

    std::size_t last = value.find_last_not_of(whitespace);
    return value.substr(first, last - first + 1);
}

std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    return value;
}

bool startsWith(const std::string& value, const std::string& prefix) {
    return value.rfind(prefix, 0) == 0;
}

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> result;
    std::stringstream stream(line);
    std::string token;

    while (std::getline(stream, token, delimiter)) {
        result.push_back(token);
    }

    return result;
}

int parseInt(const std::string& value, const std::string& fieldName) {
    std::stringstream stream(value);
    int number;
    char extra;

    if (!(stream >> number) || (stream >> extra)) {
        throw std::runtime_error("Invalid integer value for " + fieldName + ".");
    }

    return number;
}

double parseDouble(const std::string& value, const std::string& fieldName) {
    std::stringstream stream(value);
    double number;
    char extra;

    if (!(stream >> number) || (stream >> extra)) {
        throw std::runtime_error("Invalid number value for " + fieldName + ".");
    }

    return number;
}

bool parseBool(const std::string& value, const std::string& fieldName) {
    std::string lowerValue = toLower(trim(value));

    if (lowerValue == "1" || lowerValue == "true" || lowerValue == "yes" || lowerValue == "y") {
        return true;
    }

    if (lowerValue == "0" || lowerValue == "false" || lowerValue == "no" || lowerValue == "n") {
        return false;
    }

    throw std::runtime_error("Invalid boolean value for " + fieldName + ".");
}

std::string readLineRequired(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string value;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input closed.");
        }

        value = trim(value);

        if (!value.empty()) {
            return value;
        }

        std::cout << "Value cannot be empty.\n";
    }
}

int readInt(const std::string& prompt) {
    while (true) {
        try {
            return parseInt(readLineRequired(prompt), "input");
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }
}

double readDouble(const std::string& prompt) {
    while (true) {
        try {
            return parseDouble(readLineRequired(prompt), "input");
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }
}

bool readBool(const std::string& prompt) {
    while (true) {
        try {
            return parseBool(readLineRequired(prompt), "input");
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }
}

void ensureSettlementOpen() {
    if (!currentSettlement) {
        throw std::runtime_error("No settlement is currently opened.");
    }
}

void printPrompt() {
    if (currentState == Interface::Base) {
        std::cout << "\nVillageMap> ";
    } else {
        std::cout << "\nVillageMap[" << currentSettlement->getName() << "]> ";
    }
}

void applyExecutionResult(Interface::ExecutionResult result) {
    switch (result) {
    case Interface::Continue:
        break;

    case Interface::ExitProgram:
        break;

    case Interface::SwitchToBase:
        currentState = Interface::Base;
        break;

    case Interface::SwitchToInner:
        currentState = Interface::Inner;
        break;
    }
}

void printHelp(const Interface::ParsedCommand& command, Interface::MenuStates state) {
    if (command.args.empty()) {
        for (int i = 0; i < Interface::Unknown; i++) {
            if (Interface::commands[i].allowedStates == state ||
                Interface::commands[i].allowedStates == Interface::Both) {
                std::cout << Interface::commands[i].name << " - " << Interface::commands[i].usage
                          << " - " << Interface::commands[i].description << '\n';
            }
        }

        return;
    }

    Interface::CommandType type = Interface::stringToCmdType(command.args.front());

    if (type == Interface::Unknown) {
        throw std::runtime_error("Unknown command for help.");
    }

    std::cout << Interface::commands[type].name << " - " << Interface::commands[type].usage << " - "
              << Interface::commands[type].description << '\n';
}

struct CommonObjectFields {
    int id;
    std::string name;
    std::string description;
    double rating;
    double price;
};

CommonObjectFields readCommonObjectFields() {
    CommonObjectFields fields;

    fields.id = readInt("ID: ");

    if (currentSettlement && currentSettlement->findObjectById(fields.id) != nullptr) {
        throw std::runtime_error("Object with this ID already exists.");
    }

    fields.name = readLineRequired("Name: ");
    fields.description = readLineRequired("Description: ");
    fields.rating = readDouble("Rating (0-5): ");
    fields.price = readDouble("Price: ");

    return fields;
}

TouristObject* createObjectFromInput(const std::string& typeInput) {
    std::string type = toLower(typeInput);
    CommonObjectFields fields = readCommonObjectFields();

    if (type == "landmark") {
        std::string historicalPeriod = readLineRequired("Historical period: ");
        bool hasGuide = readBool("Has guide? (y/n): ");

        return new Landmark(fields.id, fields.name, fields.description, fields.rating, fields.price,
                            historicalPeriod, hasGuide);
    }

    if (type == "restaurant") {
        std::string cuisineType = readLineRequired("Cuisine type: ");
        bool hasLocalFood = readBool("Has local food? (y/n): ");

        return new Restaurant(fields.id, fields.name, fields.description, fields.rating,
                              fields.price, cuisineType, hasLocalFood);
    }

    if (type == "guesthouse" || type == "guest_house") {
        int capacity = readInt("Capacity: ");
        double pricePerNight = readDouble("Price per night: ");
        bool hasParking = readBool("Has parking? (y/n): ");

        return new GuestHouse(fields.id, fields.name, fields.description, fields.rating,
                              fields.price, capacity, pricePerNight, hasParking);
    }

    if (type == "ecopath" || type == "eco_path") {
        double length = readDouble("Length in km: ");
        std::string difficulty = readLineRequired("Difficulty: ");
        double duration = readDouble("Duration in hours: ");

        return new EcoPath(fields.id, fields.name, fields.description, fields.rating, fields.price,
                           length, difficulty, duration);
    }

    if (type == "festival") {
        std::string date = readLineRequired("Date: ");
        std::string theme = readLineRequired("Theme: ");
        bool isAnnual = readBool("Is annual? (y/n): ");

        return new Festival(fields.id, fields.name, fields.description, fields.rating, fields.price,
                            date, theme, isAnnual);
    }

    if (type == "craftworkshop" || type == "craft_workshop") {
        std::string craftType = readLineRequired("Craft type: ");
        bool hasDemonstration = readBool("Has demonstration? (y/n): ");

        return new CraftWorkshop(fields.id, fields.name, fields.description, fields.rating,
                                 fields.price, craftType, hasDemonstration);
    }

    throw std::runtime_error("Unknown object type. Available types: landmark, restaurant, "
                             "guesthouse, ecopath, festival, craftworkshop.");
}

TouristObject* createObjectFromSerializedLine(const std::string& line) {
    std::vector<std::string> parts = split(line, '|');

    if (parts.size() < 6) {
        throw std::runtime_error("Invalid object data line: " + line);
    }

    std::string type = parts[0];
    int id = parseInt(parts[1], "id");
    std::string name = parts[2];
    std::string description = parts[3];
    double rating = parseDouble(parts[4], "rating");
    double price = parseDouble(parts[5], "price");

    if (type == "Landmark") {
        if (parts.size() != 8) {
            throw std::runtime_error("Invalid Landmark data.");
        }

        return new Landmark(id, name, description, rating, price, parts[6],
                            parseBool(parts[7], "hasGuide"));
    }

    if (type == "Restaurant") {
        if (parts.size() != 8) {
            throw std::runtime_error("Invalid Restaurant data.");
        }

        return new Restaurant(id, name, description, rating, price, parts[6],
                              parseBool(parts[7], "hasLocalFood"));
    }

    if (type == "GuestHouse") {
        if (parts.size() != 9) {
            throw std::runtime_error("Invalid GuestHouse data.");
        }

        return new GuestHouse(id, name, description, rating, price, parseInt(parts[6], "capacity"),
                              parseDouble(parts[7], "pricePerNight"),
                              parseBool(parts[8], "hasParking"));
    }

    if (type == "EcoPath") {
        if (parts.size() != 9) {
            throw std::runtime_error("Invalid EcoPath data.");
        }

        return new EcoPath(id, name, description, rating, price, parseDouble(parts[6], "length"),
                           parts[7], parseDouble(parts[8], "duration"));
    }

    if (type == "Festival") {
        if (parts.size() != 9) {
            throw std::runtime_error("Invalid Festival data.");
        }

        return new Festival(id, name, description, rating, price, parts[6], parts[7],
                            parseBool(parts[8], "isAnnual"));
    }

    if (type == "CraftWorkshop") {
        if (parts.size() != 8) {
            throw std::runtime_error("Invalid CraftWorkshop data.");
        }

        return new CraftWorkshop(id, name, description, rating, price, parts[6],
                                 parseBool(parts[7], "hasDemonstration"));
    }

    throw std::runtime_error("Unknown object type in file: " + type);
}

void saveCurrentSettlement() {
    ensureSettlementOpen();

    std::ofstream file(currentFileName);

    if (!file) {
        throw std::runtime_error("Could not open file for writing: " + currentFileName);
    }

    file << FILE_MARKER << '\n';
    file << currentSettlement->getName() << '\n';
    file << currentSettlement->getRegion() << '\n';
    file << currentSettlement->getPopulation() << '\n';
    file << currentSettlement->getDescription() << '\n';
    file << "OBJECTS" << '\n';

    for (const TouristObject* object : currentSettlement->getObjects()) {
        file << object->serialize() << '\n';
    }
}

void createSettlementFile(const std::string& fileName) {
    std::string name = readLineRequired("Settlement name: ");
    std::string region = readLineRequired("Region: ");
    int population = readInt("Population: ");
    std::string description = readLineRequired("Description: ");

    currentSettlement = std::make_unique<Settlement>(name, region, population, description);
    currentFileName = fileName;

    saveCurrentSettlement();

    std::cout << "Created and opened settlement: " << name << '\n';
}

void loadSettlementFile(const std::string& fileName) {
    std::ifstream file(fileName);

    if (!file) {
        throw std::runtime_error("Could not open file: " + fileName);
    }

    std::string marker;
    std::string name;
    std::string region;
    std::string populationText;
    std::string description;

    if (!std::getline(file, marker) || !std::getline(file, name) || !std::getline(file, region) ||
        !std::getline(file, populationText) || !std::getline(file, description)) {
        throw std::runtime_error("Invalid settlement file.");
    }

    if (marker != FILE_MARKER) {
        throw std::runtime_error("Invalid file format.");
    }

    std::unique_ptr<Settlement> loadedSettlement = std::make_unique<Settlement>(
        name, region, parseInt(populationText, "population"), description);

    std::string line;
    while (std::getline(file, line)) {
        line = trim(line);

        if (line.empty() || line == "OBJECTS") {
            continue;
        }

        std::unique_ptr<TouristObject> object(createObjectFromSerializedLine(line));

        if (loadedSettlement->findObjectById(object->getId()) != nullptr) {
            throw std::runtime_error("Duplicate object ID in file.");
        }

        loadedSettlement->addObject(object.release());
    }

    currentSettlement = std::move(loadedSettlement);
    currentFileName = fileName;

    std::cout << "Loaded settlement: " << currentSettlement->getName() << '\n';
}

bool objectMatchesSearch(const TouristObject* object, const std::string& query) {
    std::string lowerQuery = toLower(query);

    return toLower(object->getName()).find(lowerQuery) != std::string::npos ||
           toLower(object->getDescription()).find(lowerQuery) != std::string::npos ||
           toLower(object->getCategory()).find(lowerQuery) != std::string::npos;
}

bool compareNumber(double value, const std::string& expression) {
    std::string text = trim(expression);

    if (startsWith(text, ">=")) {
        return value >= parseDouble(text.substr(2), "filter value");
    }

    if (startsWith(text, "<=")) {
        return value <= parseDouble(text.substr(2), "filter value");
    }

    if (startsWith(text, ">")) {
        return value > parseDouble(text.substr(1), "filter value");
    }

    if (startsWith(text, "<")) {
        return value < parseDouble(text.substr(1), "filter value");
    }

    if (startsWith(text, "=")) {
        return value == parseDouble(text.substr(1), "filter value");
    }

    throw std::runtime_error("Invalid filter comparison.");
}

bool objectMatchesFilter(const TouristObject* object, const std::string& criteriaInput) {
    std::string criteria = toLower(trim(criteriaInput));
    std::string category = toLower(object->getCategory());

    if (criteria == category) {
        return true;
    }

    if (criteria == "guesthouse" && category == "guesthouse") {
        return true;
    }

    if (criteria == "ecopath" && category == "ecopath") {
        return true;
    }

    if (criteria == "craftworkshop" && category == "craftworkshop") {
        return true;
    }

    if (criteria == "free") {
        return object->getPrice() == 0.0;
    }

    if (criteria == "paid") {
        return object->getPrice() > 0.0;
    }

    if (criteria == "top") {
        return object->calculateAttractiveness() >= 4.5;
    }

    if (startsWith(criteria, "rating")) {
        return compareNumber(object->getRating(), criteria.substr(6));
    }

    if (startsWith(criteria, "price")) {
        return compareNumber(object->getPrice(), criteria.substr(5));
    }

    if (startsWith(criteria, "attractiveness")) {
        return compareNumber(object->calculateAttractiveness(), criteria.substr(14));
    }

    throw std::runtime_error("Unknown filter. Examples: landmark, restaurant, free, paid, top, "
                             "rating>=4, price<20, attractiveness>=4.5");
}

void searchObjects(const std::string& query) {
    ensureSettlementOpen();

    bool found = false;

    for (const TouristObject* object : currentSettlement->getObjects()) {
        if (objectMatchesSearch(object, query)) {
            object->printShortInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No objects found for search: " << query << '\n';
    }
}

void filterObjects(const std::string& criteria) {
    ensureSettlementOpen();

    bool found = false;

    for (const TouristObject* object : currentSettlement->getObjects()) {
        if (objectMatchesFilter(object, criteria)) {
            object->printShortInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No objects matched filter: " << criteria << '\n';
    }
}

void printReport() {
    ensureSettlementOpen();

    const std::vector<TouristObject*>& objects = currentSettlement->getObjects();

    std::cout << "Settlement report\n";
    std::cout << "Name: " << currentSettlement->getName() << '\n';
    std::cout << "Region: " << currentSettlement->getRegion() << '\n';
    std::cout << "Population: " << currentSettlement->getPopulation() << '\n';
    std::cout << "Description: " << currentSettlement->getDescription() << '\n';
    std::cout << "Object count: " << objects.size() << '\n';

    if (objects.empty()) {
        return;
    }

    std::map<std::string, int> categoryCounts;
    double totalRating = 0.0;
    double totalPrice = 0.0;
    double totalAttractiveness = 0.0;
    const TouristObject* bestObject = objects.front();

    for (const TouristObject* object : objects) {
        categoryCounts[object->getCategory()]++;
        totalRating += object->getRating();
        totalPrice += object->getPrice();
        totalAttractiveness += object->calculateAttractiveness();

        if (object->calculateAttractiveness() > bestObject->calculateAttractiveness()) {
            bestObject = object;
        }
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Average rating: " << totalRating / objects.size() << '\n';
    std::cout << "Average price: " << totalPrice / objects.size() << '\n';
    std::cout << "Average attractiveness: " << totalAttractiveness / objects.size() << '\n';

    std::cout << "Objects by category:\n";
    for (const auto& pair : categoryCounts) {
        std::cout << "- " << pair.first << ": " << pair.second << '\n';
    }

    std::cout << "Most attractive object:\n";
    bestObject->printShortInfo();
}

} // namespace

int run() {
    std::cout << "VillageMap CLI started.\n";
    std::cout << "Type 'help' to see available commands.\n";

    bool isRunning = true;

    while (isRunning) {
        printPrompt();

        std::string inputLine;
        if (!std::getline(std::cin, inputLine)) {
            break;
        }

        try {
            std::vector<std::string> tokens = Interface::tokenize(inputLine);

            if (tokens.empty()) {
                continue;
            }

            Interface::ParsedCommand command = Interface::parseTokens(tokens, currentState);
            Interface::ExecutionResult result = executeCommand(command, currentState);

            if (result == Interface::ExitProgram) {
                isRunning = false;
            }

            applyExecutionResult(result);
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}

Interface::ExecutionResult executeCommand(Interface::ParsedCommand command,
                                          Interface::MenuStates state) {
    switch (command.type) {
    case Interface::Create:
        createSettlementFile(command.args.at(0));
        return Interface::SwitchToInner;

    case Interface::Load:
        loadSettlementFile(command.args.at(0));
        return Interface::SwitchToInner;

    case Interface::Help:
        printHelp(command, state);
        return Interface::Continue;

    case Interface::Exit:
        return Interface::ExitProgram;

    case Interface::Info:
        ensureSettlementOpen();
        std::cout << "Name: " << currentSettlement->getName() << '\n';
        std::cout << "Region: " << currentSettlement->getRegion() << '\n';
        std::cout << "Population: " << currentSettlement->getPopulation() << '\n';
        std::cout << "Description: " << currentSettlement->getDescription() << '\n';
        return Interface::Continue;

    case Interface::Add: {
        ensureSettlementOpen();

        std::unique_ptr<TouristObject> object(createObjectFromInput(command.args.at(0)));
        currentSettlement->addObject(object.release());

        std::cout << "Object added.\n";
        return Interface::Continue;
    }

    case Interface::List:
        ensureSettlementOpen();
        currentSettlement->listObjects();
        return Interface::Continue;

    case Interface::Show:
        ensureSettlementOpen();
        currentSettlement->showObjectById(parseInt(command.args.at(0), "id"));
        return Interface::Continue;

    case Interface::Delete: {
        ensureSettlementOpen();

        int id = parseInt(command.args.at(0), "id");

        if (currentSettlement->removeObjectById(id)) {
            std::cout << "Object deleted.\n";
        } else {
            std::cout << "Object with ID " << id << " was not found.\n";
        }

        return Interface::Continue;
    }

    case Interface::Update: {
        ensureSettlementOpen();

        int id = parseInt(command.args.at(0), "id");
        TouristObject* object = currentSettlement->findObjectById(id);

        if (object == nullptr) {
            std::cout << "Object with ID " << id << " was not found.\n";
            return Interface::Continue;
        }

        object->updateFromInput();
        std::cout << "Object updated.\n";

        return Interface::Continue;
    }

    case Interface::Search:
        searchObjects(command.args.at(0));
        return Interface::Continue;

    case Interface::Filter:
        filterObjects(command.args.at(0));
        return Interface::Continue;

    case Interface::Report:
        printReport();
        return Interface::Continue;

    case Interface::Save:
        saveCurrentSettlement();
        std::cout << "Saved to " << currentFileName << ".\n";
        return Interface::Continue;

    case Interface::Close:
        ensureSettlementOpen();
        currentSettlement.reset();
        currentFileName.clear();
        std::cout << "Settlement closed.\n";
        return Interface::SwitchToBase;

    default:
        throw std::runtime_error("Executor received unknown command.");
    }
}

} // namespace Application