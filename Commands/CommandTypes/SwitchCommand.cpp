

#include "SwitchCommand.h"

SwitchCommand::SwitchCommand(int session) : Command(CommandType::SWITCH), session(session) {}

int SwitchCommand::getSession() {
    return session;
}
