

#include "SaveAsCommand.h"

#include <utility>

SaveAsCommand::SaveAsCommand(std::string path) : path(std::move(path)) {}

const std::string &SaveAsCommand::getPath() const {
    return path;
}
