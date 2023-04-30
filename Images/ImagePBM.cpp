
#include "ImagePBM.h"

#include <algorithm>
#include <utility>


ImagePBM::ImagePBM(std::string fileName)
        : Image(std::move(fileName), false, true, MAX_COLOR_VALUE) {
}

ImagePBM::ImagePBM(const ImagePBM &other)
        : Image(other), pixels(other.pixels) {
}

ImagePBM *ImagePBM::copy() {
    return new ImagePBM(*this);
}

void ImagePBM::readFromFile(std::ifstream &file, bool isBinary) {


    if (isBinary) {

        std::string fileType;
        int width, height;
        file >> fileType >> width >> height;
        pixels.resize(height, width);
//        std::string dummy;
//        std::getline(file, dummy);

        std::cout<<fileType<<" "<<width<<" "<<height<<"|"<<"|"<<std::endl;

        unsigned char byte;

        int row=0;
        int col=0;

        while (!file.eof()) {
            file.read(reinterpret_cast<char *>(&byte), 1);
            //std::cout << byte << " ";
            for (int i = 0; i < 8; ++i) {
                bool bit = byte & (1 << i);
                //std::cout << "Bit " << i << ": " << bit << std::endl;
                if(row < height){
                    pixels.setElementAt(row,col,bit);
                    std::cout<<bit<<" ";
                }else{
                    std::cout<<"OUT OF BOUND:"<<col<<";"<<row<<std::endl;
                }
                col++;
                if(col>=width){
                    col=0;
                    row++;
                }
            }


        }
        std::cout<<" loadROW:"<<row<<" COL:"<<col;
        std::cout << std::endl;

//        for (int i = 0; i < height; i++)
//        {
//            for (int j = 0; j < width; j++)
//            {
//                // Read the next byte from the file
//                file.read(&byte, 1);
//
//                // Extract the next bit from the byte
//                int pixel = (byte >> (7 - bitIndex)) & 0x01;
//
//                // Store the pixel value in the array
//                pixels.setElementAt(i,j,pixel);
//                std::cout<<pixel<<" ";
//
//                // Move to the next bit in the byte
//                bitIndex++;
//                if (bitIndex == 8)
//                {
//                    bitIndex = 0;
//                }
//            }
//            //std::cout<<std::endl;
//        }


        // std::cout<<fileType<<" "<<width<<" "<<height<<std::endl;
    } else {
        readMagicNumberFromFile(file);
        privateRead(file, isBinary);
        pixels.readFromFile(file);
    }
}

void ImagePBM::writeToFile(std::ofstream &file) {
    //writeMagicNumberToFile(file);
    file << "P1\n";
    file << pixels.getCols() << ' ' << pixels.getRows() << '\n';
    privateWrite(file);
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
    pixels.rotatePixels(direction);
}

void ImagePBM::toGrayscale() {
    //no-op
}

void ImagePBM::toMonochrome() {
    //no-op
}

void ImagePBM::toNegative() {
    pixels.negativeTransformation(1);
}

void ImagePBM::privateRead(std::ifstream &file, bool isBinary) {
    pixels.readAndResize(file);
}

void ImagePBM::privateWrite(std::ofstream &file) const {
    pixels.writeToFile(file);
}

void ImagePBM::copy(Image *image) {
    auto pbm = dynamic_cast<ImagePBM *>(image);

    if (pbm == nullptr) return; //incorrect image type

    pixels = pbm->pixels;

    Image::copy(image);
}