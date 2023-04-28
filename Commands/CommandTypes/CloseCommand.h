

#ifndef BITMAPGRAPHICS_CLOSECOMMAND_H
#define BITMAPGRAPHICS_CLOSECOMMAND_H


#include "Command.h"

class CloseCommand : public Command{

public:
    CloseCommand(): Command(CommandType::CLOSE){}
};


#endif //BITMAPGRAPHICS_CLOSECOMMAND_H
