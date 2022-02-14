#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>

#include "Image.hpp"
#include "Input.hpp"
#include "Image2.hpp"

#include <QtWidgets>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>

using namespace cv;
using namespace Local;

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QWidget window;
    window.resize(320, 240);
    window.setWindowTitle(QApplication::translate("toplevel", "Main Window"));
    window.show();

    cv::Mat base_image;
    base_image = cv::imread(argv[1], 1);
    QImage test = QImage(argv[1]);
    Image2 newImageClassInstance = Image2(argv[1]);

    QImage imgIn= QImage((uchar*) base_image.data, base_image.cols, base_image.rows, base_image.step, QImage::Format_RGB888);
    imgIn = imgIn.rgbSwapped();

    newImageClassInstance.toGrayscale().quantize(8);

    QGraphicsScene scene;
    QGraphicsView view(&scene);
    // QGraphicsPixmapItem item(QPixmap::fromImage(newImageClassInstance.underlyingContainer()));
    QGraphicsPixmapItem item(QPixmap::fromImage(imgIn));
    scene.addItem(&item);
    newImageClassInstance.saveToJPEG("./file.jpeg", 100);
    view.show();

    waitKey(0);

    return app.exec();
}