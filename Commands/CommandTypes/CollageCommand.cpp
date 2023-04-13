

#include "CollageCommand.h"

#include <utility>

CollageCommand::CollageCommand(std::string path1, std::string path2, std::string outPath) : path1(std::move(
        path1)), path2(std::move(path2)), outPath(std::move(outPath)) {}

const std::string &CollageCommand::getPath1() const {
    return path1;
}

const std::string &CollageCommand::getPath2() const {
    return path2;
}

const std::string &CollageCommand::getOutPath() const {
    return outPath;
}
