

#ifndef BITMAPGRAPHICS_HELPCOMMAND_H
#define BITMAPGRAPHICS_HELPCOMMAND_H


#include "Command.h"

class HelpCommand : public Command{
public:
    HelpCommand(): Command(CommandType::HELP){}
};


#endif //BITMAPGRAPHICS_HELPCOMMAND_H
