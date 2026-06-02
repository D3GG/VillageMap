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
    : TouristObject(id, name, description, rating, price){
    setHistoricalPeriod(historicalPeriod);
    setHasGuide(hasGuide);
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

    cout << "Enter new name(current: " << getName() << "): ";
    std::getline(cin, newName);
    setName(newName);

    cout << "Enter new description(current: " << getDescription() << "): ";
    std::getline(cin, newDescription);
    setDescription(newDescription);

    while (true) {
        cout << "Enter new rating (0-5) (current: " << getRating() << "): ";

        if (!(cin >> newRating)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
        }
        else if (newRating < 0.0 || newRating > 5.0) {
            cin.ignore(1000, '\n');
            cout << "Rating must be between 0 and 5.\n";
        } 
        else {
            setRating(newRating);
            cin.ignore(1000, '\n');
            break;
        }
    }

    while (true) {
        cout << "Enter new price (current: " << getPrice() << "): ";
        
        if (!(cin >> newPrice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
        }
        else {
            setPrice(newPrice);
            cin.ignore(1000, '\n');
            break;
        }
    }

    cout << "Enter new historical period(current: " << getHistoricalPeriod() << "): ";
    std::getline(std::cin, newHistoricalPeriod);
    setHistoricalPeriod(newHistoricalPeriod);

    cout << "Is there a guide available? (y/n) (current: " << (getHasGuide() ? "Yes" : "No") << "): ";
    while (true) {
        cin >> guideChoice;
        if (guideChoice == 'y' || guideChoice == 'Y') {
            setHasGuide(true);
            break;
        }
        else if (guideChoice == 'n' || guideChoice == 'N') {
            setHasGuide(false);
            break;
        }
        else {
            cout << "Invalid input. Please enter 'y' or 'n': ";
        }
    }
    cin.ignore(1000, '\n');
}
