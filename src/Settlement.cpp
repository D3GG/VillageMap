#include "Settlement.h"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

namespace {

std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(),
                   [](unsigned char ch) { return static_cast<char>(std::tolower(ch)); });

    return value;
}

bool containsCaseInsensitive(const std::string& text, const std::string& query) {
    return toLower(text).find(toLower(query)) != std::string::npos;
}

} // namespace

Settlement::Settlement(const std::string& name, const std::string& region, int population,
                       const std::string& description) {
    setName(name);
    setRegion(region);
    setPopulation(population);
    setDescription(description);
}

Settlement::~Settlement() {
    for (TouristObject* object : objects) {
        delete object;
    }
}

std::string Settlement::getName() const {
    return name;
}

std::string Settlement::getRegion() const {
    return region;
}

int Settlement::getPopulation() const {
    return population;
}

std::string Settlement::getDescription() const {
    return description;
}

void Settlement::setName(const std::string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }

    this->name = name;
}

void Settlement::setRegion(const std::string& region) {
    if (region.empty()) {
        throw std::invalid_argument("Region cannot be empty.");
    }

    this->region = region;
}

void Settlement::setPopulation(int population) {
    if (population < 0) {
        throw std::invalid_argument("Population cannot be negative.");
    }

    this->population = population;
}

void Settlement::setDescription(const std::string& description) {
    if (description.empty()) {
        throw std::invalid_argument("Description cannot be empty.");
    }

    this->description = description;
}

void Settlement::printInfo() const {
    std::cout << "Name: " << name << '\n';
    std::cout << "Region: " << region << '\n';
    std::cout << "Population: " << population << '\n';
    std::cout << "Description: " << description << '\n';
    std::cout << "Tourist objects: " << objects.size() << '\n';
}

void Settlement::addObject(TouristObject* object) {
    if (object == nullptr) {
        throw std::invalid_argument("Object cannot be null.");
    }

    if (findObjectById(object->getId()) != nullptr) {
        delete object;
        throw std::invalid_argument("Object with this ID already exists.");
    }

    objects.push_back(object);
}

bool Settlement::removeObjectById(int id) {
    for (std::size_t i = 0; i < objects.size(); i++) {
        if (objects.at(i)->getId() == id) {
            delete objects.at(i);
            objects.erase(objects.begin() + static_cast<long>(i));
            return true;
        }
    }

    return false;
}

TouristObject* Settlement::findObjectById(int id) const {
    for (TouristObject* object : objects) {
        if (object->getId() == id) {
            return object;
        }
    }

    return nullptr;
}

void Settlement::listObjects() const {
    if (objects.empty()) {
        std::cout << "No tourist objects available.\n";
        return;
    }

    for (TouristObject* object : objects) {
        object->printShortInfo();
    }
}

void Settlement::showObjectById(int id) const {
    TouristObject* object = findObjectById(id);

    if (object == nullptr) {
        std::cout << "Tourist object with ID " << id << " was not found.\n";
        return;
    }

    object->printFullInfo();
}

void Settlement::searchObjects(const std::string& text) const {
    bool found = false;

    for (TouristObject* object : objects) {
        if (containsCaseInsensitive(object->getName(), text) ||
            containsCaseInsensitive(object->getDescription(), text) ||
            containsCaseInsensitive(object->getCategory(), text)) {
            object->printShortInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No tourist objects found for search: " << text << '\n';
    }
}

void Settlement::filterObjectsByCategory(const std::string& category) const {
    bool found = false;
    std::string wantedCategory = toLower(category);

    for (TouristObject* object : objects) {
        if (toLower(object->getCategory()) == wantedCategory) {
            object->printShortInfo();
            found = true;
        }
    }

    if (!found) {
        std::cout << "No tourist objects found in category: " << category << '\n';
    }
}

std::size_t Settlement::getObjectCount() const {
    return objects.size();
}

double Settlement::getAverageRating() const {
    if (objects.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (TouristObject* object : objects) {
        total += object->getRating();
    }

    return total / static_cast<double>(objects.size());
}

double Settlement::getTourismPotentialScore() const {
    if (objects.empty()) {
        return 0.0;
    }

    double total = 0.0;

    for (TouristObject* object : objects) {
        total += object->calculateAttractiveness();
    }

    return total / static_cast<double>(objects.size());
}

std::string Settlement::serialize() const {
    std::ostringstream out;

    out << "Settlement" << '|' << name << '|' << region << '|' << population << '|' << description
        << '|';

    for (TouristObject* object : objects) {
        out << object->serialize() << '|';
    }

    return out.str();
}