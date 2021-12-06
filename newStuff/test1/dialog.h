#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

public slots:
    void processImg();

private slots:
    void on_startButton_released();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_grayButton_clicked();

    void on_normButton_clicked();

    void on_drawButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::Dialog *ui;
    cv::VideoCapture cam;
    cv::Mat img;
    cv::Mat filtered;
    std::vector<QImage> pics;
    QImage filteredimg;

    QTimer* tmr;
    std::vector<QImage>::iterator iter;
    cv::CascadeClassifier faceCascade;
    cv::Mat sunglasses;
    int col;
    int cur;



};
#endif // DIALOG_H
