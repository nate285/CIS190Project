#include "dialog.h"
#include "./ui_dialog.h"
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <QFile>
#include <QFileDialog>
#include <iostream>
#include <QtCore>
#include <filesystem>
#include <QPainter>
using namespace cv;
using namespace std;




///////////////////////////////////////
Dialog::Dialog(QWidget *parent): QDialog(parent) , ui(new Ui::Dialog)
{

    col = 0;
    ui->setupUi(this);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    cam.open(0);
    if(cam.isOpened() == false) {
        ui->errorMsg->setText("error: camera not found");
        return;
    }
    tmr = new QTimer(this);
    connect(tmr, SIGNAL(timeout()), this, SLOT(processImg()));
    tmr->start(20);

    iter = pics.begin();

}
/////////////////////////////////////////////////////////
Dialog::~Dialog()
{
    delete ui;
}

void Dialog::processImg() {
    cam.read(img);




    int frameHeight=431, frameWidth=239;

    if(img.empty() == true){
        ui->errorMsg->setText("error: image not found");
        return;
    }

    if(col == 1) {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        QImage processedImg((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        filteredimg=processedImg.scaled(frameHeight, frameWidth, Qt::KeepAspectRatio);
        ui->imageLabel->setPixmap(QPixmap::fromImage(filteredimg));

    } else if(col == 2) {
        cv::cvtColor(img, img, cv::COLOR_BGR2GRAY);
        cv::Mat kernel=cv::getStructuringElement(cv::MORPH_RECT, cv::Size(6,6));
        cv::Canny(img, img, 50, 150);
        cv::dilate(img, img, kernel);
        cv::threshold(img, img, 100, 255, cv::THRESH_BINARY);
        cv::bitwise_not(img, img);
        QImage processedImg((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_Grayscale8);
        filteredimg=processedImg.scaled(frameHeight, frameWidth, Qt::KeepAspectRatio);
        ui->imageLabel->setPixmap(QPixmap::fromImage(filteredimg));

    }else {
        cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
        QImage processedImg((uchar*) img.data, img.cols, img.rows, img.step, QImage::Format_RGB888);
        filteredimg=processedImg.scaled(frameHeight, frameWidth, Qt::KeepAspectRatio);
        ui->imageLabel->setPixmap(QPixmap::fromImage(filteredimg));
    }



}

////////////////////////////////////////////////////////////
void Dialog::on_startButton_released()
{
    if(tmr->isActive()){
        tmr->stop();
        ui->startButton->setText("restart");
    }else{
        tmr->start(20);
        ui->startButton->setText("pause");
    }
}

void Dialog::on_pushButton_clicked()
{

    QImage temp = filteredimg.copy(0, 0, filteredimg.width(), filteredimg.height() );
    ui->picture->setPixmap(QPixmap::fromImage(temp));
    pics.push_back(temp);
    iter=pics.end()-1;
    char buffer[100];
    sprintf(buffer, "%d/%d\n", pics.size(), pics.size());
    QString s(buffer);
    ui->index->setText(s);

    ui->pushButton_3->setEnabled(false);
    if(iter != pics.begin()) {
        ui->pushButton_2->setEnabled(true);
    }


}


void Dialog::on_pushButton_2_clicked()
{

    // go to previous iterator and set imahe
    if(iter==pics.begin()){
        if(pics.begin() != pics.end()) {
            ui->pushButton_3->setEnabled(true);
        }
        ui->pushButton_2->setEnabled(false);
        return;
    }else{
        ui->pushButton_3->setEnabled(true);
        iter--;
        if(iter==pics.begin()){
            ui->pushButton_2->setEnabled(false);
        }
        if(iter<pics.end()-1){
            ui->pushButton_3->setEnabled(true);
        }
        ui->picture->setPixmap(QPixmap::fromImage(*iter));

        int cur = iter - pics.begin();
        cur++;
        char buffer[100];
        sprintf(buffer, "%d/%d\n", cur, pics.size());
        QString s(buffer);
        ui->index->setText(s);
    }
}

void Dialog::on_pushButton_3_clicked()
{
    // go to next image

    if(iter < pics.end() - 1){
        iter++;
        if(iter>pics.begin()){
            ui->pushButton_2->setEnabled(true);
        }
        if(iter==(pics.end()-1)){
            ui->pushButton_3->setEnabled(false);
        }
        ui->picture->setPixmap(QPixmap::fromImage(*iter));

        int cur = iter - pics.begin();
        cur++;
        char buffer[100];
        sprintf(buffer, "%d/%d\n", cur, pics.size());
        QString s(buffer);
        ui->index->setText(s);
    }
}

void Dialog::on_grayButton_clicked()
{
    col = 1;
}

void Dialog::on_normButton_clicked()
{
    col = 0;
}

void Dialog::on_drawButton_clicked()
{
    col = 2;
}

void Dialog::on_deleteButton_clicked()
{
    QImage image=*iter;
    if(pics.size() == 0) {
        return;
    }
    iter = pics.erase(iter);
    if(pics.size() == 0) {

        ui->pushButton_3->setEnabled(false);
        ui->pushButton_2->setEnabled(false);

        QPainter p;
        p.begin(&image);
        p.setCompositionMode(QPainter::CompositionMode_DestinationIn);
        p.fillRect(image.rect(), QColor(255, 255, 255, 0));
        p.end();
        ui->picture->setPixmap(QPixmap::fromImage(image));
//        ui->picture->setBackgroundRole(QPalette::Dark);
//        ui->picture->autoFillBackground();
        char buffer[100];
        sprintf(buffer, "0/0\n");
        QString s(buffer);
        ui->index->setText(s);
        return;

    }
    if (iter == pics.end() && pics.end() != pics.begin())
    {
        iter = pics.end() - 1;
    }

    ui->picture->setPixmap(QPixmap::fromImage(*iter));

    int cur = iter - pics.begin();
    cur++;
    char buffer[100];
    sprintf(buffer, "%d/%d\n", cur, pics.size());
    QString s(buffer);
    ui->index->setText(s);
}
