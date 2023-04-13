

#ifndef BITMAPGRAPHICS_ROTATECOMMAND_H
#define BITMAPGRAPHICS_ROTATECOMMAND_H


#include "Command.h"
#include <string>

class RotateCommand : public Command{
private:
    std::string rotation;

public:
    explicit RotateCommand(std::string rotation);
    std::string getRotation();
};


#endif //BITMAPGRAPHICS_ROTATECOMMAND_H
