#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace Interface {

enum CommandType {
    Create,
    Load,
    Help,
    Exit,
    Info,
    Add,
    List,
    Show,
    Delete,
    Update,
    Search,
    Filter,
    Report,
    Save,
    Close
};

enum MenuStates { Base, Inner, Both };

struct CommandInfo {
    std::string name;
    CommandType type;
    std::string description;
    std::string usage;
    std::size_t minArguments;
    std::size_t maxArguments;
    MenuStates allowedStates;
};

extern CommandInfo commands[];

struct ParsedCommand {
    CommandType type;
    std::vector<std::string> args;
    bool valid;
    std::string errMsg;
};

// menus
void printMenu(MenuStates state);

// sanitizer - mby

// tokenizer
std::vector<std::string> tokenize(const std::string& inputLn);

// parser
void parseTokens(const std::vector<std::string>& tokens);

// executor
void executeCommand(ParsedCommand command);

} // namespace Interface