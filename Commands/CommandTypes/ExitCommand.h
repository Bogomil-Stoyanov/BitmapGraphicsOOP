#ifndef BITMAPGRAPHICS_EXITCOMMAND_H
#define BITMAPGRAPHICS_EXITCOMMAND_H

#include "Command.h"


class ExitCommand : public Command {
public:
    ExitCommand() : Command(CommandType::EXIT) {}
};


#endif //BITMAPGRAPHICS_EXITCOMMAND_H
