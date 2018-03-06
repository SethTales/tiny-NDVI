#include "ndviprocessor.h"
#include <iostream>

ndviProcessor::ndviProcessor(QObject *parent) :
    QObject(parent)
{
    redBandFilePath = "";
    nirBandFilePath = "";
}

void ndviProcessor::setRedInputImage(string _redBandFilePath)
{
    redBandFilePath = _redBandFilePath;
    String cv_redBandFilePath(redBandFilePath);
    redBandImage = imread(cv_redBandFilePath, IMREAD_GRAYSCALE);
}

void ndviProcessor::setNirInputImage(string _nirBandFilePath)
{
    nirBandFilePath = _nirBandFilePath;
    String cv_nirBandFilePath(nirBandFilePath);
    nirBandImage = imread(cv_nirBandFilePath, IMREAD_GRAYSCALE);
}

void ndviProcessor::clearRedInputImage()
{
    redBandFilePath = "";
    redBandImage.release();
}

void ndviProcessor::clearNirInputImage()
{
    nirBandFilePath = "";
    nirBandImage.release();
}

string ndviProcessor::getRedBandImagePath()
{
    return redBandFilePath;
}

string ndviProcessor::getNirBandImagePath()
{
    return nirBandFilePath;
}

int ndviProcessor::getRedBandRows()
{
    int nRowsRed = redBandImage.rows;
    nRows = nRowsRed;
    return nRowsRed;
}

int ndviProcessor::getRedBandCols()
{
    int nColsRed = redBandImage.cols;
    nCols = nColsRed;
    return nColsRed;
}

int ndviProcessor::getRedBandTotalPix()
{
    int nRedPixTotal = redBandImage.total();
    return nRedPixTotal;
}

int ndviProcessor::getRedBandChannels()
{
    int nRedChannels = redBandImage.channels();
    return nRedChannels;
}

int ndviProcessor::getNirBandRows()
{
    int nRowsNir = nirBandImage.rows;
    return nRowsNir;
}

int ndviProcessor::getNirBandCols()
{
    int nColsNir = nirBandImage.cols;
    return nColsNir;
}

int ndviProcessor::getNirBandTotalPix()
{
    int nNirPixTotal = nirBandImage.total();
    return nNirPixTotal;
}

int ndviProcessor::getNirBandChannels()
{
    int nNirChannels = nirBandImage.channels();
    return nNirChannels;
}

bool ndviProcessor::checkIfRowsMatch()
{
    if (getRedBandRows() == getNirBandRows())
    {
        nRows = getRedBandRows();
        return true;
    }

    else
    {
        return false;
    }
}

bool ndviProcessor::checkIfColsMatch()
{
    if (getRedBandCols() == getNirBandCols())
    {
        nCols = getRedBandCols();
        return true;
    }

    else
    {
        return false;
    }
}

bool ndviProcessor::checkIfTotalPixMatch()
{
    if ((getRedBandCols() * getRedBandRows()) == (getNirBandCols() * getNirBandRows()))
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool ndviProcessor::checkRedSingleChannel()
{
    if (getRedBandChannels() == 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool ndviProcessor::checkNirSingleChannel()
{
    if (getNirBandChannels() == 1)
    {
        return true;
    }

    else
    {
        return false;
    }
}

bool ndviProcessor::checkIfFileTypesMatch()
{
    int redFilePathLength = redBandFilePath.length();
    int nirFilePathLength = nirBandFilePath.length();
    string tempRedFileExt;
    string tempNirFileExt;
    string redFileExt;
    string nirFileExt;

    for (int i = (redFilePathLength - 1); i > (redFilePathLength - 5); --i)
    {
        tempRedFileExt += redBandFilePath[i];
    }

    for (int i = (nirFilePathLength - 1); i > (nirFilePathLength - 5); --i)
    {
        tempNirFileExt += redBandFilePath[i];
    }

    for (int i = 3; i >= 0; --i)
    {
        redFileExt += tempRedFileExt[i];
        nirFileExt += tempNirFileExt[i];
    }

    if (redFileExt == nirFileExt)
    {
        return true;
    }

    else
    {
        return false;
    }

}

void ndviProcessor::processingStarted()
{
    emit processStarted();
}

void ndviProcessor::createProcessingThreads()
{

    processingStarted();
    ndviWorkerThread *workerThread = new ndviWorkerThread;
    workerThread->setNirInputImage(nirBandFilePath);
    workerThread->setRedInputImage(redBandFilePath);
    workerThread->setNumRows(nRows);
    workerThread->setNumCols(nCols);
    qRegisterMetaType<string>();
    QObject::connect(workerThread, SIGNAL(sendFilePathFromWorker(string)), this, SLOT(storeNdviFilePath(string)), Qt::QueuedConnection);
    QObject::connect(workerThread, &ndviWorkerThread::finished, workerThread, &QObject::deleteLater);
    QObject::connect(workerThread, SIGNAL(finished()), this, SLOT(ndviProcessingFinished()));
    workerThread->start();

}

void ndviProcessor::storeNdviFilePath(string filePath)
{
    ndviImageFilePath = filePath;
}

void ndviProcessor::ndviProcessingFinished()
{
    qRegisterMetaType<string>("ndviImageFilePath");
    emit sendFilePath(ndviImageFilePath);
}

void ndviProcessor::trueColorProcessingFinished()
{
    emit sendFilePath(trueColorImageFilePath);
}
