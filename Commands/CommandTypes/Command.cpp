

#include "Command.h"

Command::~Command() = default;

CommandType Command::getCommandType() const {
    return commandType;
}

Command::Command(CommandType commandType) {
    this->commandType=commandType;
}
