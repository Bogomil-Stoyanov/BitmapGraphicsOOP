

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
#include "../Images/ImageCreator.h"
#include <iostream>
#include <fstream>
#include <utility>
#include <exception>

Session &SessionManager::getActiveSession() {
    if (currentActiveSessionId == -1) throw std::runtime_error("No active session");
    return sessions[currentActiveSessionId - 1];
}

void SessionManager::execute(Command *command) {
    switch (command->getCommandType()) {
        case CommandType::ADD: {
            auto addCommand = dynamic_cast<AddCommand *>(command);
            add(addCommand->getPath());
            break;
        }
        case CommandType::CLOSE: {
            auto closeCommand = dynamic_cast<CloseCommand *>(command);
            std::cout << "close command" << std::endl;
            close();
            break;
        }
        case CommandType::COLLAGE: {
            auto collageCommand = dynamic_cast<CollageCommand *>(command);
            std::cout << "collage command " << collageCommand->getPath1() << " " << collageCommand->getPath2() << " "
                      << collageCommand->getOutPath() << " " << collageCommand->getDirection() << std::endl;
            collage(collageCommand->getDirection(), collageCommand->getPath1(), collageCommand->getPath2(),
                    collageCommand->getOutPath());
            break;
        }
        case CommandType::GRAYSCALE: {
            auto grayscaleCommand = dynamic_cast<GrayscaleCommand *>(command);
            std::cout << "grayscale command" << std::endl;
            grayscale();
            break;
        }
        case CommandType::HELP: {
            printHelp();
            break;
        }
        case CommandType::LOAD: {
            auto loadCommand = dynamic_cast<LoadCommand *>(command);
            load(loadCommand->getFilePaths());
            break;
        }
        case CommandType::MONOCHROME: {
            auto monochromeCommand = dynamic_cast<MonochromeCommand *>(command);
            std::cout << "monochrome command" << std::endl;
            monochrome();
            break;
        }
        case CommandType::NEGATIVE: {
            auto negativeCommand = dynamic_cast<NegativeCommand *>(command);
            std::cout << "negative command " << std::endl;
            negative();
            break;
        }
        case CommandType::ROTATE: {
            auto rotateCommand = dynamic_cast<RotateCommand *>(command);
            std::cout << "rotate command " << rotateCommand->getRotation() << std::endl;
            rotate(rotateCommand->getRotation());
            break;
        }
        case CommandType::SAVE_AS: {
            auto saveasCommand = dynamic_cast<SaveAsCommand *>(command);
            std::cout << "saveAs command " << saveasCommand->getPath() << std::endl;
            saveAs(saveasCommand->getPath());
            break;
        }
        case CommandType::SAVE: {
            auto saveCommand = dynamic_cast<SaveCommand *>(command);
            std::cout << "save command" << std::endl;
            save();
            break;
        }
        case CommandType::SESSION_INFO: {
            auto sessionInfoCommand = dynamic_cast<SessionInfoCommand *>(command);
            std::cout << "session info command" << std::endl;
            sessionInfo();
            break;
        }
        case CommandType::SWITCH: {
            auto switchCommand = dynamic_cast<SwitchCommand *>(command);
            std::cout << "switch command " << switchCommand->getSession() << std::endl;
            switchSession(switchCommand->getSession());
            break;
        }
        case CommandType::UNDO: {
            auto undoCommand = dynamic_cast<UndoCommand *>(command);
            std::cout << "undo command" << std::endl;
            undo();
            break;
        }
        default: {
            break;
        }
    }
}

void SessionManager::load(std::vector<std::string> paths) {
    std::vector<std::string> unusedPaths;
    for (const auto &path: paths) {
        if (isFileInUse(path)) {
            std::cout << "File: " << path << " is already in use" << std::endl;
        } else {
            unusedPaths.push_back(path);
        }
    }
    if (unusedPaths.empty()) {
        std::cout << "No session created as all provided files are currently in use!" << std::endl;
        return;
    }
    Session newSession;
    sessions.push_back(newSession);
    currentActiveSessionId = newSession.getId();
    for (const auto &path: unusedPaths) {
        bool isInBinary = isFileBinary(path);


        std::ifstream file;

        if(isInBinary){
            file = std::ifstream (path, std::ios::binary);
        }else{
            file = std::ifstream (path);
        }


        if (!file.is_open()) {
            std::cout << "File " + path << " was not opened!" << std::endl;
            file.close();
            continue;
        }
        auto image = ImageCreator::createImage(path);
        image->readFromFile(file, isInBinary);
        getActiveSession().addImage(image);
        file.close();
    }
}

void SessionManager::add(const std::string &filePath) {
    if (isFileInUse(filePath)) {
        std::cout << "File: " << filePath << " is already in use" << std::endl;
        return;
    }

    bool isInBinary = isFileBinary(filePath);


    std::ifstream file;

    if(isInBinary){
        file = std::ifstream (filePath, std::ios::binary);
    }else{
        file = std::ifstream (filePath);
    }

    if (!file.is_open()) {
        std::cout << "File " + filePath << " was not opened!" << std::endl;
        file.close();
        return;
    }

    auto image = ImageCreator::createImage(filePath);
    image->readFromFile(file, isInBinary);
    getActiveSession().addImage(image);
    file.close();
}

void SessionManager::close() {
    if (Session::countOfSessions == 0) {
        std::cout << "No active sessions" << std::endl;
        return;
    }
    if (getActiveSession().hasUnsavedChanges()) {
        std::string input = "EMPTY_STRING";
        std::cout << "You have unsaved changes? Do you want to save them before exiting? ( Y | N ):" << std::endl;
        input = "EMPTY_STRING";
        do {
            if (input != "EMPTY_STRING") {
                std::cout << "Y | N:" << std::endl;
            }
            std::getline(std::cin, input);
        } while (input != "Y" && input != "N");

        if (input == "Y") {
            save();
        }
    } else {
        std::cout << "NO unsaved changes" << std::endl;
    }
    sessions.erase(sessions.begin() + (currentActiveSessionId - 1));
    if (sessions.empty()) {
        currentActiveSessionId = 0;
        Session::countOfSessions = 0;
    } else {
        currentActiveSessionId = 1;
    }
}

void SessionManager::collage(std::string direction, std::string path1, std::string path2, std::string outPath) {
    getActiveSession().collage(std::move(path1), std::move(path2), std::move(outPath), std::move(direction));
}

void SessionManager::grayscale() {
    getActiveSession().grayscale();
}

void SessionManager::monochrome() {
    getActiveSession().monochrome();
}

void SessionManager::negative() {
    getActiveSession().negative();
}

void SessionManager::rotate(std::string rotation) {
    getActiveSession().rotate(rotation);
}

void SessionManager::saveAs(std::string filePath) {
    getActiveSession().saveAs(filePath);
}

void SessionManager::save() {
    getActiveSession().save();
}

void SessionManager::sessionInfo() {
    if (sessions.empty()) {
        std::cout << "No sessions" << std::endl;
        return;
    }
    getActiveSession().info();
}

void SessionManager::switchSession(int sessionId) {
    if (sessions.empty()) {
        std::cout << "No active sessions" << std::endl;
    }
    if (sessionId >= 1 && sessionId <= sessions.size()) {
        currentActiveSessionId = sessionId;
        sessionInfo();
    } else {
        std::cout << "Invalid session" << std::endl;
    }
}

void SessionManager::undo() {
    getActiveSession().undo();
}

bool SessionManager::isFileInUse(const std::string &filePath) {
    for (const auto &session: sessions) {
        if (session.hasFile(filePath)) return true;
    }
    return false;
}

void SessionManager::printHelp() {
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "Welcome to BitmapGraphics!" << std::endl;
    std::cout << "Here is a list of all available commands:" << std::endl;
    std::cout << "load <file> - opens <file> and creates a new session" << std::endl;
    std::cout << "add <file> - adds an image to the current session" << std::endl;
    std::cout << "save - saves all files in the current session" << std::endl;
    std::cout << "saveas <file> - saves the first file in the current session in <file>" << std::endl;
    std::cout << "close - closes the active session" << std::endl;
    std::cout << "help - gives a list of all available commands" << std::endl;
    std::cout << "exit - exits the program" << std::endl;
    std::cout << "session info - prints information about the current session" << std::endl;
    std::cout << "switch <sessionId> - changes the active session" << std::endl;
    std::cout << "grayscale - applies grayscale effect to all applicable images in the current session" << std::endl;
    std::cout << "monochrome - applies monochrome effect to all applicable images in the current session" << std::endl;
    std::cout << "negative - applies negative effect to all applicable images in the current session" << std::endl;
    std::cout
            << "rotate <left|right> - rotates every image in current session in a direction (90 degrees) - left or right"
            << std::endl;
    std::cout << "undo - undos the last command" << std::endl;
    std::cout
            << "collage <horizontal|vertical> <image1> <image2> <outimage> -> creates a collage of <image1> and <image2> in <outimage>. image1 and image2 need to be present in the current session"
            << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
}

bool SessionManager::hasUnsavedChanges() {
    for (const Session &session: sessions) {
        if (session.hasUnsavedChanges()) {
            return true;
        }
    }
    return false;
}

void SessionManager::saveAllSessions() {
    for (Session &session: sessions) {
        session.save();
    }
}

bool SessionManager::isFileBinary(const std::string& filepath) {
    std::ifstream file(filepath);
    file.ignore();
    int magicNumber;
    file >> magicNumber;
    file.close();
    if (magicNumber == 4 || magicNumber == 5 || magicNumber == 6) return true;
    return false;
}
