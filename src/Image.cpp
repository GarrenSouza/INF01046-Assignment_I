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

    Image& Image::mirrorH(){
        cv::Size size = _matrix.size();
        uchar pixelSize = _matrix.elemSize();
        uchar * buffer = new uchar[pixelSize];
        uchar *a_buffer, *b_buffer, *row;

        for (size_t i = 0; i < size.height; i++)
        {
            row = _matrix.ptr(i);
            for (size_t j = 0; j < size.width/2; j++)
            {
                int b_column = size.width - 1 - j;
                if (j != b_column){
                    a_buffer = row + j * pixelSize;
                    b_buffer = row + b_column * pixelSize;
                    memcpy(buffer, a_buffer, pixelSize * sizeof(uchar)); // buffer <- current_row
                    memcpy(a_buffer, b_buffer, pixelSize * sizeof(uchar)); // current row <- opposite row
                    memcpy(b_buffer, buffer, pixelSize * sizeof(uchar)); // opposite row <- (buffer = previous current row)
                }
            }
        }
        return *this;
    }

    Image& Image::mirrorV(){
        cv::Size size = _matrix.size();
        uchar* buffer = new uchar[3*size.width];
        uchar pixelSize = _matrix.elemSize();
        uchar* b_buffer, *row;
        int row_blength = pixelSize * size.width;

        for (size_t i = 0; i < size.height / 2; i++)
        {
            row = _matrix.ptr(i);
            std::cout << "row index: " << i << std::endl;
            int a_row = i;
            int b_row = size.height - 1 - i;
            if (a_row != b_row){
                b_buffer = _matrix.ptr(b_row);
                memcpy(buffer, row, row_blength*sizeof(uchar)); // buffer <- current_row
                memcpy(row, b_buffer, row_blength*sizeof(uchar)); // current row <- opposite row
                memcpy(b_buffer, buffer, row_blength*sizeof(uchar)); // opposite row <- (buffer = previous current row)
            }
        }
        return *this;
    }

    Image& Image::toGrayScale(){
        cv::Size size = _matrix.size();
        uchar *row, pixelSize = _matrix.elemSize();
        float L;
        int offset;

        for (size_t i = 0; i < size.height; i++)
        {
            row = _matrix.ptr(i);
            for (size_t j = 0; j < size.width; j++)
            {
                offset = j*pixelSize;
                L = 0.299*row[offset+2] + 0.587*row[offset+1] + 0.114*row[offset];

                row[offset] = (uchar) L;
                row[offset + 1] = (uchar) L;
                row[offset + 2] = (uchar) L;
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