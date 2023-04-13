#ifndef BITMAPGRAPHICS_PixelMatrixOPERATIONS_H
#define BITMAPGRAPHICS_PixelMatrixOPERATIONS_H


#include <fstream>
#include <algorithm>
#include "PixelMatrix.h"

template <typename T>
class PixelMatrixOperations {
public:
    static void readAndResize(std::ifstream& file, PixelMatrix<T>& pixels);

    static void rotatePixels(const std::string& direction, PixelMatrix<T>& pixels);

    static void writeToFile(std::ofstream& file, const PixelMatrix<T>& pixels);

    static void negativeTransformation(PixelMatrix<T>& pixels, const std::uint16_t value);
};

template<typename T>
inline void PixelMatrixOperations<T>::readAndResize(std::ifstream& file, PixelMatrix<T>& pixels) {
    int rows;
    int cols;

    file >> cols >> rows;

    pixels.resize(rows, cols);
}

template<typename T>
inline void PixelMatrixOperations<T>::rotatePixels(const std::string& direction, PixelMatrix<T>& pixels) {
    if (direction == "left")
        pixels.rotateLeft();
    else if (direction == "right")
        pixels.rotateRight();
}

template<typename T>
inline void PixelMatrixOperations<T>::writeToFile(std::ofstream& file, const PixelMatrix<T>& pixels) {
    file << pixels.getCols() << ' ' << pixels.getRows() << '\n';
}

template<typename T>
inline void PixelMatrixOperations<T>::negativeTransformation(PixelMatrix<T>& pixels, const std::uint16_t value) {
    for (int row = 0; row < pixels.getRows(); ++row)
        for (int col = 0; col < pixels.getCols(); ++col)
            pixels.getElementAt(row, col) = value - pixels.getElementAt(row, col);
}


#endif //BITMAPGRAPHICS_PixelMatrixOPERATIONS_H
