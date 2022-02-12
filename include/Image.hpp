#pragma once

#include <sstream>
#include <math.h>

#include <opencv2/opencv.hpp>


namespace Local{

    class Image{

        private:
            std::string _file_path; 
            cv::Mat _matrix;

        public:

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
            Image& quantize(int noTones);

            const cv::Mat& underlyingContainer();

            bool saveToDisk(std::string filePath);

            std::string info();
    };
}