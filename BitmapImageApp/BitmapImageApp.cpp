#include "BitmapImageApp.h"
#include "../Commands/CommandDispatcher.h"
#include "../Commands/CommandTypes/Command.h"
#include "../Commands/CommandTypes/ErrorCommand.h"
#include "../Commands/CommandTypes/ExitCommand.h"
#include <iostream>

BitmapImageApp &BitmapImageApp::getInstance() {
    static BitmapImageApp app;
    return app;
}

void BitmapImageApp::start() {
    std::string input;
    Command *command = nullptr;
    do {
        std::getline(std::cin, input);
        delete command;
        command = CommandDispatcher::analyzeCommand(input);

        if (command->getCommandType() != CommandType::ERROR && command->getCommandType() != CommandType::EXIT) {
            manager.execute(command);
        }

    } while (command->getCommandType() != CommandType::EXIT);

    delete command;
    std::cout << "END" << std::endl;
}
