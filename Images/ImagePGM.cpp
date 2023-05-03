

#include <cmath>
#include "ImagePGM.h"

ImagePGM::ImagePGM(std::string fileName)
        : Image(fileName, true, false, 1) {
}

ImagePGM::ImagePGM(const ImagePGM &other)
        : Image(other), pixels(other.pixels) {
}

ImagePGM *ImagePGM::copy() {
    return new ImagePGM(*this);
}

void ImagePGM::readFromFile(std::ifstream &file, bool isBinary) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);

    if (isBinary) {
        privateBinaryRead(file);
    } else {
        pixels.readFromFile(file);
    }
}

void ImagePGM::writeToFile(std::ofstream &file) {
    file << "P2\n";
    file << pixels.getCols() << ' ' << pixels.getRows() << '\n';
    writeMaxColorValue(file);
    pixels.writeToFile(file);
    clearPreviousVersions();
}

void ImagePGM::rotate(std::string direction) {
    pixels.rotatePixels(direction);
}

void ImagePGM::toGrayscale() {
    //no-op
}

void ImagePGM::toMonochrome() {
    monochrome = true;
    for (int row = 0; row < pixels.getRows(); ++row)
        for (int col = 0; col < pixels.getCols(); ++col)
            pixels.getElementAt(row, col) =
                    maxColorValue * std::round((double) pixels.getElementAt(row, col) / maxColorValue);
}

void ImagePGM::toNegative() {
    pixels.negativeTransformation(maxColorValue);
}

void ImagePGM::privateRead(std::ifstream &file) {
    pixels.readAndResize(file);
}

void ImagePGM::privateWrite(std::ofstream &file) const {
    pixels.writeToFile(file);
}

void ImagePGM::copy(Image *image) {
    auto *pgm = dynamic_cast<ImagePGM *>(image);

    if (pgm == nullptr) return; // incorrect image type

    pixels = pgm->pixels;

    Image::copy(image);
}

Image *ImagePGM::toCollage(Image *image2, const std::string &direction, const std::string &outPath) {
    std::string type = fileName.substr(fileName.size() - 4);
    auto image2pgm = dynamic_cast<ImagePGM *>(image2);

    int rows, cols;
    PixelMatrix<unsigned short> matrix;

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

    auto *output = new ImagePGM(outPath);
    output->magicNumber = magicNumber;
    output->pixels = matrix;

    std::ofstream file(outPath);
    output->writeToFile(file);
    file.close();

    return output;
}

void ImagePGM::privateBinaryRead(std::ifstream &file) {
    int width = pixels.getCols();
    int height = pixels.getRows();
    unsigned char byte;
    file.read(reinterpret_cast<char *>(&byte), 1);
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            file.read(reinterpret_cast<char *>(&byte), 1);
            pixels.setElementAt(i, j, static_cast<int>(byte));
        }
    }
    std::cout << std::endl;
}

ImagePGM::~ImagePGM() {
    clearPreviousVersions();
}
