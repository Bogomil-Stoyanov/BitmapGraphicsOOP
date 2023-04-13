

#ifndef BITMAPGRAPHICS_IMAGEPGM_H
#define BITMAPGRAPHICS_IMAGEPGM_H


#include <algorithm>

#include "Image.h"
#include "Data/PixelMatrix.h"

class ImagePGM : public Image {
public:
    ImagePGM(std::string fileName);
    ImagePGM(const ImagePGM& other);

    ImagePGM* copy() override;

    void readFromFile(std::ifstream& file) override;
    void writeToFile(std::ofstream& file) override;

    void rotate(std::string direction) override;

    void toGrayscale() override;
    void toMonochrome() override;
    void toNegative() override;

private:
    PixelMatrix<std::uint16_t> m_pixels;

    void privateRead(std::ifstream& file) override;

    void privateWrite(std::ofstream& file) const override;

    void copy(Image* image) override;
};


#endif //BITMAPGRAPHICS_IMAGEPGM_H
