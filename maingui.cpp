#include "maingui.h"
#include <iostream>

mainGui::mainGui(QWidget *parent) :
     QWidget(parent)
{
    this->showMaximized();
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setWindowTitle("Tiny NDVI");
    QGridLayout *mainLayout = new QGridLayout;

    ndviProcessor *processor = new ndviProcessor;
    ndviProcessor& _refToProcessor = *processor;
    inputGui = new inputImageGui(_refToProcessor);

    pageSelector = new QTabWidget;
    pageSelector->addTab(inputGui, "Input Images");

    mainLayout->addWidget(pageSelector);

    setLayout(mainLayout);

    QObject::connect(processor, SIGNAL(processStarted()), this, SLOT(createOutputImageTab()));
    QObject::connect(processor, SIGNAL(sendFilePath(string)), this, SLOT(storeNdviFilePath(string)));
}

void mainGui::createOutputImageTab()
{
    outputImageGui *outputImage = new outputImageGui;
    tabList.push_back(outputImage);
    pageSelector->addTab(outputImage, "Output Image");
    pageSelector->setCurrentIndex(pageSelector->indexOf(outputImage));
}

void mainGui::storeNdviFilePath(string filePath)
{
    ndviImageFilePath = filePath;
    loadNdviOutputImage();
}

void mainGui::loadNdviOutputImage()
{
    outputImageGui* outputImage = tabList.last();
    outputImage->loadNdviImage(ndviImageFilePath);
}

