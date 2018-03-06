#ifndef NDVIWORKERTHREAD_H
#define NDVIWORKERTHREAD_H

#include <QObject>
#include <QThread>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
using namespace cv;
Q_DECLARE_METATYPE(string)

class ndviWorkerThread : public QThread
{
    Q_OBJECT
    void run() override
    {
        //scanRedImage();
        //scanNirImage();
        generateNdviImage();
    }

public:
    ndviWorkerThread();
    void setRedInputImage(string);
    void setNirInputImage(string);
    void setNumRows(int);
    void setNumCols(int);

signals:
    void sendFilePathFromWorker(string);

public slots:

private:

    int nRows = 0, nCols = 0;
    Mat redBandImage, nirBandImage;
    string redBandFilePath, nirBandFilePath, ndviImageFilePath;
    vector<vector<double>> redPixelTable{ { 0 } };
    vector<vector<double>> nirPixelTable{ { 0 } };
    vector<vector<double>> ndviPixelTable{ { 0 } };

    void ndviWorkerProcessingFinished();
    //void scanRedImage();
    //void scanNirImage();
    void generateNdviImage();

};

#endif // NDVIWORKERTHREAD_H
