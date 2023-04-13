#ifndef BITMAPGRAPHICS_SESSIONMANAGER_H
#define BITMAPGRAPHICS_SESSIONMANAGER_H

#include "../Commands/CommandTypes/Command.h"
#include "Session/Session.h"
#include <vector>


class SessionManager {

private:
    std::vector<Session> sessions;

public:
    void execute(Command* command);
};


#endif //BITMAPGRAPHICS_SESSIONMANAGER_H
