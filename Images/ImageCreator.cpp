

#include "ImageCreator.h"
#include "ImagePBM.h"
#include "ImagePGM.h"
#include "ImagePPM.h"


Image *ImageCreator::createImage(std::string fileName) {

    if (fileName.compare(fileName.size() - 4, 4, ".pbm") == 0) {
        return new ImagePBM(fileName);
    } else if (fileName.compare(fileName.size() - 4, 4, ".pgm") == 0) {
        return new ImagePGM(fileName);
    } else {
        return new ImagePPM(fileName);
    }
}