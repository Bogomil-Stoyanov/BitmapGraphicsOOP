

#ifndef BITMAPGRAPHICS_ADDCOMMAND_H
#define BITMAPGRAPHICS_ADDCOMMAND_H

#include <string>
#include "Command.h"

class AddCommand : public Command{
private:
    std::string path;

public:
    explicit AddCommand(const std::string &path);
    std::string getPath();
};


#endif //BITMAPGRAPHICS_ADDCOMMAND_H
