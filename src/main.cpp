#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "Image.hpp"
#include "Input.hpp"
#include <QtWidgets>

using namespace cv;
using namespace Local;

int main(int argc, char **argv) {
    // cv::Mat base_image;

    Local::UserInput userInput;

    if (argc < 2) {
        printf("Usage: app.out <Image_Path>\n");
        return -1;
    }

    // base_image = cv::imread(argv[1], 1);
    // if (!base_image.data) {
    //     printf("No image data \n");
    //     return -1;
    // }

    Local::Image base_image = Image(std::string(argv[1]));
    Local::Image processing_image = Image(base_image);
    std::cout << processing_image.info() << std::endl;

    bool exit = false;
    char option = '0';
    while (!exit) {
        std::cout << "|----[ Garren's Image Manipulation Tool ]----|" << std::endl;
        std::cout << "| Enter the operation:" << std::endl;
        std::cout << "| g. convert to grayscale" << std::endl;
        std::cout << "| v. flip verticaly" << std::endl;
        std::cout << "| h. flip horizontally" << std::endl;
        std::cout << "| q. quantize" << std::endl;
        std::cout << "| r. reset to base image" << std::endl;
        std::cout << "| s. see result" << std::endl;
        std::cout << "| j. save to JPEG" << std::endl;
        std::cout << "| e. exit" << std::endl;
        option = userInput.getUserInput("Option: ", std::cin)[0];
        switch (option) {
        case 'e':
            exit = true;
            break;

        case 'v': // flips vertically
            processing_image.mirrorV();
            break;

        case 'h': // flips horizontally
            processing_image.mirrorH();
            break;

        case 'g': // converts to grayscale
            processing_image.toGrayscale();
            break;

        case 'q': // quantize
            processing_image.toGrayscale().quantize(std::stoi(userInput.getUserInput("| Tones in target set: ", std::cin)));
            break;

        case 'j': // save to JPEG file
            processing_image.saveToDisk(userInput.getUserInput("| Enter the file path: ", std::cin));
            break;

        case 'r': // resets to base image
            processing_image = base_image;
            break;

        case 's': // see result
            cv::namedWindow("Base Image", WINDOW_AUTOSIZE);
            cv::namedWindow("Transformed Image", WINDOW_AUTOSIZE);
            cv::imshow("Base Image", base_image.underlyingContainer());
            cv::imshow("Transformed Image", processing_image.underlyingContainer());
            waitKey(0);
            break;
        default:
            std::cout << ">Invalid option!" << std::endl;
            break;
        }
    }
    return 0;
}