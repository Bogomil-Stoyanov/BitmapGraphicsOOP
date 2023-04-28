

#include "RotateCommand.h"

#include <utility>

RotateCommand::RotateCommand(std::string rotation) : Command(CommandType::ROTATE), rotation(std::move(rotation)) {}

std::string RotateCommand::getRotation() {
    return rotation;
}
