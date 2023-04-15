
#include "ImagePBM.h"

#include <algorithm>
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
    readMagicNumberFromFile(file);
    privateRead(file);
    pixels.readFromFile(file);
}

void ImagePBM::writeToFile(std::ofstream &file) {
    writeMagicNumberToFile(file);
    privateWrite(file);
    pixels.writeToFile(file);
    clearPreviousVersions();
}

void ImagePBM::toCollage(Image *image2, const std::string &direction, const std::string &outPath) {
    std::string type = fileName.substr(fileName.size() - 4);
    auto image2pbm = dynamic_cast<ImagePBM *>(image2);

    int rows, cols;
    PixelMatrix<std::uint16_t> matrix;

    if (direction == "horizontal") {
        rows = std::max(pixels.getRows(), image2pbm->pixels.getRows());
        cols = pixels.getCols() + image2pbm->pixels.getCols();

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }
        for (int i = 0; i < image2pbm->pixels.getRows(); i++) {
            for (int j = 0; j < image2pbm->pixels.getCols(); j++) {
                matrix.setElementAt(i, j + pixels.getCols(), image2pbm->pixels.getElement(i, j));
            }
        }

    } else {
        //vertical
        rows = pixels.getRows() + image2pbm->pixels.getRows();
        cols = std::max(pixels.getCols(), image2pbm->pixels.getCols());

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }

        for (int i = 0; i < image2pbm->pixels.getRows(); i++) {
            for (int j = 0; j < cols; j++) {
                matrix.setElementAt(i + pixels.getRows(), j, image2pbm->pixels.getElement(i, j));
            }
        }
    }

    ImagePBM output(outPath);
    output.magicNumber = magicNumber;
    output.pixels = matrix;

    std::ofstream file(outPath);
    output.writeToFile(file);
}

void ImagePBM::rotate(std::string direction) {
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