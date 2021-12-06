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

void doneCallback(int state, void *data)
{
    state = 1;
}

void objectDetect()
{
    VideoCapture vid(0);
    Mat img = imread("images/amy2.jpg");
    Mat modifiedImg;
    CascadeClassifier faceCascade;
    faceCascade.load("Resources/twoeyes.xml");
    if (faceCascade.empty())
    {
        cout << "cascade empty\n";
        return;
    }
    Mat sunglasses = imread("images/sunglasses.png");

    float sHeight = (float)sunglasses.size().height;
    float sWidth = (float)sunglasses.size().width;
    Point2f src[4] = {{0.0f, 0.0f}, {sWidth, 0.0f}, {0.0f, sHeight}, {sWidth, sHeight}};

    vector<Rect> faces;
    int c = 0;
    Mat matrix, imgWarp, result, destinationROI;

    //UI
    int done = 0;
    namedWindow("Controls", (100, 50));
    createTrackbar("Done", "Controls", &done, 1);

    //END OF UI
    while (true)
    {
        vid.read(img);
        c++;
        // only re-calculate every 5 ms (otherwise it takes forever)
        if (c % 5 == 0)
        {
            faceCascade.detectMultiScale(img, faces, 1.1, 10);
        }
        for (int i = 0; i < faces.size(); i++)
        {
            Rect curr = faces[i];
            float left = curr.tl().x;
            float top = curr.tl().y;
            float right = curr.br().x;
            float bottom = curr.br().y;
            float height = top - bottom;
            float width = right - left;

            // cout << "AAA\n";
            resize(sunglasses, imgWarp, curr.size());
            // cout << "BBBB\n";
            resize(imgWarp, result, Size(), 1.4, 1.4);
            if(left+width*1.4<img.cols && top+height*1.4<img.rows ){

                destinationROI = img(Rect(Point(left - (int)(width * .2), top), result.size()));
            }

            // cout << "CCCCC\n";
            result.copyTo(destinationROI);

            // draw square around ROI
            // rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 255, 255), 5);
        }

        imshow("Webcam", img);

        waitKey(1);
        if (done)
        {
            imwrite("../image.jpg", img);
            break;
        }
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

int main(int argc, char **argv)
{

    string path = "waves.mp4";
    // webcamResize();
    // useWebcam();
    // imageProcessing();
    // drawShapesAndText();
    objectDetect();

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