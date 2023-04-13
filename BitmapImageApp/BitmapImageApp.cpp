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
    Command *command;
    do {
        std::getline(std::cin, input);
        command = CommandDispatcher::analyzeCommand(input);

        if (dynamic_cast<ErrorCommand *>(command) != nullptr) {
            std::cout << "ERROR" << std::endl;
        } else if (dynamic_cast<ExitCommand *>(command) != nullptr) {
        }
    } while (dynamic_cast<ExitCommand *>(command) == nullptr);

    std::cout << "END" << std::endl;
}

BitmapImageApp::BitmapImageApp() {

}
