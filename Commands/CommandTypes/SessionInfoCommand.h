

#ifndef BITMAPGRAPHICS_SESSIONINFOCOMMAND_H
#define BITMAPGRAPHICS_SESSIONINFOCOMMAND_H


#include "Command.h"

class SessionInfoCommand : public Command{
public:
SessionInfoCommand(): Command(CommandType::SESSION_INFO){}
};


#endif //BITMAPGRAPHICS_SESSIONINFOCOMMAND_H
