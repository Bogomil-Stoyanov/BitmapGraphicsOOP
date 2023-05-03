

#ifndef BITMAPGRAPHICS_PIXELPixelMatrix_H
#define BITMAPGRAPHICS_PIXELPixelMatrix_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <functional>

template<typename T>
class PixelMatrix {
public:
    PixelMatrix(int rows_ = 0, int cols_ = 0);

    ~PixelMatrix();

    int getRows() const;

    int getCols() const;

    void readFromFile(std::ifstream &file);

    void writeToFile(std::ofstream &file) const;

    T &getElementAt(int row, int col);

    void setElementAt(int row, int col, T elem);

    PixelMatrix<T> &operator=(const PixelMatrix<T> &other);

    T &getElement(int row, int col) const;

    void fillPixelMatrixWithZeroes(int newRows, int newCols);

    void resize(int newRows, int newCols);

    void readAndResize(std::ifstream &file);

    void rotatePixels(const std::string &direction);

    void negativeTransformation(const std::uint16_t value);


private:
    T **data;
    int rows;
    int columns;

    void deleteData();

    void copy(const PixelMatrix<T> &other);

    void rotate(bool isRight);

    void fillPixelMatrix(int newRows, int newColumns, std::function<void(T &, int, int)> pixelLogicFiller);

    void transpose();

    void reverseRows();
};

#endif //BITMAPGRAPHICS_PIXELPixelMatrix_H
