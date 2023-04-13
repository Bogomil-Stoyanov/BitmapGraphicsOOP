
#include "ImagePBM.h"

#include <utility>
#include "Data/MatrixOperations.h"


ImagePBM::ImagePBM(std::string fileName)
        : Image(std::move(fileName), false, true, MAX_COLOR_VALUE) {
}

ImagePBM::ImagePBM(const ImagePBM &other)
        : Image(other), pixels(other.pixels) {
}

ImagePBM *ImagePBM::copy() {
    return new ImagePBM(*this);
}

void ImagePBM::readFromFile(std::ifstream &file) {
    std::cout<<"HERE";
    readMagicNumberFromFile(file);
    privateRead(file);
    pixels.readFromFile(file);
    std::cout<<"end";
}

void ImagePBM::writeToFile(std::ofstream &file) {
    writeMagicNumberToFile(file);
    privateWrite(file);
    pixels.writeToFile(file);

    std::cout<<"SAVING"<<std::endl;

    clearPreviousVersions();
}

void ImagePBM::rotate(std::string direction) {
    //m_previousVersion = clone(); // TODO: Do something about the previousVersions

    PixelMatrixOperations<std::uint16_t>::rotatePixels(direction, pixels);
}

void ImagePBM::toGrayscale() {
    //no-op
}

void ImagePBM::toMonochrome() {
    //no-op
}

void ImagePBM::toNegative() {
    PixelMatrixOperations<std::uint16_t>::negativeTransformation(pixels, 1);
}

void ImagePBM::privateRead(std::ifstream &file) {
    PixelMatrixOperations<std::uint16_t>::readAndResize(file, pixels);
}

void ImagePBM::privateWrite(std::ofstream &file) const {
    PixelMatrixOperations<std::uint16_t>::writeToFile(file, pixels);
}

void ImagePBM::copy(Image *image) {
    auto pbm = dynamic_cast<ImagePBM *>(image);

    if (pbm == nullptr) return; //incorrect image type

    pixels = pbm->pixels;

    Image::copy(image);
}