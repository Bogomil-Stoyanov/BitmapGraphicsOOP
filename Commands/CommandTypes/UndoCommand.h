

#ifndef BITMAPGRAPHICS_UNDOCOMMAND_H
#define BITMAPGRAPHICS_UNDOCOMMAND_H


#include "Command.h"

class UndoCommand : public Command {
public:
    UndoCommand() : Command(CommandType::ADD) {}
};


#endif //BITMAPGRAPHICS_UNDOCOMMAND_H
