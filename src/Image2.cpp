#include "Image2.hpp"

namespace Local {

Image2::Image2(std::string filePath) : _file_path(filePath) {
    _matrix = QImage(filePath.c_str());
}

Image2::Image2(const Image2 &other) : _matrix(other._matrix),
                                   _file_path(other._file_path) {}

Image2 &Image2::operator=(const Image2 &other) {
    _matrix = other._matrix;
    return *this;
}

Image2 &Image2::mirrorH() {
    uint32_t height = _matrix.height();
    uint32_t width = _matrix.width();

    uchar pixel_size = _matrix.depth()/8;
    uchar *buffer = new uchar[pixel_size];
    uchar *a_buffer, *b_buffer, *row;

    for (size_t i = 0; i < height; i++) {
        row = _matrix.scanLine(i);
        for (size_t j = 0; j < width / 2; j++) {
            int b_column = width - 1 - j;
            if (j != b_column) {
                a_buffer = row + j * pixel_size;
                b_buffer = row + b_column * pixel_size;
                memcpy(buffer, a_buffer, pixel_size);   // buffer <- current_row
                memcpy(a_buffer, b_buffer, pixel_size); // current row <- opposite row
                memcpy(b_buffer, buffer, pixel_size);   // opposite row <- (buffer = previous current row)
            }
        }
    }
    return *this;
}

Image2 &Image2::mirrorV() {
    uint32_t height = _matrix.height();
    uint32_t width = _matrix.width();

    uchar *buffer = new uchar[width];
    uchar pixel_size = _matrix.depth()/8;
    uchar *b_buffer, *row;
    int row_blength = _matrix.bytesPerLine();

    std::cout << width << std::endl;

    for (size_t i = 0; i < height / 2; i++) {
        row = _matrix.scanLine(i);
        int a_row = i;
        int b_row = height - 1 - i;
        if (a_row != b_row) {
            b_buffer = _matrix.scanLine(b_row);
            memcpy(buffer, row, row_blength);      // buffer <- current_row
            memcpy(row, b_buffer, row_blength);    // current row <- opposite row
            memcpy(b_buffer, buffer, row_blength); // opposite row <- (buffer = previous current row)
        }
    }
    return *this;
}

Image2 &Image2::toGrayscale() {
    uint32_t height = _matrix.height();
    uint32_t width = _matrix.width();

    uchar *row, pixel_size = _matrix.depth()/8;
    float L;
    int offset;

    for (size_t i = 0; i < height; i++) {
        row = _matrix.scanLine(i);
        for (size_t j = 0; j < width; j++) {
            offset = j * pixel_size;
            L = 0.299 * row[offset] + 0.587 * row[offset + 1] + 0.114 * row[offset + 2];

            row[offset] = (uchar)L;
            row[offset + 1] = (uchar)L;
            row[offset + 2] = (uchar)L;
        }
    }
    return *this;
}

bool Image2::saveToJPEG(std::string filePath, int quality) {
    // TODO Recap on PNG and JPEG compression techniques in order to answer the first question appropriately
    return _matrix.save(QString(filePath.c_str()), "JPG", quality);
}

const QImage &Image2::underlyingContainer() {
    return _matrix;
}

Image2 &Image2::quantize(int n_of_tones) {
    uint32_t height = _matrix.height();
    uint32_t width = _matrix.width();

    uchar *image_row, pixel_size = _matrix.depth()/8;
    float L;
    int offset;
    uchar t1 = 255, t2 = 0;

    // scanning for the tone range
    for (size_t i = 0; i < height; i++) {
        image_row = _matrix.scanLine(i);
        for (size_t j = 0; j < width; j++) {
            offset = j * pixel_size;
            if (image_row[offset] > t2)
                t2 = image_row[offset];
            if (image_row[offset] < t1)
                t1 = image_row[offset];
        }
    }

    int current_tone_range = t2 - t1 + 1; // must be stored with the appropriate value range (i.e.: must prevent overflow)

    if (n_of_tones < current_tone_range) {
        float bin_size = float(current_tone_range) / n_of_tones;
        uchar quantized_value, *image_row;
        float L_value;

        int offset;
        float alpha, bin_center, rounded_q;

        std::cout << height << ", " << width << ", " << int(pixel_size) << "bytes per pixel" << std::endl;

        for (size_t i = 0; i < height; i++) {
            image_row = _matrix.scanLine(i);
            for (size_t j = 0; j < width; j++) {
                offset = j * pixel_size;

                alpha = floor((image_row[offset] - (t1 - 0.5)) / bin_size);
                bin_center = alpha * bin_size + t1 - .5 + bin_size / 2;
                quantized_value = uchar(round(bin_center));

                image_row[offset] = quantized_value;
                image_row[offset + 1] = quantized_value;
                image_row[offset + 2] = quantized_value;
            }
        }
    }
    return *this;
}
std::string Image2::info() {
    std::stringstream output;
    output << "FilePath: " << _file_path << std::endl;
    output << "Resolution: " << _matrix.width() << "x" << _matrix.width() << std::endl;
    output << "Pixel Size: " << _matrix.depth() / 8 << std::endl;
    
    return output.str();
}
} // namespace Local