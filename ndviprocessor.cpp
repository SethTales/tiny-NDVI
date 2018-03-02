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

void ndviProcessor::processImages()
{
    processingStarted();
    scanRedImage();
    scanNirImage();
    generateNdviImage();
}

void ndviProcessor::scanRedImage()
{
    for (uint r = 0; r < nRows; ++r)
    {
        redPixelTable.push_back(vector<double>());
        {
            for (uint c = 0; c < nCols; ++c)
            {
                redPixelTable[r].push_back(c);
                redPixelTable[r][c] = redBandImage.at<uchar>(r, c);
            }
        }
    }


}

void ndviProcessor::scanNirImage()
{
    for (uint r = 0; r < nRows; ++r)
    {
        nirPixelTable.push_back(vector<double>());
        {
            for (uint c = 0; c < nCols; ++c)
            {
                nirPixelTable[r].push_back(c);
                nirPixelTable[r][c] = nirBandImage.at<uchar>(r, c);
            }
        }
    }
}

void ndviProcessor::generateNdviImage()
{
    Mat ndviImage(nRows, nCols, CV_8UC3);

    for (int r = 0; r < nRows; ++r)
    {
        ndviPixelTable.push_back(vector<double>());
        for (int c = 0; c < nCols; ++c)
        {
            ndviPixelTable[r].push_back(c);
            if ((nirPixelTable[r][c]) + (redPixelTable[r][c]) == 0)
            {
                ndviPixelTable[r][c] = 0;
                continue;
            }

            else
            {
                ndviPixelTable[r][c] = (((nirPixelTable[r][c]) - (redPixelTable[r][c]))
                                    / ((nirPixelTable[r][c]) + (redPixelTable[r][c])));

            }
        }
    }

    for(int r = 0; r < nRows; ++r)
    {
        for(int c = 0; c < nCols; ++c)
        {
            //make these pixels black
            if (ndviPixelTable[r][c] >= -1 && ndviPixelTable[r][c] <= -0.3)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = 0;
                ndviImage.at<Vec3b>(r, c)[2] = 0;
            }

            //make these pixels light red to dark red
            else if (ndviPixelTable[r][c] >= -0.3 && ndviPixelTable[r][c] < 0.1)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = 0;
                ndviImage.at<Vec3b>(r, c)[2] = (225 - ((ndviPixelTable[r][c] - -0.3) / 0.002));
            }

            //make these pixels light yellow to dark yellow
            else if (ndviPixelTable[r][c] >= 0.1 && ndviPixelTable[r][c] < 0.4)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = (255 - ((ndviPixelTable[r][c] - 0.1) / 0.002));
                ndviImage.at<Vec3b>(r, c)[2] = (255 - ((ndviPixelTable[r][c] - 0.1) / 0.002));
            }

            //make these pixels light blue to dark blue
            else if (ndviPixelTable[r][c] >= 0.4 && ndviPixelTable[r][c] < 0.7)
            {
                ndviImage.at<Vec3b>(r, c)[0] = (80 - ((ndviPixelTable[r][c] - 0.4) / 0.003));
                ndviImage.at<Vec3b>(r, c)[1] = (200 - ((ndviPixelTable[r][c] - 0.4) / 0.002));
                ndviImage.at<Vec3b>(r, c)[2] = (100 - ((ndviPixelTable[r][c] - 0.4) / 0.003));
            }

            //make these pixels light green to dark green
            else if (ndviPixelTable[r][c] >= 0.7 && ndviPixelTable[r][c] <= 1)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = (200 - (ndviPixelTable[r][c] - 0.7) / 0.003);
                ndviImage.at<Vec3b>(r, c)[2] = (60 - (ndviPixelTable[r][c] - 0.7) / 0.003);;
            }
        }
    }

    string filePath = "/home/seth/Documents/qt_projects/tiny_NDVI/temp_images/temp.tif";
    imwrite(filePath, ndviImage);
    ndviImageFilePath = filePath;
    ndviProcessingFinished();
}

void ndviProcessor::processingStarted()
{
    emit processStarted();
}

void ndviProcessor::ndviProcessingFinished()
{
    emit sendFilePath(ndviImageFilePath);
}

void ndviProcessor::trueColorProcessingFinished()
{
    emit sendFilePath(trueColorImageFilePath);
}
