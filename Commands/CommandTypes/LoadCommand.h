

#ifndef BITMAPGRAPHICS_LOADCOMMAND_H
#define BITMAPGRAPHICS_LOADCOMMAND_H

#include <vector>
#include <string>
#include "Command.h"


class LoadCommand : public Command{
private:
    std::vector<std::string> filePaths;


public:
    explicit LoadCommand(const std::vector<std::string> &filePaths);
    std::vector<std::string> getFilePaths();
};


#endif //BITMAPGRAPHICS_LOADCOMMAND_H
