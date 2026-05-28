#include "Landmark.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

Landmark::Landmark(int id, const std::string& name, const std::string& description, double rating,
                   double price, const std::string& historicalPeriod, bool hasGuide)
    : TouristObject(id, name, description, rating, price), historicalPeriod(historicalPeriod),
      hasGuide(hasGuide) {
    if (historicalPeriod.empty()) {
        throw std::invalid_argument("Historical period cannot be empty.");
    }
}

std::string Landmark::getHistoricalPeriod() const {
    return historicalPeriod;
}

bool Landmark::getHasGuide() const {
    return hasGuide;
}

void Landmark::setHistoricalPeriod(const std::string& historicalPeriod) {
    if (historicalPeriod.empty()) {
        throw std::invalid_argument("Historical period cannot be empty.");
    }

    this->historicalPeriod = historicalPeriod;
}

void Landmark::setHasGuide(bool hasGuide) {
    this->hasGuide = hasGuide;
}

std::string Landmark::getCategory() const {
    return "Landmark";
}

void Landmark::printShortInfo() const {
    cout << "[" << getId() << "] " << getName() << " | Category: " << getCategory()
         << " | Rating: " << getRating() << " | Price: " << getPrice() << endl;
}

void Landmark::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Historical period: " << historicalPeriod << '\n';
    cout << "Guide available: " << (hasGuide ? "Yes" : "No") << endl;
}

double Landmark::calculateAttractiveness() const {
    double score = getRating();

    if (hasGuide) {
        score += 0.5;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

string Landmark::serialize() const {
    std::ostringstream out;

    out << getCategory() << "|" << getId() << "|" << getName() << "|" << getDescription() << "|"
        << getRating() << "|" << getPrice() << "|" << historicalPeriod << "|" << hasGuide;

    return out.str();
}

void Landmark::updateFromInput() {
    string newName;
    string newDescription;
    string newHistoricalPeriod;
    double newRating;
    double newPrice;
    char guideChoice;

    cout << "Enter new name: ";
    getline(cin, newName);

    cout << "Enter new description: ";
    getline(cin, newDescription);

    cout << "Enter new rating (0-5): ";
    cin >> newRating;

    cout << "Enter new price: ";
    cin >> newPrice;

    cin.ignore();

    cout << "Enter new historical period: ";
    std::getline(std::cin, newHistoricalPeriod);

    cout << "Has guide? (y/n): ";
    cin >> guideChoice;

    cin.ignore();

    setName(newName);
    setDescription(newDescription);
    setRating(newRating);
    setPrice(newPrice);
    setHistoricalPeriod(newHistoricalPeriod);

    if (guideChoice == 'y' || guideChoice == 'Y') {
        setHasGuide(true);
    } else if (guideChoice == 'n' || guideChoice == 'N') {
        setHasGuide(false);
    } else {
        throw std::invalid_argument("Guide choice must be y or n.");
    }
}
