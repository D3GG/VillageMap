#include "CraftWorkshop.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

CraftWorkshop::CraftWorkshop(int id, const string& name, const string& description, double rating,
                             double price, const string& craftType, bool hasDemonstration)
    : TouristObject(id, name, description, rating, price) {
    setCraftType(craftType);
    setHasDemonstration(hasDemonstration);
}

std::string CraftWorkshop::getCraftType() const {
    return craftType;
}

bool CraftWorkshop::getHasDemonstration() const {
    return hasDemonstration;
}

void CraftWorkshop::setCraftType(const std::string& craftType) {
    if (craftType.empty()) {
        throw std::invalid_argument("Craft type cannot be empty.");
    }

    this->craftType = craftType;
}

void CraftWorkshop::setHasDemonstration(bool hasDemonstration) {
    this->hasDemonstration = hasDemonstration;
}

std::string CraftWorkshop::getCategory() const {
    return "Craft Workshop";
}

void CraftWorkshop::printShortInfo() const {
    cout << "[" << getId() << "] " << getName() << " | Category: " << getCategory()
         << " | Rating: " << getRating() << " | Price: " << getPrice() << endl;
}

void CraftWorkshop::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Craft type: " << craftType << '\n';
    cout << "Demonstration available: " << (hasDemonstration ? "Yes" : "No") << endl;
}

double CraftWorkshop::calculateAttractiveness() const {
    double score = getRating();

    if (hasDemonstration) {
        score += 0.5;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

std::string CraftWorkshop::serialize() const {
    std::ostringstream out;

    out << getCategory() << '|' << getId() << '|' << getName() << '|' << getDescription() << '|'
        << getRating() << '|' << getPrice() << '|' << craftType << '|' << hasDemonstration;

    return out.str();
}

void CraftWorkshop::updateFromInput() {
    string newName, newDescription, newCraftType;
    double newRating, newPrice;
    char newDemonstrationInput;

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
        } else {
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
        } else {
            setPrice(newPrice);
            cin.ignore(1000, '\n');
            break;
        }
    }

    cout << "Enter new craft type (current: " << craftType << "): ";
    std::getline(cin, newCraftType);
    setCraftType(newCraftType);

    cout << "Does it have a demonstration? (y/n) (current: " << (hasDemonstration ? "Yes" : "No")
         << "): ";
    while (true) {
        cin >> newDemonstrationInput;

        if (newDemonstrationInput == 'y' || newDemonstrationInput == 'Y') {
            setHasDemonstration(true);
            break;
        } else if (newDemonstrationInput == 'n' || newDemonstrationInput == 'N') {
            setHasDemonstration(false);
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n':";
        }
    }
    cin.ignore(1000, '\n');
}