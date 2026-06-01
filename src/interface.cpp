#include "Interface.h"
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace Interface {

#define CMD_COUNT 15
CommandInfo commands[] = {
    {"create", CommandType::Create, "Creates a new file", "create <file_name>", 1, 1,
     MenuStates::Base},
    {"load", CommandType::Load, "Loads an existing file", "load <file_name>", 1, 1,
     MenuStates::Base},
    {"help", CommandType::Help,
     "Print all available commands and their usage or just for a specified command",
     "help or help <cmd>", 0, 1, MenuStates::Both},
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

ParsedCommand parseTokens(const std::vector<std::string>& tokens, MenuStates state) {
    if (tokens.empty()) {
        throw std::runtime_error("Empty command");
    }

    CommandType type = stringToCmdType(tokens.at(0));

    if (type == Unknown) {
        throw std::runtime_error("Unknown command");
    }

    ParsedCommand newCommand;
    newCommand.type = type;
    newCommand.args = std::vector<std::string>(tokens.begin() + 1, tokens.end());

    if (newCommand.args.size() < commands[type].minArguments ||
        newCommand.args.size() > commands[type].maxArguments) {
        throw std::runtime_error("Invalid number of arguments. Usage: " + commands[type].usage);
    }

    if (commands[type].allowedStates != Both && commands[type].allowedStates != state) {
        throw std::runtime_error("Invalid state for such command");
    }

    return newCommand;
}

ExecutionResult executeCommand(ParsedCommand command, MenuStates state) {
    switch (command.type) {
    case CommandType::Create:
        // command.args[0] = file name
        return SwitchToInner;
        break;

    case CommandType::Load:
        // command.args[0] = file name
        return SwitchToInner;
        break;

    case CommandType::Help:
        if (command.args.empty()) {
            for (int i = 0; i < CMD_COUNT; i++) {
                if (commands[i].allowedStates == state || commands[i].allowedStates == Both) {
                    std::cout << commands[i].name << " - " << commands[i].usage << " "
                              << commands[i].description << std::endl;
                }
            }
            return;
        }
        std::cout << commands[stringToCmdType(command.args.front())].name << " - "
                  << commands[stringToCmdType(command.args.front())].usage << " "
                  << commands[stringToCmdType(command.args.front())].description << std::endl;
        return Continue;
        break;

    case CommandType::Exit:
        return ExitProgram;
        break;

    case CommandType::Info:
        // print settlement info
        return Continue;
        break;

    case CommandType::Add:
        // start add logic
        return Continue;
        break;

    case CommandType::List:
        // list objects
        return Continue;
        break;

    case CommandType::Show:
        // show object by id/name
        return Continue;
        break;

    case CommandType::Delete:
        // delete object
        return Continue;
        break;

    case CommandType::Update:
        // update object
        return Continue;
        break;

    case CommandType::Search:
        // search objects
        return Continue;
        break;

    case CommandType::Filter:
        // filter objects
        return Continue;
        break;

    case CommandType::Report:
        // generate report
        return Continue;
        break;

    case CommandType::Save:
        // save current file
        return Continue;
        break;

    case CommandType::Close:
        // close current file
        return SwitchToBase;
        break;

    default:
        throw std::runtime_error("Executor received unknown command");
    }

    return;
}

} // namespace Interface
