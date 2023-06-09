

#ifndef BITMAPGRAPHICS_IMAGEPPM_H
#define BITMAPGRAPHICS_IMAGEPPM_H

#include <string>
#include "Image.h"
#include "Data/RGBPixelData.h"
#include "Data/PixelMatrix.h"


class ImagePPM : public Image {
public:
    explicit ImagePPM(std::string fileName);
    ImagePPM(const ImagePPM& other);
    ~ImagePPM();


    ImagePPM* copy() override;

    void readFromFile(std::ifstream& file, bool isBinary) override;
    void writeToFile(std::ofstream& file) override;

    void rotate(std::string direction) override;

    void toGrayscale() override;
    void toMonochrome() override;
    void toNegative() override;
    Image* toCollage(Image* image2, const std::string& direction, const std::string& outPath) override;

private:
    PixelMatrix<RGBPixelData> pixels;

    void privateRead(std::ifstream& file) override;
    void privateBinaryRead(std::ifstream& file) override;

    void privateWrite(std::ofstream& file) const override;

    void copy(Image* image) override;


};


#endif //BITMAPGRAPHICS_IMAGEPPM_H
