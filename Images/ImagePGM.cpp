

#include <cmath>
#include "ImagePGM.h"
#include "Data/MatrixOperations.h"

ImagePGM::ImagePGM(std::string fileName)
        : Image(fileName, true, false, 1) {
}

ImagePGM::ImagePGM(const ImagePGM& other)
        : Image(other), m_pixels(other.m_pixels) {
}

ImagePGM* ImagePGM::copy() {
    return new ImagePGM(*this);
}

void ImagePGM::readFromFile(std::ifstream& file) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);
    m_pixels.readFromFile(file);
}

void ImagePGM::writeToFile(std::ofstream& file) {
    writeMagicNumberToFile(file);
    privateWrite(file);
    writeMaxColorValue(file);
    m_pixels.writeToFile(file);

    clearPreviousVersions();
}

void ImagePGM::rotate(std::string direction) {
    PixelMatrixOperations<std::uint16_t>::rotatePixels(direction, m_pixels);
}

void ImagePGM::toGrayscale() {
    //no-op
}

void ImagePGM::toMonochrome() {
    for (int row = 0; row < m_pixels.getRows(); ++row)
        for (int col = 0; col < m_pixels.getCols(); ++col)
            m_pixels.getElementAt(row, col) = maxColorValue * std::round((double)m_pixels.getElementAt(row, col) / maxColorValue);
}

void ImagePGM::toNegative() {
    PixelMatrixOperations<std::uint16_t>::negativeTransformation(m_pixels, maxColorValue);
}

void ImagePGM::privateRead(std::ifstream& file) {
    PixelMatrixOperations<std::uint16_t>::readAndResize(file, m_pixels);
}

void ImagePGM::privateWrite(std::ofstream& file) const {
    PixelMatrixOperations<std::uint16_t>::writeToFile(file, m_pixels);
}

void ImagePGM::copy(Image* image) {
    ImagePGM* pgm = dynamic_cast<ImagePGM*>(image);

    if (pgm == nullptr) return; // incorrect image type

    m_pixels = pgm->m_pixels;

    Image::copy(image);
}
