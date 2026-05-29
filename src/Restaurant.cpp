#include "Restaurant.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

Restaurant::Restaurant(int id, const string& name, const string& description, double rating,
                       double price, const string& cuisineType, bool hasLocalFood)
    : TouristObject(id, name, description, rating, price), hasLocalFood(hasLocalFood) {
    setCuisineType(cuisineType);
}

std::string Restaurant::getCuisineType() const {
    return cuisineType;
}

bool Restaurant::getHasLocalFood() const {
    return hasLocalFood;
}

void Restaurant::setCuisineType(const std::string& cuisineType) {
    if (cuisineType.empty()) {
        throw std::invalid_argument("Cuisine type cannot be empty.");
    }

    this->cuisineType = cuisineType;
}

void Restaurant::setHasLocalFood(bool hasLocalFood) {
    this->hasLocalFood = hasLocalFood;
}

std::string Restaurant::getCategory() const {
    return "Restaurant";
}

void Restaurant::printShortInfo() const {
    cout << "[" << getId() << "] " << getName() << " | Category: " << getCategory()
         << " | Rating: " << getRating() << " | Price: " << getPrice() << endl;
}

void Restaurant::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Cuisine type: " << cuisineType << '\n';
    cout << "Local food available: " << (hasLocalFood ? "Yes" : "No") << endl;
}

double Restaurant::calculateAttractiveness() const {
    double score = getRating();

    if (hasLocalFood) {
        score += 0.5;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

std::string Restaurant::serialize() const {
    std::ostringstream out;

    out << getCategory() << '|' << getId() << '|' << getName() << '|' << getDescription() << '|'
        << getRating() << '|' << getPrice() << '|' << cuisineType << '|' << hasLocalFood;

    return out.str();
}

void Restaurant::updateFromInput() {
    string newName, newDescription, newCuisineType;
    double newRating, newPrice;
    char newLocalFoodInput;

    cout << "Enter new name (current: " << getName() << "): ";
    std::getline(cin, newName);
    setName(newName);

    cout << "Enter new description (current: " << getDescription() << "): ";
    std::getline(cin, newDescription);
    setDescription(newDescription);

    while (true) {
        cout << "Enter new rating (0-5) (current: " << getRating() << "): ";
        
        if (!(cin >> newRating)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
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

    cout << "Enter new cuisine type (current: " << cuisineType << "): ";
    std::getline(cin, newCuisineType);
    setCuisineType(newCuisineType);

    cout << "Does it have local food? (y/n) (current: " << (hasLocalFood ? "Yes" : "No") << "): ";
    while (true) {
        cin >> newLocalFoodInput;

        if (newLocalFoodInput == 'y' || newLocalFoodInput == 'Y') {
            setHasLocalFood(true);
            break;
        } else if (newLocalFoodInput == 'n' || newLocalFoodInput == 'N') {
            setHasLocalFood(false);
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n': ";
        }
    }
    cin.ignore(1000, '\n');
}