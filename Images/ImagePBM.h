

#ifndef BITMAPGRAPHICS_IMAGEPBM_H
#define BITMAPGRAPHICS_IMAGEPBM_H

#include "Image.h"
#include "Data/PixelMatrix.h"

class ImagePBM : public Image {
public:
    ImagePBM(std::string fileName);
    ImagePBM(const ImagePBM& other);

    ImagePBM* copy() override;

    void readFromFile(std::ifstream& file) override;
    void writeToFile(std::ofstream& file) override;

    void rotate(std::string direction) override;

    void toGrayscale() override;
    void toMonochrome() override;
    void toNegative() override;

private:
    static const std::uint16_t MAX_COLOR_VALUE = 1;
    PixelMatrix<std::uint16_t> pixels;
    void privateRead(std::ifstream& file) override;
    void privateWrite(std::ofstream& file) const override;
    void copy(Image* image) override;
};



#endif //BITMAPGRAPHICS_IMAGEPBM_H
