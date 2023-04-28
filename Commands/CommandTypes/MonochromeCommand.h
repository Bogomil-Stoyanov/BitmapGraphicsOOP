

#ifndef BITMAPGRAPHICS_MONOCHROMECOMMAND_H
#define BITMAPGRAPHICS_MONOCHROMECOMMAND_H


#include "Command.h"

class MonochromeCommand : public Command{
public:
 MonochromeCommand(): Command(CommandType::MONOCHROME){}
};


#endif //BITMAPGRAPHICS_MONOCHROMECOMMAND_H
