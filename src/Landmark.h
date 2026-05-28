#pragma once
#include "TouristObject.h"

#include <string>

class Landmark : public TouristObject {
private:
    std::string historicalPeriod;
    bool hasGuide;

public:
    Landmark(int id, const std::string& name, const std::string& description, double rating,
             double price, const std::string& historicalPeriod, bool hasGuide);

    ~Landmark() override = default;

    std::string getHistoricalPeriod() const;
    bool getHasGuide() const;

    void setHistoricalPeriod(const std::string& historicalPeriod);
    void setHasGuide(bool hasGuide);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};