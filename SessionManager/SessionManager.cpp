

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

Session &SessionManager::getActiveSession() {
    return sessions[currentActiveSessionId - 1];
}

void SessionManager::execute(Command *command) {
    if (dynamic_cast<AddCommand *>(command) != nullptr) {
        auto addCommand = dynamic_cast<AddCommand *>(command);
        add(addCommand->getPath());
    } else if (dynamic_cast<CloseCommand *>(command) != nullptr) {
        auto closeCommand = dynamic_cast<CloseCommand *>(command);
        std::cout << "close command" << std::endl;
        close();
    } else if (dynamic_cast<CollageCommand *>(command) != nullptr) {
        auto collageCommand = dynamic_cast<CollageCommand *>(command);
        std::cout << "collage command " << collageCommand->getPath1() << " " << collageCommand->getPath2() << " "
                  << collageCommand->getOutPath() << " " << collageCommand->getDirection() << std::endl;
        collage(collageCommand->getDirection(), collageCommand->getPath1(), collageCommand->getPath2(),
                collageCommand->getOutPath());
    } else if (dynamic_cast<GrayscaleCommand *>(command) != nullptr) {
        auto grayscaleCommand = dynamic_cast<GrayscaleCommand *>(command);
        std::cout << "grayscale command" << std::endl;
        grayscale();
    } else if (dynamic_cast<LoadCommand *>(command) != nullptr) {
        auto loadCommand = dynamic_cast<LoadCommand *>(command);
        load(loadCommand->getFilePaths());
    } else if (dynamic_cast<MonochromeCommand *>(command) != nullptr) {
        auto monochromeCommand = dynamic_cast<MonochromeCommand *>(command);
        std::cout << "monochrome command" << std::endl;
        monochrome();
    } else if (dynamic_cast<NegativeCommand *>(command) != nullptr) {
        auto negativeCommand = dynamic_cast<NegativeCommand *>(command);
        std::cout << "negative command " << std::endl;
        negative();
    } else if (dynamic_cast<RotateCommand *>(command) != nullptr) {
        auto rotateCommand = dynamic_cast<RotateCommand *>(command);
        std::cout << "rotate command " << rotateCommand->getRotation() << std::endl;
        rotate(rotateCommand->getRotation());
    } else if (dynamic_cast<SaveAsCommand *>(command) != nullptr) {
        auto saveasCommand = dynamic_cast<SaveAsCommand *>(command);
        std::cout << "saveAs command " << saveasCommand->getPath() << std::endl;
        saveAs(saveasCommand->getPath());
    } else if (dynamic_cast<SaveCommand *>(command) != nullptr) {
        auto saveCommand = dynamic_cast<SaveCommand *>(command);
        std::cout << "save command" << std::endl;
        save();
    } else if (dynamic_cast<SessionInfoCommand *>(command) != nullptr) {
        auto sessionInfoCommand = dynamic_cast<SessionInfoCommand *>(command);
        std::cout << "session info command" << std::endl;
        sessionInfo();
    } else if (dynamic_cast<SwitchCommand *>(command) != nullptr) {
        auto switchCommand = dynamic_cast<SwitchCommand *>(command);
        std::cout << "switch command " << switchCommand->getSession() << std::endl;
        switchSession(switchCommand->getSession());
    } else if (dynamic_cast<UndoCommand *>(command) != nullptr) {
        auto undoCommand = dynamic_cast<UndoCommand *>(command);
        std::cout << "undo command" << std::endl;
        undo();
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
        std::ifstream file;
        file.open(path);

        if (!file.is_open()) {
            std::cout << "File " + path << " was not opened!" << std::endl;
            file.close();
            continue;
        }
        auto image = ImageCreator::createImage(path);
        image->readFromFile(file);
        getActiveSession().addImage(image);
        file.close();
    }
}

void SessionManager::add(const std::string& filePath) {
    if (isFileInUse(filePath)) {
        std::cout << "File: " << filePath << " is already in use" << std::endl;
        return;
    }

    std::ifstream file;
    file.open(filePath);

    if (!file.is_open()) {
        std::cout << "File " + filePath << " was not opened!" << std::endl;
        file.close();
        return;
    }

    auto image = ImageCreator::createImage(filePath);
    image->readFromFile(file);
    getActiveSession().addImage(image);
    file.close();
}

void SessionManager::close() {
    if(Session::countOfSessions==0){
        std::cout<<"No active sessions"<<std::endl;
        return;
    }
    sessions.erase(sessions.begin() + (currentActiveSessionId-1));
    if(sessions.empty()){
        currentActiveSessionId = 0;
        Session::countOfSessions = 0;
    }else {
        currentActiveSessionId = 1;
    }

}

void SessionManager::collage(std::string direction, std::string path1, std::string path2, std::string outPath) {
    //TODO
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
    if(sessions.empty()){
        std::cout<<"No sessions"<<std::endl;
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
