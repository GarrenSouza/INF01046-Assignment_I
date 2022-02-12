#include "Image.hpp"

namespace Local{
    Image::Image(std::string filePath):_file_path(filePath){
        _matrix = cv::imread(filePath);
    }

    Image::Image(const Image& other):
            _matrix(other._matrix.clone()),
            _file_path(other._file_path){}

    Image& Image::operator=(const Image& other){
        _matrix = other._matrix.clone();
        return *this;
    }

    Image& Image::mirrorH(){
        cv::Size size = _matrix.size();
        uchar pixel_size = _matrix.elemSize();
        uchar * buffer = new uchar[pixel_size];
        uchar *a_buffer, *b_buffer, *row;

        for (size_t i = 0; i < size.height; i++)
        {
            row = _matrix.ptr(i);
            for (size_t j = 0; j < size.width/2; j++)
            {
                int b_column = size.width - 1 - j;
                if (j != b_column){
                    a_buffer = row + j * pixel_size;
                    b_buffer = row + b_column * pixel_size;
                    memcpy(buffer, a_buffer, pixel_size * sizeof(uchar)); // buffer <- current_row
                    memcpy(a_buffer, b_buffer, pixel_size * sizeof(uchar)); // current row <- opposite row
                    memcpy(b_buffer, buffer, pixel_size * sizeof(uchar)); // opposite row <- (buffer = previous current row)
                }
            }
        }
        return *this;
    }

    Image& Image::mirrorV(){
        cv::Size size = _matrix.size();
        uchar* buffer = new uchar[3*size.width];
        uchar pixel_size = _matrix.elemSize();
        uchar* b_buffer, *row;
        int row_blength = pixel_size * size.width;

        for (size_t i = 0; i < size.height / 2; i++)
        {
            row = _matrix.ptr(i);
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

    Image& Image::toGrayScale(){        cv::Size size = _matrix.size();
        uchar *row, pixel_size = _matrix.elemSize();
        float L;
        int offset;

        for (size_t i = 0; i < size.height; i++)
        {
            row = _matrix.ptr(i);
            for (size_t j = 0; j < size.width; j++)
            {
                offset = j*pixel_size;
                L = 0.299*row[offset+2] + 0.587*row[offset+1] + 0.114*row[offset];

                row[offset] = (uchar) L;
                row[offset + 1] = (uchar) L;
                row[offset + 2] = (uchar) L;
            }
        }
        return *this;
    }

    bool Image::saveToDisk(std::string filePath){
        // TODO Recap on PNG and JPEG compression techniques in order to answer the first question appropriately
        // std::vector<int> compression_params = {IMWRITE_JPEG_QUALITY, 20};
        return cv::imwrite(filePath, _matrix);
    }

    const cv::Mat& Image::underlyingContainer(){
        return _matrix;
    }

    Image& Image::quantize(int n_of_tones){
        
        cv::Size size = _matrix.size();
        uchar *image_row, pixel_size = _matrix.elemSize();
        float L;
        int offset;
        uchar t1 = 255, t2 = 0;

        // scanning for the tone range
        for (size_t i = 0; i < size.height; i++)
        {
            image_row = _matrix.ptr(i);
            for (size_t j = 0; j < size.width; j++)
            {
                offset = j*pixel_size;
                if(image_row[offset] > t2)
                    t2 = image_row[offset];
                if(image_row[offset] < t1)
                    t1 = image_row[offset];
            }
        }

        int current_tone_range = t2 - t1 + 1; // must be stored with the appropriate value range (i.e.: must prevent overflow)
        
        if(n_of_tones < current_tone_range){
            float bin_size = float(current_tone_range) / n_of_tones;
            uchar quantized_value, *image_row;
            float L_value;
            uchar pixelSize = _matrix.elemSize();

            int offset;
            float alpha, bin_center, rounded_q;

            for (size_t i = 0; i < size.height; i++)
            {
                image_row = _matrix.ptr(i);
                for (size_t j = 0; j < size.width; j++)
                {
                    offset = j*pixelSize;
                    
                    alpha = floor((image_row[offset] - (t1 - 0.5)) / bin_size);
                    bin_center = alpha * bin_size + t1 - .5 + bin_size/2;
                    quantized_value = uchar(round(bin_center));

                    image_row[offset] = quantized_value;
                    image_row[offset + 1] = quantized_value;
                    image_row[offset + 2] = quantized_value;
                }
            }
            
        }
        return *this;
    }
    std::string Image::info(){
        std::stringstream output;
        output << "FilePath: " << _file_path << std::endl;
        output << "Resolution: " << _matrix.size().width << "x" << _matrix.size().width << std::endl;
        output << "Channels: " << _matrix.elemSize() / _matrix.elemSize1()  << std::endl;
        output << "Channel Size: " << _matrix.elemSize1();
        return output.str();
    }
}