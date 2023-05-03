#ifndef BITMAPGRAPHICS_RGBPIXELDATA_H
#define BITMAPGRAPHICS_RGBPIXELDATA_H

#include <iostream>
#include <cmath>

//https://www.whydomath.org/node/wavlets/imagebasics.html

struct RGBPixelData {
    
public:
    unsigned short red;
    unsigned short green;
    unsigned short blue;

public:
    RGBPixelData(unsigned short val = 0);
    RGBPixelData(unsigned short red, unsigned short green, unsigned short blue);
    bool operator==(const RGBPixelData& other) const;

    void read(std::istream& in);
    void write(std::ostream& out) const;
    void toGrayscale();
    void normalize(unsigned short value);
    void toNegative(unsigned short value);

    void setRGB(unsigned short value);
    void setRGB(unsigned short red, unsigned short green, unsigned short blue);

    friend RGBPixelData& operator-(unsigned short val, RGBPixelData& pixelData);
    friend std::istream& operator>>(std::istream& in, RGBPixelData& pixelData);
    friend std::ostream& operator<<(std::ostream& out, const RGBPixelData& pixelData);

};


#endif //BITMAPGRAPHICS_RGBPIXELDATA_H
