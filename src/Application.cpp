#include "Application.h"

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

namespace Application {

namespace {

void applyExecutionResult(Interface::ExecutionResult result, Interface::MenuStates& state) {
    switch (result) {
    case Interface::ExecutionResult::Continue:
        break;

    case Interface::ExecutionResult::ExitProgram:
        break;

    case Interface::ExecutionResult::SwitchToBase:
        state = Interface::MenuStates::Base;
        break;

    case Interface::ExecutionResult::SwitchToInner:
        state = Interface::MenuStates::Inner;
        break;
    }
}

void printPrompt(Interface::MenuStates state) {
    if (state == Interface::MenuStates::Base) {
        std::cout << "\nVillageMap> ";
    } else {
        std::cout << "\nVillageMap[file]> ";
    }
}

} // namespace

int run() {
    Interface::MenuStates state = Interface::MenuStates::Base;

    std::cout << "VillageMap CLI started.\n";
    std::cout << "Type 'help' to see available commands.\n";

    bool isRunning = true;

    while (isRunning) {
        printPrompt(state);

        std::string inputLine;
        if (!std::getline(std::cin, inputLine)) {
            break;
        }

        try {
            std::vector<std::string> tokens = Interface::tokenize(inputLine);

            if (tokens.empty()) {
                continue;
            }

            Interface::ParsedCommand command = Interface::parseTokens(tokens, state);
            Interface::ExecutionResult result = executeCommand(command, state);

            if (result == Interface::ExecutionResult::ExitProgram) {
                isRunning = false;
            }

            applyExecutionResult(result, state);
        } catch (const std::exception& error) {
            std::cout << "Error: " << error.what() << '\n';
        }
    }

    return 0;
}

Interface::ExecutionResult executeCommand(Interface::ParsedCommand command,
                                          Interface::MenuStates state) {
    switch (command.type) {
    case Interface::CommandType::Create:
        // command.args[0] = file name
        std::cout << "Create file: " << command.args[0] << '\n';
        return Interface::ExecutionResult::SwitchToInner;

    case Interface::CommandType::Load:
        // command.args[0] = file name
        std::cout << "Load file: " << command.args[0] << '\n';
        return Interface::ExecutionResult::SwitchToInner;

    case Interface::CommandType::Help:
        if (command.args.empty()) {
            for (std::size_t i = 0; i < Interface::COMMAND_COUNT; i++) {
                if (Interface::commands[i].allowedStates == state ||
                    Interface::commands[i].allowedStates == Interface::MenuStates::Both) {
                    std::cout << Interface::commands[i].name << " - "
                              << Interface::commands[i].usage << " "
                              << Interface::commands[i].description << '\n';
                }
            }

            return Interface::ExecutionResult::Continue;
        }

        {
            Interface::CommandType helpCommandType =
                Interface::stringToCmdType(command.args.front());

            if (helpCommandType == Interface::CommandType::Unknown) {
                throw std::runtime_error("Unknown command for help.");
            }

            std::cout << Interface::commands[helpCommandType].name << " - "
                      << Interface::commands[helpCommandType].usage << " "
                      << Interface::commands[helpCommandType].description << '\n';

            return Interface::ExecutionResult::Continue;
        }

    case Interface::CommandType::Exit:
        return Interface::ExecutionResult::ExitProgram;

    case Interface::CommandType::Info:
        // print settlement info
        std::cout << "Info command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Add:
        // start add logic
        std::cout << "Add command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::List:
        // list objects
        std::cout << "List command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Show:
        // show object by id/name
        std::cout << "Show command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Delete:
        // delete object
        std::cout << "Delete command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Update:
        // update object
        std::cout << "Update command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Search:
        // search objects
        std::cout << "Search command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Filter:
        // filter objects
        std::cout << "Filter command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Report:
        // generate report
        std::cout << "Report command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Save:
        // save current file
        std::cout << "Save command selected.\n";
        return Interface::ExecutionResult::Continue;

    case Interface::CommandType::Close:
        // close current file
        std::cout << "Close command selected.\n";
        return Interface::ExecutionResult::SwitchToBase;

    default:
        throw std::runtime_error("Executor received unknown command.");
    }
}

} // namespace Application