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
#include "outputimagegui.h"

using namespace std;
using namespace cv;

class ndviProcessor
{
public:
    ndviProcessor(outputImageGui&);
    outputImageGui& _refToOutputInProcessor;
    void setRedInputImage(string);
    void setNirInputImage(string);
    string getRedBandImagePath();
    string getNirBandImagePath();
    int getRedBandRows();
    int getRedBandCols();
    int getRedBandTotalPix();
    int getNirBandRows();
    int getNirBandCols();
    int getNirBandTotalPix();
    void processImages();

private:
    Mat redBandImage, nirBandImage, ndviImage;
    string redBandFilePath, nirBandFilePath;
    int nCols = 0, nRows = 0;
    vector<vector<double>> redPixelTable{ { 0 } };
    vector<vector<double>> nirPixelTable{ { 0 } };
    vector<vector<double>> ndviPixelTable{ { 0 } };

    void scanRedImage();
    void scanNirImage();
    void generateNdviImage();
};

#endif // NDVIPROCESSOR_H
