

#include "RGBPixelData.h"

RGBPixelData::RGBPixelData(const unsigned short val)
        : red(val), green(val), blue(val) {
}

RGBPixelData::RGBPixelData(const unsigned short red, const unsigned short green, const unsigned short blue)
        : red(red), green(green), blue(blue) {
}

bool RGBPixelData::operator==(const RGBPixelData& other) const {
    return (red == other.red && green == other.green && blue == other.blue);
}

void RGBPixelData::read(std::istream& in) {
    in >> *this;
}

void RGBPixelData::write(std::ostream& out) const {
    out << *this;
}

void RGBPixelData::toGrayscale() {
    unsigned short gray = std::round((0.229 * red) + (0.587 * green) + (0.114 * blue));

    setRGB(gray);
}

void RGBPixelData::normalize(const unsigned short value) {
    unsigned short BWVal = std::round((double)(red + green + blue) / (3 * value));

    setRGB(value * BWVal);
}

void RGBPixelData::toNegative(const unsigned short value) {
    *this = value - *this;
}

void RGBPixelData::setRGB(const unsigned short val) {
    red = val;
    green = val;
    blue = val;
}

void RGBPixelData::setRGB(const unsigned short red, const unsigned short green, const unsigned short blue) {
    this->red  = red;
    this->green = green;
    this->blue = blue;
}

RGBPixelData& operator-(const unsigned short val, RGBPixelData& rgb) {
    rgb.setRGB(val - rgb.red, val - rgb.green, val - rgb.blue);

    return rgb;
}

std::istream& operator>>(std::istream& in, RGBPixelData& RGBPixelData) {
    return (in >> RGBPixelData.red >> RGBPixelData.green >> RGBPixelData.blue);
}

std::ostream& operator<<(std::ostream& out, const RGBPixelData& RGBPixelData) {
    return (out << RGBPixelData.red << ' ' << RGBPixelData.green << ' ' << RGBPixelData.blue);
}