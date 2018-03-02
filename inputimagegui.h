#ifndef INPUTIMAGEGUI_H
#define INPUTIMAGEGUI_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QComboBox>
#include <QFileDialog>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QPixmap>
#include <QProgressBar>
#include <string>
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
    int pixPerRowRed, pixPerColRed, totalPixRed, numChannelsRed;
    int pixPerRowNir, pixPerColNir, totalPixNir, numChannelsNir;
    QComboBox *sourceSatelliteList;
    QPlainTextEdit *inputExceptionsDisplay;

    QPushButton *createButton(const QString& text);
    QLineEdit *createLineEdit(const QString& text);
    QLabel *createLabelDisplay();
    QComboBox *createComboBox();
    QPlainTextEdit *createTextEdit();

    //Mat redImage, nirImage;
    int nRowsRed, nColsRed, nRowsNir, nColsNir, nRowsFinal, nColsFinal;

    void checkForInputErrors();

};

#endif // INPUTIMAGEGUI_H
