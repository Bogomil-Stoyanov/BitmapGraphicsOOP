

#include "SaveAsCommand.h"

#include <utility>

SaveAsCommand::SaveAsCommand(std::string path) : Command(CommandType::SAVE_AS), path(std::move(path)) {}

const std::string &SaveAsCommand::getPath() const {
    return path;
}
