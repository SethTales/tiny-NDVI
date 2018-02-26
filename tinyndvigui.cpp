#include "tinyndvigui.h"

tinyNDVIgui::tinyNDVIgui(QWidget *parent) :
     QWidget(parent)
{
    this->showMaximized();
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setWindowTitle("Tiny NDVI");
    QGridLayout *mainLayout = new QGridLayout;

    outputGui = new outputImageGui;
    outputImageGui& _refToOutputGui = *outputGui;
    ndviProcessor *processor = new ndviProcessor(_refToOutputGui);
    ndviProcessor& _refToProcessor = *processor;
    inputGui = new inputImageGui(_refToProcessor);

    pageSelector = new QTabWidget;
    pageSelector->addTab(inputGui, "Input Images");
    pageSelector->addTab(outputGui, "Output Image");

    mainLayout->addWidget(pageSelector);

    setLayout(mainLayout);
}
