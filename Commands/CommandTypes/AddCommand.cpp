

#include "AddCommand.h"

#include <utility>

AddCommand::AddCommand(std::string path) : Command(CommandType::ADD), path(std::move(path)) {}

std::string AddCommand::getPath() {
    return path;
}
