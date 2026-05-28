#include "TouristObject.h"
#include <stdexcept>

#include <string>
using std::string;

TouristObject::TouristObject(int id, const string& name, const string& description, double rating,
                             double price) {
    if (id <= 0) {
        throw std::invalid_argument("Id must be positive.");
    }

    this->id = id;

    setName(name);
    setDescription(description);
    setRating(rating);
    setPrice(price);
}

int TouristObject::getId() const {
    return id;
}

string TouristObject::getName() const {
    return name;
}

string TouristObject::getDescription() const {
    return description;
}

double TouristObject::getRating() const {
    return rating;
}

double TouristObject::getPrice() const {
    return price;
}

void TouristObject::setName(const string& name) {
    if (name.empty()) {
        throw std::invalid_argument("Name cannot be empty.");
    }

    this->name = name;
}

void TouristObject::setDescription(const string& description) {
    if (description.empty()) {
        throw std::invalid_argument("Description cannot be empty.");
    }

    this->description = description;
}

void TouristObject::setRating(double rating) {
    if (rating < 0.0 || rating > 5.0) {
        throw std::invalid_argument("Rating must be between 0 and 5.");
    }

    this->rating = rating;
}

void TouristObject::setPrice(double price) {
    if (price < 0.0) {
        throw std::invalid_argument("Price cannot be negative.");
    }

    this->price = price;
}