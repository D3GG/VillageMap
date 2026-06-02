#include "Interface.h"

#include <sstream>
#include <stdexcept>

namespace Interface {

CommandInfo commands[] = {
    {"create", Create, "Creates a new settlement file", "create <file>", 1, 1, Base},
    {"load", Load, "Loads an existing settlement file", "load <file>", 1, 1, Base},
    {"help", Help, "Prints all commands or help for one command", "help or help <command>", 0, 1,
     Both},
    {"exit", Exit, "Exits the program", "exit", 0, 0, Both},
    {"info", Info, "Prints information about the current settlement", "info", 0, 0, Inner},
    {"add", Add, "Adds a tourist object", "add <type>", 1, 1, Inner},
    {"list", List, "Lists all tourist objects", "list", 0, 0, Inner},
    {"show", Show, "Shows one tourist object by ID", "show <id>", 1, 1, Inner},
    {"delete", Delete, "Deletes one tourist object by ID", "delete <id>", 1, 1, Inner},
    {"update", Update, "Updates one tourist object by ID", "update <id>", 1, 1, Inner},
    {"search", Search, "Searches by name, description, or category", "search <text>", 1, 1, Inner},
    {"filter", Filter, "Filters objects", "filter <criteria>", 1, 1, Inner},
    {"report", Report, "Generates settlement statistics", "report", 0, 0, Inner},
    {"save", Save, "Saves the current settlement", "save", 0, 0, Inner},
    {"close", Close, "Closes the current settlement", "close", 0, 0, Inner}};

std::vector<std::string> tokenize(const std::string& inputLn) {
    std::vector<std::string> output;
    std::istringstream stream(inputLn);
    std::string currToken;

    while (stream >> currToken) {
        output.push_back(currToken);
    }

    return output;
}

CommandType stringToCmdType(const std::string token) {
    for (std::size_t i = 0; i < COMMAND_COUNT; i++) {
        if (token == commands[i].name) {
            return commands[i].type;
        }
    }

    return CommandType::Unknown;
}

MenuStates stringToMenuState(const std::string token) {
    if (token == "Base") {
        return MenuStates::Base;
    }

    if (token == "Inner") {
        return MenuStates::Inner;
    }

    if (token == "Both") {
        return MenuStates::Both;
    }

    return MenuStates::Unknown1;
}

ParsedCommand parseTokens(const std::vector<std::string>& tokens, MenuStates state) {
    if (tokens.empty()) {
        throw std::runtime_error("Empty command");
    }

    CommandType type = stringToCmdType(tokens.at(0));

    if (type == CommandType::Unknown) {
        throw std::runtime_error("Unknown command");
    }

    ParsedCommand newCommand;
    newCommand.type = type;
    newCommand.args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (newCommand.args.size() < commands[type].minArguments ||
        newCommand.args.size() > commands[type].maxArguments) {
        throw std::runtime_error("Invalid number of arguments.\nUsage: " + commands[type].usage);
    }

    if (commands[type].allowedStates != MenuStates::Both && commands[type].allowedStates != state) {
        throw std::runtime_error("Invalid state for such command");
    }

    return newCommand;
}

} // namespace Interface