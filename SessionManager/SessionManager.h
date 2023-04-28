#ifndef BITMAPGRAPHICS_SESSIONMANAGER_H
#define BITMAPGRAPHICS_SESSIONMANAGER_H

#include "../Commands/CommandTypes/Command.h"
#include "Session/Session.h"
#include <vector>


class SessionManager {

private:
    std::vector<Session> sessions;
    int currentActiveSessionId;

    Session& getActiveSession();
    void add(const std::string& filePath);
    void close();
    void collage(std::string direction, std::string path1, std::string path2, std::string outPath);
    void grayscale();
    void load(std::vector<std::string> paths);
    void monochrome();
    void negative();
    void rotate(std::string rotation);
    void saveAs(std::string filePath);
    void save();
    void sessionInfo();
    void switchSession(int sessionId);
    void undo();
    bool isFileInUse(const std::string& filePath);
    static void printHelp();

public:
    void execute(Command* command);
};


#endif //BITMAPGRAPHICS_SESSIONMANAGER_H
