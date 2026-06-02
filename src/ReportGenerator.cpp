#include "ReportGenerator.h"

#include <iostream>

namespace ReportGenerator {

void printReport(const Settlement& settlement) {
    std::cout << "===== Tourism Report =====\n";
    std::cout << "Settlement: " << settlement.getName() << '\n';
    std::cout << "Region: " << settlement.getRegion() << '\n';
    std::cout << "Population: " << settlement.getPopulation() << '\n';
    std::cout << "Description: " << settlement.getDescription() << '\n';
    std::cout << "Tourist objects: " << settlement.getObjectCount() << '\n';
    std::cout << "Average rating: " << settlement.getAverageRating() << '\n';
    std::cout << "Tourism potential score: " << settlement.getTourismPotentialScore() << '\n';

    std::cout << "\nRecommendations:\n";

    if (settlement.getObjectCount() == 0) {
        std::cout << "- Add tourist objects before generating a meaningful report.\n";
        return;
    }

    if (settlement.getTourismPotentialScore() >= 4.5) {
        std::cout << "- This settlement has strong tourism potential.\n";
        std::cout << "- It is suitable for active promotion.\n";
    } else if (settlement.getTourismPotentialScore() >= 3.0) {
        std::cout << "- This settlement has moderate tourism potential.\n";
        std::cout << "- Improve object descriptions, services, and accessibility.\n";
    } else {
        std::cout << "- This settlement needs more developed tourist objects.\n";
        std::cout << "- Add landmarks, restaurants, guest houses, festivals, or eco paths.\n";
    }
}

} // namespace ReportGenerator