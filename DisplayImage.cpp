#include <stdio.h>
#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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
    Mat matrix, imgWarp, result;

    //UI
    int done = 0;
    namedWindow("Controls", (100, 100));
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

            Mat destinationROI = img(Rect(Point(left - (int)(width * .2), top), result.size()));

            // cout << "CCCCC\n";
            result.copyTo(destinationROI);

            // draw square around ROI
            // rectangle(img, faces[i].tl(), faces[i].br(), Scalar(255, 255, 255), 5);
        }

        imshow("Webcam", img);

        waitKey(1);
        if (done)
        {
            break;
        }
    }
}

int main(int argc, char **argv)
{

    string path = "waves.mp4";

    // objectDetect();
    QApplication app(argc, argv);
    QLabel hello("<center>Welcome to my first Qt program</center>");
    hello.setWindowTitle("My First Qt Program");
    hello.resize(400, 400);
    hello.show();
    return app.exec();

    return 0;
}