#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "Image.hpp"
#include "Input.hpp"
#include <QtWidgets>

using namespace cv;
using namespace Local;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.show();
    window.setWindowTitle(QApplication::translate("toplevel", "Main Window"));
    return app.exec();
    // cv::Mat base_image;

    // Local::UserInput userInput;

    // if (argc < 2) {
    //     printf("Usage: app.out <Image_Path>\n");
    //     return -1;
    // }

    // base_image = cv::imread(argv[1], 1);
    // if (!base_image.data) {
    //     printf("No image data \n");
    //     return -1;
    // }

    // cv::namedWindow("Base Image", WINDOW_AUTOSIZE);
    // cv::namedWindow("Transformed Image", WINDOW_AUTOSIZE);

    // Local::Image processing_image = Image(std::string(argv[1]));
    // std::cout << processing_image.info() << std::endl;
    // processing_image.toGrayscale();
    // cv::imshow("Base Image", base_image);
    // cv::imshow("Transformed Image", processing_image.underlyingContainer());

    // waitKey(0);
    // // processing_image.saveToDisk(std::string(argv[3]));
    // return 0;
}