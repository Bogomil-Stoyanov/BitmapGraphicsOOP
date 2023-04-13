#include "CommandDispatcher.h"
#include "CommandTypes/ErrorCommand.h"
#include "CommandTypes/ExitCommand.h"
#include "CommandTypes/Command.h"
#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <sstream>

Command* CommandDispatcher::analyzeCommand(std::string rawCommand) {
    std::string command = std::move(rawCommand);
    std::transform(command.begin(), command.end(), command.begin(), [](unsigned char c) { return std::tolower(c); });

    if (command.compare(0, 4, "load") == 0) {

        std::cout << "Load command\n";
        if (command.size() <= 5) {
            std::cout << "Invalid parameters: Expected a filepath" << std::endl;
            return new ErrorCommand();
        }
        std::string filePath = command.substr(5);
        if (command.compare(command.size() - 4, 4, ".pbm") == 0 ||
            command.compare(command.size() - 4, 4, ".ppm") == 0 ||
            command.compare(command.size() - 4, 4, ".pgm") == 0) {
            std::cout << "path is " << filePath << std::endl;
        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
        }

    } else if (command.compare(0, 3, "add") == 0) {

        std::cout << "Add command\n";

        if (command.size() <= 4) {
            std::cout << "Invalid parameters: Expected a filepath" << std::endl;
            return new ErrorCommand();
        }

        std::string filePath = command.substr(4);
        if (command.compare(command.size() - 4, 4, ".pbm") == 0 ||
            command.compare(command.size() - 4, 4, ".ppm") == 0 ||
            command.compare(command.size() - 4, 4, ".pgm") == 0) {
            std::cout << "path is " << filePath << std::endl;
        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
        }

    } else if (command.compare(0, 4, "save") == 0) {
        std::cout << "Save command\n";
    } else if (command.compare(0, 5, "close") == 0) {
        std::cout << "Close command\n";
    } else if (command.compare(0, 7, "save as") == 0) {
        std::cout << "Save as command\n";
    } else if (command.compare(0, 4, "help") == 0) {
        std::cout << "Help command\n";
    } else if (command.compare(0, 4, "exit") == 0) {
        std::cout << "Exit command\n";
        return new ExitCommand();
    } else if (command.compare(0, 9, "grayscale") == 0) {
        std::cout << "Grayscale command\n";
    } else if (command.compare(0, 10, "monochrome") == 0) {
        std::cout << "Monochrome command\n";
    } else if (command.compare(0, 8, "negative") == 0) {
        std::cout << "Negative command\n";
    } else if (command.compare(0, 6, "rotate") == 0) {
        std::cout << "Rotate command\n";
    } else if (command.compare(0, 4, "undo") == 0) {
        std::cout << "Undo command\n";
    } else if (command.compare(0, 12, "session info") == 0) {
        std::cout << "Session info command\n";
    } else if (command.compare(0, 6, "switch") == 0) {
        std::cout << "Switch command\n";

        std::string sessionNumberString = command.substr(7);
        std::cout << sessionNumberString << std::endl;
        try {
            int session = std::stoi(sessionNumberString);
        } catch (const std::exception &err) {
            std::cout << "Enter a valid number" << std::endl;
        }

    } else if (command.compare(0, 7, "collage") == 0) {
        std::cout << "Collage command\n";

        std::vector<std::string> args;
        std::istringstream iss(command);
        std::string word;
        while (iss >> word) {
            args.push_back(word);
        }

        if (args[1] == "horizontal") {
            std::cout << "horizontal" << std::endl;
        } else if (args[1] == "vertical") {
            std::cout << "vertical" << std::endl;
        } else {
            std::cout << "error" << std::endl;
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

                if(args[2].substr(args[2].size() - 4) != args[3].substr(args[3].size() - 4)
                || args[2].substr(args[2].size() - 4) != args[4].substr(args[4].size() - 4)){
                    std::cout<<"All files should be the same type"<<std::endl;
                }

            } else {
                std::cout << "Output file is not a PPM/PGM/PBM image." << std::endl;
            }

        } else {
            std::cout << "File is not a PPM/PGM/PBM image." << std::endl;
        }

    } else {
        std::cout << "Invalid command\n";
    }

    return new ErrorCommand();

}
