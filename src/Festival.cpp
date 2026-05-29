#include "Festival.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

Festival::Festival(int id, const std::string& name, const std::string& description, double rating,
                    double price, const std::string& date, const std::string& theme, bool isAnnual)
    : TouristObject(id, name, description, rating, price), date(date), theme(theme),
      isAnnual(isAnnual) {
    if (date.empty()) {
        throw std::invalid_argument("Date cannot be empty.");
    }
    if (theme.empty()) {
        throw std::invalid_argument("Theme cannot be empty.");
    }
}

std::string Festival::getDate() const {
    return date;
}

std::string Festival::getTheme() const {
    return theme;
}

bool Festival::getIsAnnual() const {
    return isAnnual;
}

void Festival::setDate(const std::string& date) {
    if (date.empty()) {
        throw std::invalid_argument("Date cannot be empty.");
    }

    this->date = date;
}

void Festival::setTheme(const std::string& theme) {
    if (theme.empty()) {
        throw std::invalid_argument("Theme cannot be empty.");
    }

    this->theme = theme;
}

void Festival::setIsAnnual(bool isAnnual) {
    this->isAnnual = isAnnual;
}

std::string Festival::getCategory() const {
    return "Festival";
}

void Festival::printShortInfo() const {
    cout << "[" << getId() << "] " << getName() << " | Category: " << getCategory()
         << " | Rating: " << getRating() << " | Price: " << getPrice() << endl;
}

void Festival::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Date: " << date << '\n';
    cout << "Theme: " << theme << '\n';
    cout << "Annual event: " << (isAnnual ? "Yes" : "No") << endl;
}

double Festival::calculateAttractiveness() const {
    double score = getRating();

    if (isAnnual) {
        score += 0.5;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

std::string Festival::serialize() const {
    std::ostringstream out;

    out << getCategory() << '|' << getId() << '|' << getName() << '|' << getDescription() << '|'
        << getRating() << '|' << getPrice() << '|' << date << '|' << theme << '|' << isAnnual;

    return out.str();
}

void Festival::updateFromInput() {
    string newName, newDescription, newDate, newTheme;
    double newRating, newPrice;
    char newAnnualInput;

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

    cout << "Enter new date (current: " << date << "): ";
    std::getline(cin, newDate);
    setDate(newDate);

    cout << "Enter new theme (current: " << theme << "): ";
    std::getline(cin, newTheme);
    setTheme(newTheme);

    cout << "Is it an annual event? (y/n) (current: " << (isAnnual ? "Yes" : "No") << "): ";
    while (true) {
        cin >> newAnnualInput;

        if (newAnnualInput == 'y' || newAnnualInput == 'Y') {
            setIsAnnual(true);
            break;
        } else if (newAnnualInput == 'n' || newAnnualInput == 'N') {
            setIsAnnual(false);
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n': ";
        }
    }
    cin.ignore(1000, '\n');
}