

#include "ImagePPM.h"
#include "Data/RGBPixelData.h"

ImagePPM::ImagePPM(std::string fileName)
        : Image(fileName, false, false, 1) {
}

ImagePPM::ImagePPM(const ImagePPM& other)
        : Image(other), pixels(other.pixels) {
}

ImagePPM* ImagePPM::copy() {
    return new ImagePPM(*this);
}

void ImagePPM::readFromFile(std::ifstream& file) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);
    pixels.readFromFile(file);
}

void ImagePPM::writeToFile(std::ofstream& file) {
    writeMagicNumberToFile(file);
    file << pixels.getCols() << ' ' << pixels.getRows() << '\n';
    writeMaxColorValue(file);
    privateWrite(file);

    clearPreviousVersions();
}

void ImagePPM::toCollage(Image *image2, const std::string &direction, const std::string &outPath) {
    std::string type = fileName.substr(fileName.size() - 4);
    auto image2ppm = dynamic_cast<ImagePPM *>(image2);

    int rows, cols;
    PixelMatrix<RGBPixelData> matrix;

    if (direction == "horizontal") {
        rows = std::max(pixels.getRows(), image2ppm->pixels.getRows());
        cols = pixels.getCols() + image2ppm->pixels.getCols();

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }
        for (int i = 0; i < image2ppm->pixels.getRows(); i++) {
            for (int j = 0; j < image2ppm->pixels.getCols(); j++) {
                matrix.setElementAt(i, j + pixels.getCols(), image2ppm->pixels.getElement(i, j));
            }
        }

    } else {
        //vertical
        rows = pixels.getRows() + image2ppm->pixels.getRows();
        cols = std::max(pixels.getCols(), image2ppm->pixels.getCols());

        matrix.fillPixelMatrixWithZeroes(rows, cols);

        for (int i = 0; i < pixels.getRows(); i++) {
            for (int j = 0; j < pixels.getCols(); j++) {
                matrix.setElementAt(i, j, pixels.getElement(i, j));
            }
        }

        for (int i = 0; i < image2ppm->pixels.getRows(); i++) {
            for (int j = 0; j < cols; j++) {
                matrix.setElementAt(i + pixels.getRows(), j, image2ppm->pixels.getElement(i, j));
            }
        }
    }

    ImagePPM output(outPath);
    output.magicNumber = magicNumber;
    output.pixels = matrix;

    std::ofstream file(outPath);
    output.writeToFile(file);
}

void ImagePPM::rotate(std::string direction) {
    pixels.rotatePixels(direction);
}

void ImagePPM::toGrayscale() {
    for (int row = 0; row < pixels.getRows(); ++row)
        for (int col = 0; col < pixels.getCols(); ++col)
            pixels.getElementAt(row, col).toGrayscale();
}

void ImagePPM::toMonochrome() {
    for (int row = 0; row < pixels.getRows(); ++row)
        for (int col = 0; col < pixels.getCols(); ++col)
            pixels.getElementAt(row, col).normalize(maxColorValue);
}

void ImagePPM::toNegative() {
    pixels.negativeTransformation(maxColorValue);
}

void ImagePPM::privateRead(std::ifstream& file) {
    pixels.readAndResize(file);
}

void ImagePPM::privateWrite(std::ofstream& file) const {
    pixels.writeToFile(file);
}

void ImagePPM::copy(Image* image) {
    auto ppm = dynamic_cast<ImagePPM*>(image);

    if (ppm == nullptr) return; // incorrect image type

    pixels = ppm->pixels;

    Image::copy(image);
}
