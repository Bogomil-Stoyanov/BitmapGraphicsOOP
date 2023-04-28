

#include "LoadCommand.h"


LoadCommand::LoadCommand(const std::vector<std::string> &filePaths) : Command(CommandType::LOAD), filePaths(filePaths) {}


std::vector<std::string> LoadCommand::getFilePaths() {
    return filePaths;
}
