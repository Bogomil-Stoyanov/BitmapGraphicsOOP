#ifndef BITMAPGRAPHICS_RGBPIXELDATA_H
#define BITMAPGRAPHICS_RGBPIXELDATA_H

#include <iostream>
#include <cmath>

//https://www.whydomath.org/node/wavlets/imagebasics.html

struct RGBPixelData {
    
public:
    std::uint16_t red;
    std::uint16_t green;
    std::uint16_t blue;

public:
    RGBPixelData(std::uint16_t val = 0);
    RGBPixelData(std::uint16_t red, std::uint16_t green, std::uint16_t blue);
    bool operator==(const RGBPixelData& other) const;

    void read(std::istream& in);
    void write(std::ostream& out) const;
    void toGrayscale();
    void normalize(std::uint16_t value);
    void toNegative(std::uint16_t value);

    void setRGB(std::uint16_t value);
    void setRGB(std::uint16_t red, std::uint16_t green, std::uint16_t blue);

    friend RGBPixelData& operator-(std::uint16_t val, RGBPixelData& pixelData);
    friend std::istream& operator>>(std::istream& in, RGBPixelData& pixelData);
    friend std::ostream& operator<<(std::ostream& out, const RGBPixelData& pixelData);

};


#endif //BITMAPGRAPHICS_RGBPIXELDATA_H
