#ifndef BITMAPGRAPHICS_SESSION_H
#define BITMAPGRAPHICS_SESSION_H

#include <string>
#include <vector>
#include "../../Images/Image.h"

class Session {
private:
    int sessionId;
    std::vector<std::string> unsavedChanges;
    std::vector<Image*> images;
    static void saveImage(Image* image, const std::string& filePath);

public:
    explicit Session();
    static int countOfSessions;
    int getId() const;
    void addImage(Image* image);
    void grayscale();
    void monochrome();
    void rotate(const std::string& direction);
    void negative();
    void collage(std::string path1, std::string path2, std::string outputPath, std::string direction);
    void save();
    void saveAs(const std::string& filePath);
    void undo();
    void close();
    void info() const;
    bool hasFile(const std::string& filepath) const;
    bool hasUnsavedChanges() const;
};


#endif //BITMAPGRAPHICS_SESSION_H
