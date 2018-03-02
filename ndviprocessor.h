#ifndef NDVIPROCESSOR_H
#define NDVIPROCESSOR_H

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <string>
#include <QObject>
#include "outputimagegui.h"

using namespace std;
using namespace cv;

class ndviProcessor : public QObject
{
    Q_OBJECT

public:
    ndviProcessor(QObject *parent = 0);

    void setRedInputImage(string);
    void setNirInputImage(string);
    void clearRedInputImage();
    void clearNirInputImage();
    string getRedBandImagePath();
    string getNirBandImagePath();
    int getRedBandRows();
    int getRedBandCols();
    int getRedBandTotalPix();
    int getRedBandChannels();
    int getNirBandRows();
    int getNirBandCols();
    int getNirBandTotalPix();
    int getNirBandChannels();
    void processImages();

    bool checkIfRowsMatch();
    bool checkIfColsMatch();
    bool checkIfTotalPixMatch();
    bool checkRedSingleChannel();
    bool checkNirSingleChannel();
    bool checkIfFileTypesMatch();

signals:
    void processStarted();
    void sendFilePath(string);

public slots:

private:
    Mat redBandImage, nirBandImage, ndviImage;
    string redBandFilePath, nirBandFilePath, ndviImageFilePath, trueColorImageFilePath;
    int nCols = 0, nRows = 0;
    vector<vector<double>> redPixelTable{ { 0 } };
    vector<vector<double>> nirPixelTable{ { 0 } };
    vector<vector<double>> ndviPixelTable{ { 0 } };

    void scanRedImage();
    void scanNirImage();
    void generateNdviImage();
    void processingStarted();
    void ndviProcessingFinished();
    void trueColorProcessingFinished();
};

#endif // NDVIPROCESSOR_H
