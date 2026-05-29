#pragma once
#include "TouristObject.h"

#include <string>

class Restaurant : public TouristObject {
private:
    std::string cuisineType;
    bool hasLocalFood;

public:
    Restaurant(int id, const std::string& name, const std::string& description, double rating,
               double price, const std::string& cuisineType, bool hasLocalFood);

    ~Restaurant() = default;

    std::string getCuisineType() const;
    bool getHasLocalFood() const;

    void setCuisineType(const std::string& cuisineType);
    void setHasLocalFood(bool hasLocalFood);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};