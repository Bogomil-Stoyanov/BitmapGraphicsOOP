#include "PixelMatrix.h"
#include "RGBPixelData.h"

//NOTE ALL INFINITE LOOP WARNINGS ARE NOT TRUE! CLION IS HAVING A SEIZURE!!!

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
inline PixelMatrix<T>::PixelMatrix(const int rows_, const int cols_)
        : data(nullptr), rows(rows_), columns(cols_) {
    fillPixelMatrixWithZeroes(rows_, cols_);
}

template<typename T>
inline PixelMatrix<T>::~PixelMatrix() {
    deleteData();
}

template<typename T>
inline int PixelMatrix<T>::getRows() const {
    return rows;
}

template<typename T>
inline int PixelMatrix<T>::getCols() const {
    return columns;
}

template<typename T>
inline void PixelMatrix<T>::readFromFile(std::ifstream &file) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col) {
            file >> data[row][col];
        }
    }
}

template<typename T>
inline void PixelMatrix<T>::writeToFile(std::ofstream &file) const {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < columns; ++col)
            file << data[row][col] << (col == columns - 1 ? '\n' : ' ');
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
    for (int row = 0; row < rows; ++row) {
        delete[] data[row];
        data[row] = nullptr;
    }
    delete[] data;
    data = nullptr;
}

template<typename T>
inline void PixelMatrix<T>::copy(const PixelMatrix<T> &other) {
    deleteData();
    rows = other.rows;
    columns = other.columns;

    data = new T *[rows];

    for (int row = 0; row < rows; ++row) {
        data[row] = new T[columns];

        for (int col = 0; col < columns; ++col)
            data[row][col] = other.data[row][col];
    }
}

template<typename T>
inline void
PixelMatrix<T>::fillPixelMatrix(const int newRows, const int newColumns,
                                std::function<void(T &, int, int)> pixelLogicFiller) {
    T **newData = new T *[newRows];

    for (int row = 0; row < newRows; ++row) {
        newData[row] = new T[newColumns];
        for (int col = 0; col < newColumns; ++col) {
            pixelLogicFiller(newData[row][col], row, col);
        }
    }

    deleteData();
    data = newData;
    rows = newRows;
    columns = newColumns;
}


template<typename T>
inline void PixelMatrix<T>::fillPixelMatrixWithZeroes(const int newRows, const int newCols) {
    fillPixelMatrix(newRows, newCols, [](T &elem, int, int) { elem = 0; });
}

template<typename T>
inline void PixelMatrix<T>::transpose() {
    fillPixelMatrix(columns, rows, [=](T &elem, int row, int col) { elem = data[col][row]; });
}

template<typename T>
inline void PixelMatrix<T>::reverseRows() {
    fillPixelMatrix(rows, columns, [=](T &elem, int row, int col) { elem = data[rows - row - 1][col]; });
}

template<typename T>
inline T &PixelMatrix<T>::getElement(const int row, const int col) const {
    return data[row][col];
}

template<typename T>
inline void PixelMatrix<T>::resize(const int newRows, const int newCols) {
    fillPixelMatrix(newRows, newCols, [=](T &elem, int row, int col) {
        if (row < rows && col < columns) { elem = data[row][col]; }
        else { elem = 0; }
    });
}

template<typename T>
inline void PixelMatrix<T>::readAndResize(std::ifstream &file) {
    int rows;
    int cols;
    file >> cols >> rows;
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
inline void PixelMatrix<T>::negativeTransformation(const unsigned short value) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < columns; ++col) {
            getElementAt(row, col) = value - getElementAt(row, col);
        }
    }
}

template
class PixelMatrix<RGBPixelData>;

template
class PixelMatrix<unsigned short>;