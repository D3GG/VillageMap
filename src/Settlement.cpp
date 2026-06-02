#include "Settlement.h"
#include <iostream>
#include <stdexcept>
#include <sstream>

#include <string>
using std::cout;
using std::string;


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

void Settlement::setName(const string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }

    this->name = name;
}

void Settlement::setRegion(const string& region) {
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

void Settlement::setDescription(const string& description) {
    if (description.empty()) {
        throw std::invalid_argument("Description cannot be empty.");
    }

    this->description = description;
}

void Settlement::addObject(TouristObject* object) {
    if (object == nullptr) {
        throw std::invalid_argument("Object cannot be null.");
    }

    objects.push_back(object);
}

bool Settlement::removeObjectById(int id) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects[i]->getId() == id) {
            delete objects[i];
            objects.erase(objects.begin() + i);
            return true;
        }
    }

    return false;
}

const std::vector<TouristObject*>& Settlement::getObjects() const {
    return objects;
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
        cout << "No tourist objects available.\n";
        return;
    }

    for (TouristObject* object : objects) {
        object->printShortInfo();
    }
}

void Settlement::showObjectById(int id) const {
    TouristObject* object = findObjectById(id);

    if (object == nullptr) {
        cout << "Tourist object with ID " << id << " was not found.\n";
        return;
    }

    object->printFullInfo();
}

std::string Settlement::serialize() const {
    std::ostringstream out;

    out << "Settlement" << '|'
        << name << '|'
        << region << '|'
        << population << '|'
        << description << '|';

    for(std::size_t i = 0; i < objects.size(); i++){
        out << objects.at(i)->serialize();
    }    

    return out.str();
}