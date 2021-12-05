#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void useWebcam()
{
    VideoCapture vid(0);

    Mat img, imgGrey, imgCanny;

    while (true)
    {
        vid.read(img);
        cvtColor(img, imgGrey, COLOR_BGR2GRAY);
        Canny(imgGrey, imgCanny, 50, 150);
        imshow("Image", imgCanny);

        waitKey(1);
    }
}

void imageProcessing()
{
    string path = "amy2.jpg";
    Mat img = imread(path);
    Mat imgGrey;
    cvtColor(img, imgGrey, COLOR_BGR2GRAY);

    imshow("Greyscale", imgGrey);
    waitKey(0);
}

void webcamResize()
{
    VideoCapture vid(0);

    Mat img, imgResize, imgCrop;

    while (true)
    {
        vid.read(img);
        resize(img, imgResize, Size(), 0.5, 0.5);
        Rect roi(100, 100, 200, 250);
        imgCrop = img(roi);
        imshow("Image", imgResize);
        imshow("Image Cropped", imgCrop);

        waitKey(1);
    }
}

void drawShapesAndText()
{
    VideoCapture vid(0);

    Mat img(512, 512, CV_8UC3, Scalar(255, 255, 250));

    circle(img, Point(256, 256), 155, Scalar(0, 69, 255), 10);

    imshow("Drawing", img);
    waitKey(0);
}