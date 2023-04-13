

#ifndef BITMAPGRAPHICS_IMAGECREATOR_H
#define BITMAPGRAPHICS_IMAGECREATOR_H

#include "Image.h"


class ImageCreator {
public:
    ImageCreator() = delete;

    ImageCreator(const ImageCreator &) = delete;

    ImageCreator &operator=(const ImageCreator &) = delete;

    static Image *createImage(std::string fileName);
};


#endif //BITMAPGRAPHICS_IMAGECREATOR_H
