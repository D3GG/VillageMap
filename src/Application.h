#pragma once

#include "Interface.h"

namespace Application {

int run();

Interface::ExecutionResult executeCommand(Interface::ParsedCommand command,
                                          Interface::MenuStates state);

} // namespace Application