

#include "ImagePPM.h"
#include "Data/RGBPixelData.h"
#include "Data/MatrixOperations.h"

ImagePPM::ImagePPM(std::string fileName)
        : Image(fileName, false, false, 1) {
}

ImagePPM::ImagePPM(const ImagePPM& other)
        : Image(other), m_pixels(other.m_pixels) {
}

ImagePPM* ImagePPM::copy() {
    return new ImagePPM(*this);
}

void ImagePPM::readFromFile(std::ifstream& file) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);
    m_pixels.readFromFile(file);
}

void ImagePPM::writeToFile(std::ofstream& file) {
    writeMagicNumberToFile(file);
    privateWrite(file);
    writeMaxColorValue(file);
    m_pixels.writeToFile(file);

    clearPreviousVersions();
}

void ImagePPM::rotate(std::string direction) {
    PixelMatrixOperations<RGBPixelData>::rotatePixels(direction, m_pixels);
}

void ImagePPM::toGrayscale() {
    for (int row = 0; row < m_pixels.getRows(); ++row)
        for (int col = 0; col < m_pixels.getCols(); ++col)
            m_pixels.getElementAt(row, col).toGrayscale();
}

void ImagePPM::toMonochrome() {
    for (int row = 0; row < m_pixels.getRows(); ++row)
        for (int col = 0; col < m_pixels.getCols(); ++col)
            m_pixels.getElementAt(row, col).normalize(maxColorValue);
}

void ImagePPM::toNegative() {
    PixelMatrixOperations<RGBPixelData>::negativeTransformation(m_pixels, maxColorValue);
}

void ImagePPM::privateRead(std::ifstream& file) {
    PixelMatrixOperations<RGBPixelData>::readAndResize(file, m_pixels);
}

void ImagePPM::privateWrite(std::ofstream& file) const {
    PixelMatrixOperations<RGBPixelData>::writeToFile(file, m_pixels);
}

void ImagePPM::copy(Image* image) {
    auto ppm = dynamic_cast<ImagePPM*>(image);

    if (ppm == nullptr) return; // incorrect image type

    m_pixels = ppm->m_pixels;

    Image::copy(image);
}
