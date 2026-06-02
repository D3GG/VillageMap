#include "GuestHouse.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

GuestHouse::GuestHouse(int id, const string& name, const string& description, double rating,
                       double price, int capacity, double pricePerNight, bool hasParking)
    : TouristObject(id, name, description, rating, price){
    setCapacity(capacity);
    setPricePerNight(pricePerNight);
    setHasParking(hasParking);
}

int GuestHouse::getCapacity() const {
    return capacity;
}

double GuestHouse::getPricePerNight() const {
    return pricePerNight;
}

bool GuestHouse::getHasParking() const {
    return hasParking;
}

void GuestHouse::setCapacity(int capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Capacity must be positive.");
    }

    this->capacity = capacity;
}

void GuestHouse::setPricePerNight(double pricePerNight) {
    if (pricePerNight < 0.0) {
        throw std::invalid_argument("Price per night cannot be negative.");
    }

    this->pricePerNight = pricePerNight;
}

void GuestHouse::setHasParking(bool hasParking) {
    this->hasParking = hasParking;
}

string GuestHouse::getCategory() const {
    return "GuestHouse";
}

void GuestHouse::printShortInfo() const {
    cout << "[" << getId() << "] " << getName() << " | Category: " << getCategory()
         << " | Rating: " << getRating() << " | Price per night: " << pricePerNight << endl;
}

void GuestHouse::printFullInfo() const {
    cout << "ID: " << getId() << '\n';
    cout << "Name: " << getName() << '\n';
    cout << "Category: " << getCategory() << '\n';
    cout << "Description: " << getDescription() << '\n';
    cout << "Rating: " << getRating() << '\n';
    cout << "Price: " << getPrice() << '\n';
    cout << "Capacity: " << capacity << '\n';
    cout << "Price per night: " << pricePerNight << '\n';
    cout << "Parking available: " << (hasParking ? "Yes" : "No") << endl;
}

double GuestHouse::calculateAttractiveness() const {
    double score = getRating();

    if (hasParking) {
        score += 0.3;
    }

    if (score > 5.0) {
        score = 5.0;
    }

    return score;
}

string GuestHouse::serialize() const {
    std::ostringstream out;

    out << getCategory() << '|' << getId() << '|' << getName() << '|' << getDescription() << '|'
        << getRating() << '|' << getPrice() << '|' << capacity << '|' << pricePerNight << '|'
        << hasParking;

    return out.str();
}

void GuestHouse::updateFromInput() {
    string newName, newDescription;
    double newRating, newPrice, newPricePerNight;
    int newCapacity;
    char newParkingInput;

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
        } else {
            setPrice(newPrice);
            cin.ignore(1000, '\n');
            break;
        }
    }

    while (true) {
        cout << "Enter new capacity (current: " << capacity << "): ";

        if (!(cin >> newCapacity)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
        } else {
            setCapacity(newCapacity);
            cin.ignore(1000, '\n');
            break;
        }
    }

    while (true) {
        cout << "Enter new price per night (current: " << pricePerNight << "): ";

        if (!(cin >> newPricePerNight)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Try again.\n";
        } else {
            setPricePerNight(newPricePerNight);
            cin.ignore(1000, '\n');
            break;
        }
    }

    cout << "Does it have parking? (y/n) (current: " << (hasParking ? "Yes" : "No") << "): ";
    while (true) {
        cin >> newParkingInput;

        if (newParkingInput == 'y' || newParkingInput == 'Y') {
            setHasParking(true);
            break;
        } else if (newParkingInput == 'n' || newParkingInput == 'N') {
            setHasParking(false);
            break;
        } else {
            cout << "Invalid input. Please enter 'y' or 'n': ";
        }
    }

    cin.ignore(1000, '\n');
}