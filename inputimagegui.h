#ifndef INPUTIMAGEGUI_H
#define INPUTIMAGEGUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QDialog>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPixmap>
#include <string>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ndviprocessor.h"

using namespace std;

class inputImageGui : public QWidget
{
    Q_OBJECT
public:
    inputImageGui(ndviProcessor&, QWidget *parent = nullptr);
    ndviProcessor& _refToProcessorInInput;

public slots:
    void loadRedImage();
    void loadNirImage();
    void processImages();

private:
    QPushButton *loadRedImageButton, *loadNirImageButton, *processButton;
    QLabel *redBandImageDisplay, *nirBandImageDisplay;
    QPixmap *redBandImage, *nirBandImage;
    QLineEdit *pixPerRowRed, *pixPerColRed, *totalPixRed, *fileImageBandRed;
    QLineEdit *pixPerRowNir, *pixPerColNir, *totalPixNir, *fileImageBandNir;
    QComboBox *sourceSatelliteList;
    QPlainTextEdit *inputExceptionsDisplay;

    QPushButton *createButton(const QString& text);
    QLineEdit *createLineEdit(const QString& text);
    QLabel *createLabelDisplay();
    QComboBox *createComboBox();
    QPlainTextEdit *createTextEdit();

    Mat redImage, nirImage;
    int nRowsRed, nColsRed, nRowsNir, nColsNir, nRowsFinal, nColsFinal;

    void checkSourceSatellite();
    bool checkSourceBands();
    void checkForInputErrors();

};

#endif // INPUTIMAGEGUI_H
