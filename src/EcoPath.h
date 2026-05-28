#pragma once
#include "TouristObject.h"

#include <string>

class EcoPath : public TouristObject {
private:
    double length;
    std::string difficulty;
    double duration;

public:
    EcoPath(int id, const std::string& name, const std::string& description, double rating,
            double price, double length, const std::string& difficulty, double duration);

    ~EcoPath() override = default;

    double getLength() const;
    std::string getDifficulty() const;
    double getDuration() const;

    void setLength(double length);
    void setDifficulty(const std::string& difficulty);
    void setDuration(double duration);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};
