#pragma once

#include <math.h>
#include <iostream>
#include <sstream>

#include <QImage>


namespace Local {

class Image2 {

private:
    std::string _file_path;
    QImage _matrix;

public:
    Image2(std::string filePath);

    //! The copy constructor
    Image2(const Image2 &other);

    //! The copy-assignment operator
    Image2 &operator=(const Image2 &other);

    // ~Image();

    //! Mirrors the image horizontally
    Image2 &mirrorH();

    //! Mirrors the image vertically
    Image2 &mirrorV();

    //! Converts the image to grayscale
    Image2 &toGrayscale();

    //! Quantizes the grayscale version into the given amount of tones
    Image2 &quantize(int noTones);

    const QImage &underlyingContainer();

    bool saveToJPEG(std::string filePath, int quality);

    std::string info();
};
} // namespace Local