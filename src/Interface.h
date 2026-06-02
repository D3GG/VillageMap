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
    Close,
    Unknown
};

enum MenuStates { Base, Inner, Both, Unknown1 };

enum ExecutionResult { Continue, ExitProgram, SwitchToBase, SwitchToInner };

struct CommandInfo {
    std::string name;
    CommandType type;
    std::string description;
    std::string usage;
    std::size_t minArguments;
    std::size_t maxArguments;
    MenuStates allowedStates;
};

constexpr std::size_t COMMAND_COUNT = 15;

extern CommandInfo commands[COMMAND_COUNT];

struct ParsedCommand {
    CommandType type;
    std::vector<std::string> args;
};

MenuStates stringToMenuState(const std::string token);

CommandType stringToCmdType(const std::string token);

std::vector<std::string> tokenize(const std::string& inputLn);

ParsedCommand parseTokens(const std::vector<std::string>& tokens, MenuStates state);

} // namespace Interface