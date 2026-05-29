#pragma once
#include "TouristObject.h"

#include <string>

class Festival : public TouristObject {
private:
    std::string date;
    std::string theme;
    bool isAnnual;

public:
    Festival(int id, const std::string& name, const std::string& description, double rating,
            double price, const std::string& date, const std::string& theme, bool isAnnual);

    ~Festival() override = default;

    std::string getDate() const;
    std::string getTheme() const;
    bool getIsAnnual() const;

    void setDate(const std::string& date);
    void setTheme(const std::string& theme);
    void setIsAnnual(bool isAnnual);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};