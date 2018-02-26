#include "ndviprocessor.h"
#include <iostream>

ndviProcessor::ndviProcessor(outputImageGui& _refToOutputInConst) :
    _refToOutputInProcessor(_refToOutputInConst)
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

void ndviProcessor::processImages()
{
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
            if (ndviPixelTable[r][c] >= -1 && ndviPixelTable[r][c] <= -0.2)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = 0;
                ndviImage.at<Vec3b>(r, c)[2] = 0;
            }

            //make these pixels light red to dark red
            else if (ndviPixelTable[r][c] >= -0.2 && ndviPixelTable[r][c] < 0.1)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = 0;
                ndviImage.at<Vec3b>(r, c)[2] = (255 - ((ndviPixelTable[r][c] - -0.2) / 0.002));
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
                ndviImage.at<Vec3b>(r, c)[0] = (188 - ((ndviPixelTable[r][c] - 0.4) / 0.003333333));
                ndviImage.at<Vec3b>(r, c)[1] = (255 - ((ndviPixelTable[r][c] - 0.4) / 0.002));
                ndviImage.at<Vec3b>(r, c)[2] = 0;
            }

            //make these pixels light green to dark green
            else if (ndviPixelTable[r][c] >= 0.7 && ndviPixelTable[r][c] <= 1)
            {
                ndviImage.at<Vec3b>(r, c)[0] = 0;
                ndviImage.at<Vec3b>(r, c)[1] = (205 - (ndviPixelTable[r][c] - 0.7) / 0.002);
                ndviImage.at<Vec3b>(r, c)[2] = 0;
            }
        }
    }

    string fileName = "/home/seth/Documents/qt_projects/tiny_NDVI/temp_images/temp.tif";
    imwrite(fileName, ndviImage);
    _refToOutputInProcessor.loadNdviImage(fileName);
}
