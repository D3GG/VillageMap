#include "Interface.h"

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

} // namespace Interface
