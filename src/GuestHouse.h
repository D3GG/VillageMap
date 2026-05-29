#pragma once
#include "TouristObject.h"

#include <string>

class GuestHouse : public TouristObject {
private:
    int capacity;
    double pricePerNight;
    bool hasParking;

public:
    GuestHouse(int id, const std::string& name, const std::string& description, double rating,
               double price, int capacity, double pricePerNight, bool hasParking);

    ~GuestHouse() override = default;

    int getCapacity() const;
    double getPricePerNight() const;
    bool getHasParking() const;

    void setCapacity(int capacity);
    void setPricePerNight(double pricePerNight);
    void setHasParking(bool hasParking);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};