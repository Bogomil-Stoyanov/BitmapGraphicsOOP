

#include "SwitchCommand.h"

SwitchCommand::SwitchCommand(int session) : session(session) {}

int SwitchCommand::getSession() {
    return session;
}
