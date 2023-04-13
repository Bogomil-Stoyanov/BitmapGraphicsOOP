

#ifndef BITMAPGRAPHICS_COLLAGECOMMAND_H
#define BITMAPGRAPHICS_COLLAGECOMMAND_H


#include "Command.h"
#include <string>

class CollageCommand : public Command{
private:
    std::string direction;
    std::string path1;
    std::string path2;
    std::string outPath;

public:
    CollageCommand(std::string direction, std::string path1, std::string path2,
                   std::string outPath);

    const std::string &getPath1() const;

    const std::string &getPath2() const;

    const std::string &getOutPath() const;

    const std::string &getDirection() const;
};


#endif //BITMAPGRAPHICS_COLLAGECOMMAND_H
