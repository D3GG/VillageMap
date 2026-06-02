#include "Interface.h"

#include <sstream>
#include <stdexcept>

namespace Interface {

CommandInfo commands[COMMAND_COUNT] = {
    {"create", CommandType::Create, "Creates a new file", "create <file>", 1, 1, MenuStates::Base},
    {"load", CommandType::Load, "Loads an existing file", "load <file>", 1, 1, MenuStates::Base},
    {"help", CommandType::Help,
     "Print all available commands and their usage or just for a specified command",
     "help or help <command>", 0, 1, MenuStates::Both},
    {"exit", CommandType::Exit, "Exits the program", "exit", 0, 0, MenuStates::Base},
    {"info", CommandType::Info, "Print information about the Settlement", "info", 0, 0,
     MenuStates::Inner},
    {"add", CommandType::Add, "Tbd", "add <type>", 1, 1, MenuStates::Inner},
    {"list", CommandType::List, "Tbd", "list", 0, 0, MenuStates::Inner},
    {"show", CommandType::Show, "Tbd", "show <id>", 1, 1, MenuStates::Inner},
    {"delete", CommandType::Delete, "Tbd", "delete <id>", 1, 1, MenuStates::Inner},
    {"update", CommandType::Update, "Tbd", "update <id>", 1, 1, MenuStates::Inner},
    {"search", CommandType::Search, "Tbd", "search <text>", 1, 1, MenuStates::Inner},
    {"filter", CommandType::Filter, "Tbd", "filter <criteria>", 1, 1, MenuStates::Inner},
    {"report", CommandType::Report, "Tbd", "report", 0, 0, MenuStates::Inner},
    {"save", CommandType::Save, "Saves the current file", "save", 0, 0, MenuStates::Inner},
    {"close", CommandType::Close, "Closes the current file", "close", 0, 0, MenuStates::Inner}};

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