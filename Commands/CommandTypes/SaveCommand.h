

#ifndef BITMAPGRAPHICS_SAVECOMMAND_H
#define BITMAPGRAPHICS_SAVECOMMAND_H


#include "Command.h"

class SaveCommand : public Command{
public:
    SaveCommand(): Command(CommandType::SAVE){}
};


#endif //BITMAPGRAPHICS_SAVECOMMAND_H
