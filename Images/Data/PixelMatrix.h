

#ifndef BITMAPGRAPHICS_PIXELPixelMatrix_H
#define BITMAPGRAPHICS_PIXELPixelMatrix_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <functional>

template<typename T>
class PixelMatrix {
public:
    PixelMatrix(int rows = 0, int cols = 0);

    ~PixelMatrix();

    int getRows() const;

    int getCols() const;

    void readFromFile(std::ifstream &file);

    void writeToFile(std::ofstream &file) const;

    T &getElementAt(int row, int col);

    void setElementAt(int row, int col, T elem);

    PixelMatrix<T> &operator=(const PixelMatrix<T> &other);

    T &getElement(int row, int col) const;

    void fillPixelMatrixWithZeroes(int rows, int cols);

    void resize(int rows, int cols);

     void readAndResize(std::ifstream &file);

     void rotatePixels(const std::string &direction);

     void negativeTransformation(const std::uint16_t value);


private:
    T **data;
    int countRows;
    int countColumns;

    void deleteData();

    void copy(const PixelMatrix<T> &other);

    void rotate(bool isRight);

    void fillPixelMatrix(int rows, int cols, std::function<void(T &, int, int)> pixelLogicFiller);

    void transpose();

    void reverseRows();
};

template<typename T>
void PixelMatrix<T>::rotate(bool isRight) {
    if (isRight) {
        reverseRows();
        transpose();
    } else {
        transpose();
        reverseRows();
    }
}

template<typename T>
void PixelMatrix<T>::setElementAt(int row, int col, T elem) {
    data[row][col] = elem;
}


template<typename T>
inline PixelMatrix<T>::PixelMatrix(const int rows, const int cols)
        : data(nullptr), countRows(rows), countColumns(cols) {
    fillPixelMatrixWithZeroes(rows, cols);
}

template<typename T>
inline PixelMatrix<T>::~PixelMatrix() {
    deleteData();
}

template<typename T>
inline int PixelMatrix<T>::getRows() const {
    return countRows;
}

template<typename T>
inline int PixelMatrix<T>::getCols() const {
    return countColumns;
}

template<typename T>
inline void PixelMatrix<T>::readFromFile(std::ifstream &file) {
    for (int row = 0; row < countRows; ++row) {
        for (int col = 0; col < countColumns; ++col) {
            file >> data[row][col];
        }
    }
}

template<typename T>
inline void PixelMatrix<T>::writeToFile(std::ofstream &file) const {
    for (int row = 0; row < countRows; ++row) {
        for (int col = 0; col < countColumns; ++col)
            file << data[row][col] << (col == countColumns - 1 ? '\n' : ' ');
    }
}

template<typename T>
inline T &PixelMatrix<T>::getElementAt(const int row, const int col) {
    return getElement(row, col);
}

template<typename T>
inline PixelMatrix<T> &PixelMatrix<T>::operator=(const PixelMatrix<T> &other) {
    if (this != &other) copy(other);
    return *this;
}

template<typename T>
inline void PixelMatrix<T>::deleteData() {
    for (int row = 0; row < countRows; ++row) {
        delete[] data[row];
        data[row] = nullptr;
    }
    delete[] data;
    data = nullptr;
}

template<typename T>
inline void PixelMatrix<T>::copy(const PixelMatrix<T> &other) {
    deleteData();
    countRows = other.countRows;
    countColumns = other.countColumns;

    data = new T *[countRows];

    for (int row = 0; row < countRows; ++row) {
        data[row] = new T[countColumns];

        for (int col = 0; col < countColumns; ++col)
            data[row][col] = other.data[row][col];
    }
}

template<typename T>
inline void
PixelMatrix<T>::fillPixelMatrix(const int rows, const int cols, std::function<void(T &, int, int)> pixelLogicFiller) {
    T **newData = new T *[rows];

    for (int row = 0; row < rows; ++row) {
        newData[row] = new T[cols];
        for (int col = 0; col < cols; ++col) {
            pixelLogicFiller(newData[row][col], row, col);
        }
    }

    deleteData();
    data = newData;
    countRows = rows;
    countColumns = cols;
}


template<typename T>
inline void PixelMatrix<T>::fillPixelMatrixWithZeroes(const int rows, const int cols) {
    fillPixelMatrix(rows, cols, [](T &elem, int, int) { elem = 0; });
}

template<typename T>
inline void PixelMatrix<T>::transpose() {
    fillPixelMatrix(countColumns, countRows, [=](T &elem, int row, int col) { elem = data[col][row]; });
}

template<typename T>
inline void PixelMatrix<T>::reverseRows() {
    fillPixelMatrix(countRows, countColumns, [=](T &elem, int row, int col) { elem = data[countRows - row - 1][col]; });
}

template<typename T>
inline T &PixelMatrix<T>::getElement(const int row, const int col) const {
    return data[row][col];
}

template<typename T>
inline void PixelMatrix<T>::resize(const int rows, const int cols) {
    fillPixelMatrix(rows, cols, [=](T &elem, int row, int col) {
        if (row < countRows && col < countColumns) { elem = data[row][col]; }
        else { elem = 0; }
    });
}
template<typename T>
inline void PixelMatrix<T>::readAndResize(std::ifstream &file) {
    int rows;
    int cols;
    file >> cols >> rows;
    std::cout<<cols<<" "<<rows<<std::endl;
    resize(rows, cols);
}

template<typename T>
inline void PixelMatrix<T>::rotatePixels(const std::string &direction) {
    if (direction == "left")
        rotate(false);
    else if (direction == "right")
        rotate(true);
}

template<typename T>
inline void PixelMatrix<T>::negativeTransformation(const std::uint16_t value) {
    for (int row = 0; row < countRows; ++row) {
        for (int col = 0; col < countColumns; ++col) {
            getElementAt(row, col) = value - getElementAt(row, col);
        }

    }
}



#endif //BITMAPGRAPHICS_PIXELPixelMatrix_H
