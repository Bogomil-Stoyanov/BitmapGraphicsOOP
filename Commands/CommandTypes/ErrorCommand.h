#ifndef BITMAPGRAPHICS_ERRORCOMMAND_H
#define BITMAPGRAPHICS_ERRORCOMMAND_H

#include "Command.h"


class ErrorCommand : public Command{
public:
    ErrorCommand(): Command(CommandType::ERROR){}
};


#endif //BITMAPGRAPHICS_ERRORCOMMAND_H
