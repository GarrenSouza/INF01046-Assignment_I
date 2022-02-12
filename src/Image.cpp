#include "Image.hpp"

namespace Local{
    Image::Image(std::string filePath){
        _matrix = cv::imread(filePath);
    }

    Image::Image(const Image& other):
            _matrix(other._matrix.clone()){}

    Image& Image::operator=(const Image& other){
        _matrix = other._matrix.clone();
        return *this;
    }

    Image& Image::mirrorV(){
        cv::Size size = _matrix.size();
        uchar* buffer = new uchar[3*size.width];
        uchar pixelSize = _matrix.elemSize();
        uchar* b_buffer;
        int row_blength = pixelSize * size.width;

        for (size_t i = 0; i < size.height / 2; i++)
        {
            std::cout << "row index: " << i << std::endl;
            uchar* row = _matrix.ptr(i);
            int a_row = i;
            int b_row = size.height - 1 - i;
            if (a_row != b_row){
                b_buffer = _matrix.ptr(b_row);
                memcpy(buffer, row, row_blength); // buffer <- current_row
                memcpy(row, b_buffer, row_blength); // current row <- opposite row
                memcpy(b_buffer, buffer, row_blength); // opposite row <- (buffer = previous current row)
            }
        }
        return *this;
    }

    bool Image::saveToDisk(){
        // TODO Recap on PNG and JPEG compression techniques in order to answer the first question appropriately
        // std::vector<int> compression_params = {IMWRITE_JPEG_QUALITY, 20};
        return cv::imwrite("transformed_image.png", _matrix);
    }
}