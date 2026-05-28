#pragma once

#include <string>

class TouristObject {
private:
    int id;
    std::string name;
    std::string description;
    double rating;
    double price;

public:
    TouristObject(int id, const std::string& name, const std::string& description, double rating,
                  double price);

    virtual ~TouristObject() = default;

    int getId() const;
    std::string getName() const;
    std::string getDescription() const;
    double getRating() const;
    double getPrice() const;

    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setRating(double rating);
    void setPrice(double price);

    virtual std::string getCategory() const = 0;

    virtual void printShortInfo() const = 0;
    virtual void printFullInfo() const = 0;

    virtual double calculateAttractiveness() const = 0;

    virtual std::string serialize() const = 0;

    virtual void updateFromInput() = 0;
};