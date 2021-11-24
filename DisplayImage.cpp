#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
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
        imgCrop=img(roi);
        imshow("Image", imgResize);
        imshow("Image Cropped", imgCrop);

        waitKey(1);
    }
}

int main(int argc, char **argv)
{

    string path = "waves.mp4";
    webcamResize();
    // useWebcam();
    // imageProcessing();

    return 0;
}

// int main(int argc, char** argv )
// {
//     // if ( argc != 2 )
//     // {
//     //     printf("usage: DisplayImage.out <Image_Path>\n");
//     //     return -1;
//     // }

//     string path="waves.mp4";

//     VideoCapture vid(path);

//     Mat image;

//     while(true){
//         vid.read(image);
//         imshow("Image", image);
//         waitKey(1);
//     }

//     // image = imread( argv[1], 1 );

//     // if ( !image.data )
//     // {
//     //     printf("No image data \n");
//     //     return -1;
//     // }
//     // namedWindow("Display Image", WINDOW_AUTOSIZE );
//     // imshow("Display Image", image);

//     // waitKey(0);

//     return 0;
// }