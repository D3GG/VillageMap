#include "Interface.h"
#include <iostream>
#include <sstream>

namespace Interface {
CommandInfo commands[] = {
    {"create", CommandType::Create, "Creates a new file", "create <file_name>", 1, 1,
     MenuStates::Base},
    {"load", CommandType::Load, "Loads an existing file", "load <file_name>", 1, 1,
     MenuStates::Base},
    {"help", CommandType::Help, "Print all available commands and their usage", "help", 0, 0,
     MenuStates::Both},
    {"exit", CommandType::Exit, "Exits the program", "exit", 0, 0, MenuStates::Base},
    {"info", CommandType::Info, "Print information about the Settlement", "info", 0, 0,
     MenuStates::Inner},
    {"add", CommandType::Add, "Tbd", " ", 1, 1, MenuStates::Inner},
    {"list", CommandType::List, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
    {"show", CommandType::Show, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
    {"delete", CommandType::Delete, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
    {"update", CommandType::Update, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
    {"search", CommandType::Search, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
    {"filter", CommandType::Filter, "Tbd", "Tbd", 1, 1, MenuStates::Inner},
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
    if (token == commands[0].name)
        return commands[0].type;
    if (token == commands[1].name)
        return commands[1].type;
    if (token == commands[2].name)
        return commands[2].type;
    if (token == commands[3].name)
        return commands[3].type;
    if (token == commands[4].name)
        return commands[4].type;
    if (token == commands[5].name)
        return commands[5].type;
    if (token == commands[6].name)
        return commands[6].type;
    if (token == commands[7].name)
        return commands[7].type;
    if (token == commands[8].name)
        return commands[8].type;
    if (token == commands[9].name)
        return commands[9].type;
    if (token == commands[10].name)
        return commands[10].type;
    if (token == commands[11].name)
        return commands[11].type;
    if (token == commands[12].name)
        return commands[12].type;
    if (token == commands[13].name)
        return commands[13].type;
    if (token == commands[14].name)
        return commands[14].type;

    return Unknown;
}

MenuStates stringToMenuState(const std::string token) {
    if (token == "Base")
        return Base;
    if (token == "Inner")
        return Inner;
    if (token == "Both")
        return Both;

    return Unknown1;
}

} // namespace Interface
