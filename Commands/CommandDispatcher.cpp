#include "CommandDispatcher.h"
#include "CommandTypes/ErrorCommand.h"
#include "CommandTypes/ExitCommand.h"
#include "CommandTypes/LoadCommand.h"
#include "CommandTypes/AddCommand.h"
#include "CommandTypes/Command.h"
#include "CommandTypes/SaveCommand.h"
#include "CommandTypes/CloseCommand.h"
#include "CommandTypes/HelpCommand.h"
#include "CommandTypes/SaveAsCommand.h"
#include "CommandTypes/GrayscaleCommand.h"
#include "CommandTypes/MonochromeCommand.h"
#include "CommandTypes/NegativeCommand.h"
#include "CommandTypes/RotateCommand.h"
#include "CommandTypes/UndoCommand.h"
#include "CommandTypes/SessionInfoCommand.h"
#include "CommandTypes/SwitchCommand.h"
#include "CommandTypes/CollageCommand.h"
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

Command *CommandDispatcher::analyzeCommand(std::string rawCommand) {
    std::string command = std::move(rawCommand);
    std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c) { return std::tolower(c); });

    std::vector<std::string> args;
    std::istringstream iss(command);
    std::string word;
    while (iss >> word) {
        args.push_back(word);
    }

    if (args[0] == "load") {

        if (args.size() < 2) {
            std::cout << "Invalid parameters: Expected a filepath" << std::endl;
            return new ErrorCommand();
        }

        std::vector<std::string> paths;

        for (int i = 1; i < args.size(); i++) {
            std::string filePath = args[i];
            if (filePath.compare(filePath.size() - 4, 4, ".pbm") == 0 ||
                filePath.compare(filePath.size() - 4, 4, ".ppm") == 0 ||
                filePath.compare(filePath.size() - 4, 4, ".pgm") == 0) {
                paths.push_back(filePath);
            } else {
                std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
                return new ErrorCommand();
            }
        }

        return new LoadCommand(paths);
    }
    else if (args[0] == "add") {

        if (command.size() <= 4) {
            std::cout << "Invalid parameters: Expected a filepath" << std::endl;
            return new ErrorCommand();
        }

        std::string filePath = command.substr(4);
        if (command.compare(command.size() - 4, 4, ".pbm") == 0 ||
            command.compare(command.size() - 4, 4, ".ppm") == 0 ||
            command.compare(command.size() - 4, 4, ".pgm") == 0) {
            return new AddCommand(filePath);
        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
            return new ErrorCommand();
        }

    }
    else if (args[0] == "save") {
        if (args.size() == 1) {
            return new SaveCommand();
        } else {
            std::cout << "No parameters expected!" << std::endl;
            return new ErrorCommand();
        }
    }
    else if (args[0] == "close") {
        if (args.size() == 1) {
            return new CloseCommand();
        } else {
            std::cout << "No parameters expected!" << std::endl;
            return new ErrorCommand();
        }
    }
    else if (args[0] == "saveas") {
        std::cout << "Save as command\n";
        std::string filePath = args[1];
        if (filePath.compare(filePath.size() - 4, 4, ".pbm") == 0 ||
            filePath.compare(filePath.size() - 4, 4, ".ppm") == 0 ||
            filePath.compare(filePath.size() - 4, 4, ".pgm") == 0) {
            return new SaveAsCommand(filePath);
        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
            return new ErrorCommand();
        }
    }
    else if (args[0] == "help") {
        std::cout << "Help command\n";
        return new HelpCommand();
    }
    else if (args[0] == "exit") {
        return new ExitCommand();
    }
    else if (args[0] == "close") {
        return new CloseCommand();
    }
    else if (args[0]=="grayscale") {
        return new GrayscaleCommand();
    }
    else if (args[0]=="monochrome") {
        return new MonochromeCommand();
    }
    else if (args[0]=="negative") {
        return new NegativeCommand();
    }
    else if (args[0]=="rotate") {
        if(args[1] == "left" || args[1] == "right"){
            return new RotateCommand(args[1]);
        }else{
            std::cout<<"Invalid rotation: choose left or right";
            return new ErrorCommand();
        }
    }
    else if (args[0] == "undo") {
        return new UndoCommand();
    }
    else if (args[0] == "session" && args[1] == "info") {
        return new SessionInfoCommand();
    }
    else if (args[0] == "switch") {

        std::string sessionNumberString = args[1];
        try {
            int session = std::stoi(sessionNumberString);
            return new SwitchCommand(session);
        } catch (const std::exception &err) {
            std::cout << "Enter a valid session number" << std::endl;
            return new ErrorCommand();
        }

    }
    else if (args[0] == "collage") {

        if(args[1]!="horizontal" && args[1] != "vertical"){
            std::cout<<"Provide a valid orientation: horizontal / vertical"<<std::endl;
            return new ErrorCommand();
        }

        if (args[2].compare(args[2].size() - 4, 4, ".pbm") == 0 ||
            args[2].compare(args[2].size() - 4, 4, ".ppm") == 0 ||
            args[2].compare(args[2].size() - 4, 4, ".pgm") == 0 ||
            args[3].compare(args[3].size() - 4, 4, ".pbm") == 0 ||
            args[3].compare(args[3].size() - 4, 4, ".ppm") == 0 ||
            args[3].compare(args[3].size() - 4, 4, ".pgm") == 0) {

            if (args[4].compare(args[4].size() - 4, 4, ".pbm") == 0 ||
                args[4].compare(args[4].size() - 4, 4, ".ppm") == 0 ||
                args[4].compare(args[4].size() - 4, 4, ".pgm") == 0) {

                if (args[2].substr(args[2].size() - 4) != args[3].substr(args[3].size() - 4)
                    || args[2].substr(args[2].size() - 4) != args[4].substr(args[4].size() - 4)) {
                    std::cout << "All files should be the same type" << std::endl;
                    return new ErrorCommand();
                }

                std::cout<<"here2"<<std::endl;
                return new CollageCommand(args[1],args[2], args[3], args[4]);

            } else {
                std::cout << "Output file is not a PPM/PGM/PBM image." << std::endl;
                return new ErrorCommand();
            }

        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
            return new ErrorCommand();
        }

    }
    else {
        std::cout << "Invalid command\n";
        return new ErrorCommand();
    }
}
