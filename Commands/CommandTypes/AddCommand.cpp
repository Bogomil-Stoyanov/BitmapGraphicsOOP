

#include "AddCommand.h"

AddCommand::AddCommand(const std::string &path) : path(path) {}

std::string AddCommand::getPath() {
    return path;
}
