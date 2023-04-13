

#include "SessionManager.h"

#include "../Commands/CommandTypes/ErrorCommand.h"
#include "../Commands/CommandTypes/ExitCommand.h"
#include "../Commands/CommandTypes/LoadCommand.h"
#include "../Commands/CommandTypes/AddCommand.h"
#include "../Commands/CommandTypes/Command.h"
#include "../Commands/CommandTypes/SaveCommand.h"
#include "../Commands/CommandTypes/CloseCommand.h"
#include "../Commands/CommandTypes/HelpCommand.h"
#include "../Commands/CommandTypes/SaveAsCommand.h"
#include "../Commands/CommandTypes/GrayscaleCommand.h"
#include "../Commands/CommandTypes/MonochromeCommand.h"
#include "../Commands/CommandTypes/NegativeCommand.h"
#include "../Commands/CommandTypes/RotateCommand.h"
#include "../Commands/CommandTypes/UndoCommand.h"
#include "../Commands/CommandTypes/SessionInfoCommand.h"
#include "../Commands/CommandTypes/SwitchCommand.h"
#include "../Commands/CommandTypes/CollageCommand.h"
#include "../Commands/CommandTypes/Command.h"
#include <iostream>

void SessionManager::execute(Command *command) {
    if (dynamic_cast<AddCommand *>(command) != nullptr) {
        auto addCommand = dynamic_cast<AddCommand *>(command);
        std::cout << "add command " << addCommand->getPath() << std::endl;
    } else if (dynamic_cast<CloseCommand *>(command) != nullptr) {
        auto closeCommand = dynamic_cast<CloseCommand *>(command);
        std::cout << "close command" << std::endl;
    } else if (dynamic_cast<CollageCommand *>(command) != nullptr) {
        auto collageCommand = dynamic_cast<CollageCommand *>(command);
        std::cout << "collage command " << collageCommand->getPath1() << " " << collageCommand->getPath2() << " "
                  << collageCommand->getOutPath() << std::endl;
    }else  if (dynamic_cast<GrayscaleCommand *>(command) != nullptr) {
        auto grayscaleCommand = dynamic_cast<GrayscaleCommand *>(command);
        std::cout << "grayscale command" << std::endl;
    }else  if (dynamic_cast<LoadCommand *>(command) != nullptr) {
        auto loadCommand = dynamic_cast<LoadCommand *>(command);
        std::cout << "load command ";
        for(int i =0;i<loadCommand->getFilePaths().size();i++){
            std::cout<<loadCommand->getFilePaths()[i] <<" ";
        }
        std::cout<<std::endl;
    }else  if (dynamic_cast<MonochromeCommand *>(command) != nullptr) {
        auto monochromeCommand = dynamic_cast<MonochromeCommand *>(command);
        std::cout << "monochrome command" << std::endl;
    }else  if (dynamic_cast<NegativeCommand *>(command) != nullptr) {
        auto negativeCommand = dynamic_cast<NegativeCommand *>(command);
        std::cout << "negative command " << std::endl;
    }else  if (dynamic_cast<RotateCommand *>(command) != nullptr) {
        auto rotateCommand = dynamic_cast<RotateCommand *>(command);
        std::cout << "rotate command " << rotateCommand->getRotation() << std::endl;
    }else  if (dynamic_cast<SaveAsCommand *>(command) != nullptr) {
        auto saveasCommand = dynamic_cast<SaveAsCommand *>(command);
        std::cout << "saveAs command " << saveasCommand->getPath()<< std::endl;
    }else  if (dynamic_cast<SaveCommand *>(command) != nullptr) {
        auto saveCommand = dynamic_cast<SaveCommand *>(command);
        std::cout << "save command" << std::endl;
    }else  if (dynamic_cast<SessionInfoCommand *>(command) != nullptr) {
        auto sessionInfoCommand = dynamic_cast<SessionInfoCommand *>(command);
        std::cout << "session info command" << std::endl;
    }else  if (dynamic_cast<SwitchCommand *>(command) != nullptr) {
        auto switchCommand = dynamic_cast<SwitchCommand *>(command);
        std::cout << "switch command " << switchCommand->getSession() << std::endl;
    }else  if (dynamic_cast<UndoCommand *>(command) != nullptr) {
        auto undoCommand = dynamic_cast<UndoCommand *>(command);
        std::cout << "undo command" << std::endl;
    }
}
