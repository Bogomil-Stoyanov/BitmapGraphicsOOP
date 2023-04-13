
#include <fstream>
#include "Image.h"


void Image::undo() {
    if (previousVersion == nullptr) return; // undo not available

    copy(previousVersion);
}

void Image::removeUnsavedChanges() {
    clearPreviousVersions();
}

Image *Image::toCollage(Image *image1, Image *image2, const std::string& direction, const std::string& outImageLocation) {
    return nullptr;
}

Image::Image(const Image &other)
        : m_fileName(other.m_fileName), magicNumber(other.magicNumber),
          maxColorValue(other.maxColorValue), grayscale(other.grayscale),
          monochrome(isMonochrome()), previousVersion(other.previousVersion) {
}

std::string Image::getFileName() const {
    return m_fileName;
}

bool Image::isGrayscale() const {
    return grayscale;
}

bool Image::isMonochrome() const {
    return monochrome;
}

void Image::readMagicNumberFromFile(std::ifstream &file) {
    file.ignore();
    file >> magicNumber;
}

void Image::readMaxColorValueFromFile(std::ifstream &file) {
    file >> maxColorValue;
}

void Image::writeMagicNumberToFile(std::ofstream &file) const {
    file << 'P' << magicNumber << '\n';
}

void Image::writeMaxColorValue(std::ofstream &file) const {
    file << maxColorValue << '\n';
}

void Image::clearPreviousVersions() {
    if (previousVersion == nullptr) return;

    previousVersion->clearPreviousVersions();

    delete previousVersion;
}

void Image::copy(Image *image) {
    m_fileName = image->m_fileName;
    magicNumber = image->magicNumber;
    maxColorValue = image->maxColorValue;
    grayscale = image->grayscale;
    monochrome = image->monochrome;
    previousVersion = image->previousVersion;

    delete image;
}

Image::Image(std::string filePath, const bool grayscale, const bool monochrome, const std::uint16_t maxColorValue) : m_fileName(std::move(
        filePath)), grayscale(grayscale),monochrome(monochrome),maxColorValue(maxColorValue),previousVersion(nullptr) {
}
