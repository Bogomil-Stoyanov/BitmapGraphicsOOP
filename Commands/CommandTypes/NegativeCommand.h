

#ifndef BITMAPGRAPHICS_NEGATIVECOMMAND_H
#define BITMAPGRAPHICS_NEGATIVECOMMAND_H


#include "Command.h"

class NegativeCommand : public Command{
public:
 NegativeCommand(): Command(CommandType::NEGATIVE){}
};


#endif //BITMAPGRAPHICS_NEGATIVECOMMAND_H
