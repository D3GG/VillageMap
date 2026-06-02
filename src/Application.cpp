#include "Application.h"

#include "FileManager.h"
#include "ReportGenerator.h"
#include "Settlement.h"
#include "TouristObjFactory.h"

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

namespace Application {

namespace {

Interface::MenuStates currentState = Interface::Base;
std::unique_ptr<Settlement> currentSettlement = nullptr;
std::string currentFileName;

void ensureSettlementOpen() {
    if (currentSettlement == nullptr) {
        throw std::runtime_error("No settlement is currently loaded.");
    }
}

int getNextObjectId() {
    ensureSettlementOpen();

    int id = 1;

    while (currentSettlement->findObjectById(id) != nullptr) {
        id++;
    }

    return id;
}

int parseIntArgument(const std::string& text, const std::string& argumentName) {
    std::size_t processed = 0;
    int value = 0;

    try {
        value = std::stoi(text, &processed);
    } catch (...) {
        throw std::runtime_error("Invalid " + argumentName + ".");
    }

    if (processed != text.size()) {
        throw std::runtime_error("Invalid " + argumentName + ".");
    }

    return value;
}

void printPrompt() {
    if (currentState == Interface::Base) {
        std::cout << "\nVillageMap> ";
    } else {
        std::cout << "\nVillageMap[" << currentSettlement->getName() << "]> ";
    }
}

void applyExecutionResult(Interface::ExecutionResult result) {
    switch (result) {
    case Interface::Continue:
        break;

    case Interface::ExitProgram:
        break;

    case Interface::SwitchToBase:
        currentState = Interface::Base;
        break;

    case Interface::SwitchToInner:
        currentState = Interface::Inner;
        break;
    }
}

void printHelp(const Interface::ParsedCommand& command, Interface::MenuStates state) {
    if (command.args.empty()) {
        for (std::size_t i = 0; i < Interface::COMMAND_COUNT; i++) {
            const Interface::CommandInfo& info = Interface::commands[i];

            if (info.allowedStates == state || info.allowedStates == Interface::Both) {
                std::cout << info.name << " - " << info.usage << " - " << info.description << '\n';
            }
        }

        return;
    }

    Interface::CommandType type = Interface::stringToCmdType(command.args.front());

    if (type == Interface::Unknown) {
        throw std::runtime_error("Unknown command for help.");
    }

    const Interface::CommandInfo& info = Interface::commands[type];

    std::cout << info.name << " - " << info.usage << " - " << info.description << '\n';
}

std::string readRequiredLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;

        std::string value;
        if (!std::getline(std::cin, value)) {
            throw std::runtime_error("Input closed.");
        }

        if (!value.empty()) {
            return value;
        }

        std::cout << "Value cannot be empty.\n";
    }
}

int readInt(const std::string& prompt) {
    while (true) {
        try {
            return parseIntArgument(readRequiredLine(prompt), "number");
        } catch (const std::exception& error) {
            std::cout << error.what() << '\n';
        }
    }
}

void createSettlement(const std::string& fileName) {
    std::string name = readRequiredLine("Settlement name: ");
    std::string region = readRequiredLine("Region: ");
    int population = readInt("Population: ");
    std::string description = readRequiredLine("Description: ");

    currentSettlement = std::make_unique<Settlement>(name, region, population, description);

    currentFileName = fileName;

    FileManager::saveFile(currentFileName, *currentSettlement);

    std::cout << "Created settlement '" << currentSettlement->getName() << "' in file '"
              << currentFileName << "'.\n";
}

void loadSettlement(const std::string& fileName) {
    currentSettlement = FileManager::loadFile(fileName);
    currentFileName = fileName;

    std::cout << "Loaded settlement '" << currentSettlement->getName() << "' from file '"
              << currentFileName << "'.\n";
}

} // namespace

int run() {
    std::cout << "===== VillageMap CLI =====\n";
    std::cout << "Type 'help' to see available commands.\n";

    bool isRunning = true;

    while (isRunning) {
        printPrompt();

        std::string inputLine;
        if (!std::getline(std::cin, inputLine)) {
            break;
        }

        try {
            std::vector<std::string> tokens = Interface::tokenize(inputLine);

            if (tokens.empty()) {
                continue;
            }

            Interface::ParsedCommand command = Interface::parseTokens(tokens, currentState);
            Interface::ExecutionResult result = executeCommand(command, currentState);

            if (result == Interface::ExitProgram) {
                isRunning = false;
            }

            applyExecutionResult(result);
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}

Interface::ExecutionResult executeCommand(Interface::ParsedCommand command,
                                          Interface::MenuStates state) {
    switch (command.type) {
    case Interface::Create:
        createSettlement(command.args.at(0));
        return Interface::SwitchToInner;

    case Interface::Load:
        loadSettlement(command.args.at(0));
        return Interface::SwitchToInner;

    case Interface::Help:
        printHelp(command, state);
        return Interface::Continue;

    case Interface::Exit:
        return Interface::ExitProgram;

    case Interface::Info:
        ensureSettlementOpen();
        currentSettlement->printInfo();
        return Interface::Continue;

    case Interface::Add: {
        ensureSettlementOpen();

        int nextId = getNextObjectId();

        currentSettlement->addObject(
            TouristObjFactory::createFromInput(command.args.at(0), nextId)
        );

        std::cout << "Tourist object added successfully.\n";
        return Interface::Continue;
    }

    case Interface::List:
        ensureSettlementOpen();
        currentSettlement->listObjects();
        return Interface::Continue;

    case Interface::Show:
        ensureSettlementOpen();
        currentSettlement->showObjectById(parseIntArgument(command.args.at(0), "id"));
        return Interface::Continue;

    case Interface::Delete:
        ensureSettlementOpen();

        if (currentSettlement->removeObjectById(parseIntArgument(command.args.at(0), "id"))) {
            std::cout << "Tourist object deleted successfully.\n";
        } else {
            std::cout << "Tourist object was not found.\n";
        }

        return Interface::Continue;

    case Interface::Update: {
        ensureSettlementOpen();

        int id = parseIntArgument(command.args.at(0), "id");
        TouristObject* object = currentSettlement->findObjectById(id);

        if (object == nullptr) {
            std::cout << "Tourist object was not found.\n";
            return Interface::Continue;
        }

        object->updateFromInput();
        std::cout << "Tourist object updated successfully.\n";

        return Interface::Continue;
    }

    case Interface::Search:
        ensureSettlementOpen();
        currentSettlement->searchObjects(command.args.at(0));
        return Interface::Continue;

    case Interface::Filter:
        ensureSettlementOpen();
        currentSettlement->filterObjectsByCategory(command.args.at(0));
        return Interface::Continue;

    case Interface::Report:
        ensureSettlementOpen();
        ReportGenerator::printReport(*currentSettlement);
        return Interface::Continue;

    case Interface::Save:
        ensureSettlementOpen();
        FileManager::saveFile(currentFileName, *currentSettlement);
        std::cout << "File saved successfully.\n";
        return Interface::Continue;

    case Interface::Close:
        ensureSettlementOpen();
        currentSettlement.reset();
        currentFileName.clear();
        std::cout << "Settlement closed.\n";
        return Interface::SwitchToBase;

    default:
        throw std::runtime_error("Executor received unknown command.");
    }
}

} // namespace Application