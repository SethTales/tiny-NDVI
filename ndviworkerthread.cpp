#include "ndviworkerthread.h"

ndviWorkerThread::ndviWorkerThread()
{

}
void ndviWorkerThread::setRedInputImage(string _redBandFilePath)
{
    redBandFilePath = _redBandFilePath;
    String cv_redBandFilePath(redBandFilePath);
    redBandImage = imread(cv_redBandFilePath, IMREAD_GRAYSCALE);
}

void ndviWorkerThread::setNirInputImage(string _nirBandFilePath)
{
    nirBandFilePath = _nirBandFilePath;
    String cv_nirBandFilePath(nirBandFilePath);
    nirBandImage = imread(cv_nirBandFilePath, IMREAD_GRAYSCALE);
}

void ndviWorkerThread::setNumRows(int _nRows)
{
    nRows = _nRows;
}
void ndviWorkerThread::setNumCols(int _nCols)
{
    nCols = _nCols;
}

void ndviWorkerThread::generateNdviImage()
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
    ndviWorkerProcessingFinished();
}
void ndviWorkerThread::ndviWorkerProcessingFinished()
{
    qRegisterMetaType<string>("ndviImageFilePath");
    emit sendFilePathFromWorker(ndviImageFilePath);
}
