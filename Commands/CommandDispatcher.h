#ifndef BITMAPGRAPHICS_COMMANDDISPATCHER_H
#define BITMAPGRAPHICS_COMMANDDISPATCHER_H

#include <string>
#include "CommandTypes/Command.h"

class CommandDispatcher {

public:
    static Command* analyzeCommand(std::string rawCommand);
};


#endif //BITMAPGRAPHICS_COMMANDDISPATCHER_H
