

#include <cmath>
#include "ImagePGM.h"
#include "Data/MatrixOperations.h"

ImagePGM::ImagePGM(std::string fileName)
        : Image(fileName, true, false, 1) {
}

ImagePGM::ImagePGM(const ImagePGM& other)
        : Image(other), pixels(other.pixels) {
}

ImagePGM* ImagePGM::copy() {
    return new ImagePGM(*this);
}

void ImagePGM::readFromFile(std::ifstream& file) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);
    pixels.readFromFile(file);
}

void ImagePGM::writeToFile(std::ofstream& file) {
    writeMagicNumberToFile(file);
    privateWrite(file);
    writeMaxColorValue(file);
    pixels.writeToFile(file);

    clearPreviousVersions();
}

void ImagePGM::rotate(std::string direction) {
    PixelMatrixOperations<std::uint16_t>::rotatePixels(direction, pixels);
}

void ImagePGM::toGrayscale() {
    //no-op
}

void ImagePGM::toMonochrome() {
    for (int row = 0; row < pixels.getRows(); ++row)
        for (int col = 0; col < pixels.getCols(); ++col)
            pixels.getElementAt(row, col) = maxColorValue * std::round((double)pixels.getElementAt(row, col) / maxColorValue);
}

void ImagePGM::toNegative() {
    PixelMatrixOperations<std::uint16_t>::negativeTransformation(pixels, maxColorValue);
}

void ImagePGM::privateRead(std::ifstream& file) {
    PixelMatrixOperations<std::uint16_t>::readAndResize(file, pixels);
}

void ImagePGM::privateWrite(std::ofstream& file) const {
    PixelMatrixOperations<std::uint16_t>::writeToFile(file, pixels);
}

void ImagePGM::copy(Image* image) {
    ImagePGM* pgm = dynamic_cast<ImagePGM*>(image);

    if (pgm == nullptr) return; // incorrect image type

    pixels = pgm->pixels;

    Image::copy(image);
}

void ImagePGM::toCollage(Image *image2, const std::string &direction, const std::string &outPath) {
    std::string type = fileName.substr(fileName.size() - 4);
    auto image2pgm = dynamic_cast<ImagePGM *>(image2);

    int rows, cols;
    PixelMatrix<std::uint16_t> matrix;

    if (direction == "horizontal") {
        rows = std::max(pixels.getRows(), image2pgm->pixels.getRows());
        cols = pixels.getCols() + image2pgm->pixels.getCols();

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }
        for (int i = 0; i < image2pgm->pixels.getRows(); i++) {
            for (int j = 0; j < image2pgm->pixels.getCols(); j++) {
                matrix.setElementAt(i, j + pixels.getCols(), image2pgm->pixels.getElement(i, j));
            }
        }

    } else {
        //vertical
        rows = pixels.getRows() + image2pgm->pixels.getRows();
        cols = std::max(pixels.getCols(), image2pgm->pixels.getCols());

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }

        for (int i = 0; i < image2pgm->pixels.getRows(); i++) {
            for (int j = 0; j < cols; j++) {
                matrix.setElementAt(i + pixels.getRows(), j, image2pgm->pixels.getElement(i, j));
            }
        }
    }

    ImagePGM output(outPath);
    output.magicNumber = magicNumber;
    output.pixels = matrix;

    std::ofstream file(outPath);
    output.writeToFile(file);
}
