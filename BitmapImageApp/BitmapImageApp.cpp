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
            try{
                manager.execute(command);
            }catch (std::runtime_error& e){
                std::cout<<e.what()<<std::endl;
            }
        }

    } while (command->getCommandType() != CommandType::EXIT);

    delete command;


    if (manager.hasUnsavedChanges()) {
        std::cout << "You have unsaved changes? Do you want to save them before exiting? ( Y | N ):" << std::endl;
        input = "EMPTY_STRING";
        do {
            if (input != "EMPTY_STRING") {
                std::cout << "Y | N:" << std::endl;
            }
            std::getline(std::cin, input);
        } while (input != "Y" && input != "N");

        if(input=="Y"){
            manager.saveAllSessions();
        }
    }
    std::cout << "END" << std::endl;
}
