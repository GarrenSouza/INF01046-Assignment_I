#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>

#include "Input.hpp"
#include "Image.hpp"

using namespace cv;
using namespace Local;

int main(int argc, char** argv )
{
    cv::Mat base_image;
    
    Local::UserInput userInput;

    if ( argc != 2 )
    {
        printf("Usage: app.out <Image_Path>\n");
        return -1;
    }

    base_image = cv::imread( argv[1], 1 );
    if ( !base_image.data )
    {
        printf("No image data \n");
        return -1;
    }

    cv::namedWindow("Base Image", WINDOW_AUTOSIZE );
    cv::namedWindow("Transformed Image", WINDOW_AUTOSIZE );

    Local::Image transformed_image = Image(std::string(argv[1]));
    transformed_image.mirrorV();

    cv::imshow("Transformed Image", transformed_image._matrix);
    cv::imshow("Base Image", base_image);


    waitKey(0);
    return 0;
}