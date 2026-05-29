#pragma once
#include "TouristObject.h"

#include <string>

class CraftWorkshop : public TouristObject {
private:
    std::string craftType;
    bool hasDemonstration;

public:
    CraftWorkshop(int id, const std::string& name, const std::string& description, double rating,
                    double price, const std::string& craftType, bool hasDemonstration);

    ~CraftWorkshop() = default;

    std::string getCraftType() const;
    bool getHasDemonstration() const;

    void setCraftType(const std::string& craftType);
    void setHasDemonstration(bool hasDemonstration);

    std::string getCategory() const override;

    void printShortInfo() const override;
    void printFullInfo() const override;

    double calculateAttractiveness() const override;

    std::string serialize() const override;

    void updateFromInput() override;
};