

#ifndef BITMAPGRAPHICS_SWITCHCOMMAND_H
#define BITMAPGRAPHICS_SWITCHCOMMAND_H


#include "Command.h"

class SwitchCommand : public Command{
private:
    int session;

public:
    explicit SwitchCommand(int session);
    int getSession();
};


#endif //BITMAPGRAPHICS_SWITCHCOMMAND_H
