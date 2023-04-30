

#include "ImagePPM.h"

#include <utility>
#include "Data/RGBPixelData.h"

ImagePPM::ImagePPM(std::string fileName)
        : Image(std::move(fileName), false, false, 1) {
}

ImagePPM::ImagePPM(const ImagePPM& other)
        : Image(other), pixels(other.pixels) {
}

ImagePPM* ImagePPM::copy() {
    return new ImagePPM(*this);
}

void ImagePPM::readFromFile(std::ifstream& file, bool isBinary) {
    readMagicNumberFromFile(file);
    privateRead(file);
    readMaxColorValueFromFile(file);

    if(isBinary){
        privateBinaryRead(file);
    }else{
        pixels.readFromFile(file);
    }

}

void ImagePPM::writeToFile(std::ofstream& file) {
    file<<"P3\n";
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

void ImagePPM::privateBinaryRead(std::ifstream &file) {
    int width = pixels.getCols();
    int height = pixels.getRows();
    unsigned char byte;
    file.read(reinterpret_cast<char *>(&byte), 1);
    for(int i = 0; i< height;i++){
        for(int j = 0; j <width; j++){
            file.read(reinterpret_cast<char *>(&byte), 1);
            int red = static_cast<int>(byte);
            file.read(reinterpret_cast<char *>(&byte), 1);
            int green = static_cast<int>(byte);
            file.read(reinterpret_cast<char *>(&byte), 1);
            int blue = static_cast<int>(byte);
            pixels.setElementAt(i,j,RGBPixelData(red,green,blue));
        }
    }
}
