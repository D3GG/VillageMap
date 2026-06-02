#pragma once
#include "TouristObject.h"

#include <string>
#include <vector>

class Settlement {
private:
    std::string name;
    std::string region;
    int population;
    std::string description;
    std::vector<TouristObject*> objects;

public:
    Settlement(const std::string& name, const std::string& region, int population,
               const std::string& description);

    ~Settlement();

    std::string getName() const;
    std::string getRegion() const;
    int getPopulation() const;
    std::string getDescription() const;

    void setName(const std::string& name);
    void setRegion(const std::string& region);
    void setPopulation(int population);
    void setDescription(const std::string& description);

    void addObject(TouristObject* object);
    bool removeObjectById(int id);
    const std::vector<TouristObject*>& getObjects() const;
    TouristObject* findObjectById(int id) const;

    void listObjects() const;
    void showObjectById(int id) const;

    std::string serialize() const;
};