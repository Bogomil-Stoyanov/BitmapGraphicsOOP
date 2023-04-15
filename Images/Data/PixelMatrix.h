

#ifndef BITMAPGRAPHICS_PIXELPixelMatrix_H
#define BITMAPGRAPHICS_PIXELPixelMatrix_H

#include <iostream>
#include <fstream>
#include <cstdint>
#include <functional>

template <typename T>
class PixelMatrix {
public:
    PixelMatrix(const int rows = 0, const int cols = 0);
    PixelMatrix(const PixelMatrix<T>& other);
    ~PixelMatrix();

    int getRows() const;
    int getCols() const;

    void readFromFile(std::ifstream& file);
    void writeToFile(std::ofstream& file) const;

    void resize(const int rows, const int cols);

    void rotateRight();
    void rotateLeft();

    T& getElementAt(const int row, const int col);
    const T& getElementAt(const int row, const int col) const;
    void setElementAt(int row, int col, T elem);

    PixelMatrix<T>& operator=(const PixelMatrix<T>& other);

//private:
    T** data;
    int countRows;
    int countColumns;

    void deleteData();
    void copyPixelMatrix(const PixelMatrix<T>& other);
    void copy(const PixelMatrix<T>& other);

    void fillPixelMatrix(const int rows, const int cols, std::function<void(T&, int, int)> pixelLogicFiller);

    void fillPixelMatrixWithZeroes(const int rows, const int cols);
    void transpose();
    void reverseRows();

    T& getElement(const int row, const int col) const;
};

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
inline PixelMatrix<T>::PixelMatrix(const PixelMatrix<T>& other) {
    copy(other);
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
inline void PixelMatrix<T>::readFromFile(std::ifstream& file) {
    for (int row = 0; row < countRows; ++row){
        for (int col = 0; col < countColumns; ++col){
            file >> data[row][col];
        }
    }
}

template<typename T>
inline void PixelMatrix<T>::writeToFile(std::ofstream& file) const {
    for (int row = 0; row < countRows; ++row) {
        for (int col = 0; col < countColumns; ++col)
            file << data[row][col] << (col == countColumns - 1 ? '\n' : ' ');
    }
}

template<typename T>
inline void PixelMatrix<T>::resize(const int rows, const int cols) {
    fillPixelMatrix(rows, cols, [=](T& elem, int row, int col) {
        if (row < countRows && col < countColumns)
            elem = data[row][col];
        else
            elem = 0;
    });
}

template<typename T>
inline void PixelMatrix<T>::rotateRight() {
    reverseRows();
    transpose();
}

template<typename T>
inline void PixelMatrix<T>::rotateLeft() {
    transpose();
    reverseRows();
}

template<typename T>
inline T& PixelMatrix<T>::getElementAt(const int row, const int col) {
    return getElement(row, col);
}

template<typename T>
inline const T& PixelMatrix<T>::getElementAt(const int row, const int col) const {
    return getElement(row, col);
}

template<typename T>
inline PixelMatrix<T>& PixelMatrix<T>::operator=(const PixelMatrix<T>& other) {
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
inline void PixelMatrix<T>::copyPixelMatrix(const PixelMatrix<T>& other) {
    countRows = other.countRows;
    countColumns = other.countColumns;

    data = new T * [countRows];

    for (int row = 0; row < countRows; ++row) {
        data[row] = new T[countColumns];

        for (int col = 0; col < countColumns; ++col)
            data[row][col] = other.data[row][col];
    }
}

template<typename T>
inline void PixelMatrix<T>::copy(const PixelMatrix<T>& other) {
    deleteData();
    copyPixelMatrix(other);
}

template<typename T>
inline void PixelMatrix<T>::fillPixelMatrix(const int rows, const int cols, std::function<void(T&, int, int)> pixelLogicFiller) {
    T** blockOfMem = new T * [rows];

    for (int row = 0; row < rows; ++row) {
        blockOfMem[row] = new T[cols];

        for (int col = 0; col < cols; ++col)
            pixelLogicFiller(blockOfMem[row][col], row, col);
    }

    deleteData();
    data = blockOfMem;
    countRows = rows;
    countColumns = cols;
}

template<typename T>
inline void PixelMatrix<T>::fillPixelMatrixWithZeroes(const int rows, const int cols) {
    fillPixelMatrix(rows, cols, [](T& elem, int, int) { elem = 0; });
}

template<typename T>
inline void PixelMatrix<T>::transpose() {
    fillPixelMatrix(countColumns, countRows, [=](T& elem, int row, int col) { elem = data[col][row]; });
}

template<typename T>
inline void PixelMatrix<T>::reverseRows() {
    fillPixelMatrix(countRows, countColumns, [=](T& elem, int row, int col) { elem = data[countRows - row - 1][col]; });
}

template<typename T>
inline T& PixelMatrix<T>::getElement(const int row, const int col) const {
   return data[row][col];
}


#endif //BITMAPGRAPHICS_PIXELPixelMatrix_H
