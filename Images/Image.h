

#ifndef BITMAPGRAPHICS_IMAGE_H
#define BITMAPGRAPHICS_IMAGE_H

#include <string>

class Image {
public:
    std::string getFileName() const;

    bool isGrayscale() const;
    bool isMonochrome() const;

    virtual Image* copy() = 0;

    virtual void readFromFile(std::ifstream& file, bool isBinary) = 0;
    virtual void writeToFile(std::ofstream& file) = 0;

    virtual void rotate(std::string direction) = 0;
    virtual void toGrayscale() = 0;
    virtual void toMonochrome() = 0;
    virtual void toNegative() = 0;
    virtual void toCollage(Image* image2, const std::string& direction, const std::string& outPath) = 0;

    virtual void undo();

    void removeUnsavedChanges();

    virtual ~Image() = default;

protected:
    Image(std::string filePath, const bool grayscale = false, const bool monochrome = false, const std::uint16_t maxColorValue = 0);
    Image(const Image& other);

    std::string fileName;
    int magicNumber;
    std::uint16_t maxColorValue;
    bool grayscale;
    bool monochrome;
    Image* previousVersion;

    void readMagicNumberFromFile(std::ifstream& file);
    void readMaxColorValueFromFile(std::ifstream& file);
    virtual void privateRead(std::ifstream& file) = 0;
    virtual void privateBinaryRead(std::ifstream& file) = 0;

    void writeMagicNumberToFile(std::ofstream& file) const;
    void writeMaxColorValue(std::ofstream& file) const;
    virtual void privateWrite(std::ofstream& file) const = 0;

    void clearPreviousVersions();

    virtual void copy(Image* image);

};


#endif //BITMAPGRAPHICS_IMAGE_H
