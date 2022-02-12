#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>

namespace Local{

    class Image{


        public:
            cv::Mat _matrix;

            Image(std::string filePath);

            //! The copy constructor
            Image(const Image& other);

            //! The copy-assignment operator
            Image& operator=(const Image& other);

            // ~Image();

            //! Mirrors the image horizontally
            Image& mirrorH();

            //! Mirrors the image vertically
            Image& mirrorV();

            //! Converts the image to grayscale
            Image& toGrayScale();

            //! Quantizes the grayscale version into the given amount of tones
            Image& quantize(int tones);

            bool saveToDisk();
    };
}