#include "EcoPath.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

EcoPath::EcoPath(int id, const std::string& name, const std::string& description, double rating,
                 double price, double length, const std::string& difficulty, double duration)
    : TouristObject(id, name, description, rating, price) {
    setLength(length);
    setDifficulty(difficulty);
    setDuration(duration);
}

double EcoPath::getLength() const {
    return length;
}

std::string EcoPath::getDifficulty() const {
    return difficulty;
}

double EcoPath::getDuration() const {
    return duration;
}

void EcoPath::setLength(double length) {
    if (length <= 0.0) {
        throw std::invalid_argument("Length must be positive.");
    }

    this->length = length;
}

void EcoPath::setDifficulty(const string& difficulty) {
    if (difficulty.empty()) {
        throw std::invalid_argument("Difficulty cannot be empty.");
    }

    this->difficulty = difficulty;
}

void EcoPath::setDuration(double duration) {
    if (duration <= 0.0) {
        throw std::invalid_argument("Duration must be positive.");
    }

    this->duration = duration;
}

string EcoPath::getCategory() const {
    return "EcoPath";
}

void EcoPath::printShortInfo() const {
    cout << "[" << getId() << "] " << getName()
         << " | Category: " << getCategory()
         << " | Rating: " << getRating()
         << " | Length: " << length << " km"
         << " | Difficulty: " << difficulty
         << '\n';
}

void EcoPath::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Length: " << length << " km" << '\n';
    cout << "Difficulty: " << difficulty << '\n';
    cout << "Duration: " << duration << " hours" << '\n';
}

double EcoPath::calculateAttractiveness() const {
    double score = getRating();

    if (difficulty == "Easy" || difficulty == "easy") {
        score += 0.3;
    } else if (difficulty == "Medium" || difficulty == "medium") {
        score += 0.2;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

string EcoPath::serialize() const {
    std::ostringstream out;

    out << getCategory() << "|"
        << getId() << "|"
        << getName() << "|"
        << getDescription() << "|"
        << getRating() << "|"
        << getPrice() << "|"
        << length << "|"
        << difficulty << "|"
        << duration;

    return out.str();
}

void EcoPath::updateFromInput() {
    string newName;
    string newDescription;
    double newRating;
    double newPrice;
    double newLength;
    string newDifficulty;
    double newDuration;

    cout << "Enter new name: ";
    getline(cin, newName);

    cout << "Enter new description: ";
    getline(cin, newDescription);

    cout << "Enter new rating (0-5): ";
    cin >> newRating;

    cout << "Enter new price: ";
    cin >> newPrice;

    cout << "Enter new length in km: ";
    cin >> newLength;

    cin.ignore();

    cout << "Enter new difficulty: ";
    getline(cin, newDifficulty);

    cout << "Enter new duration in hours: ";
    cin >> newDuration;

    cin.ignore();

    setName(newName);
    setDescription(newDescription);
    setRating(newRating);
    setPrice(newPrice);
    setLength(newLength);
    setDifficulty(newDifficulty);
    setDuration(newDuration);
}