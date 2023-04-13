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
    RGBPixelData(const std::uint16_t val = 0);
    RGBPixelData(const std::uint16_t red, const std::uint16_t green, const std::uint16_t blue);
    bool operator==(const RGBPixelData& other) const;

    void read(std::istream& in);
    void write(std::ostream& out) const;
    void toGrayscale();
    void normalize(const std::uint16_t value);
    void toNegative(const std::uint16_t value);

    void setRGB(const std::uint16_t value);
    void setRGB(const std::uint16_t red, const std::uint16_t green, const std::uint16_t blue);

    friend RGBPixelData& operator-(const std::uint16_t val, RGBPixelData& pixelData);
    friend std::istream& operator>>(std::istream& in, RGBPixelData& pixelData);
    friend std::ostream& operator<<(std::ostream& out, const RGBPixelData& pixelData);

};


#endif //BITMAPGRAPHICS_RGBPIXELDATA_H
