

#ifndef BITMAPGRAPHICS_GRAYSCALECOMMAND_H
#define BITMAPGRAPHICS_GRAYSCALECOMMAND_H


#include "Command.h"

class GrayscaleCommand : public Command{
public:
    GrayscaleCommand(): Command(CommandType::GRAYSCALE){}
};


#endif //BITMAPGRAPHICS_GRAYSCALECOMMAND_H
