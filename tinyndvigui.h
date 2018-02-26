#ifndef TINYNDVIGUI_H
#define TINYNDVIGUI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPushButton>
#include <QLineEdit>
#include "inputimagegui.h"
#include "outputimagegui.h"
#include "ndviprocessor.h"

class tinyNDVIgui : public QWidget
{
    Q_OBJECT
public:
    explicit tinyNDVIgui(QWidget *parent = nullptr);
    //ndviProcessor& _refToProcessorInMainGui;

signals:

public slots:

    //void open();
    //void process();
    //void save();
    //void saveAs();

private:
    QTabWidget *pageSelector;
    QWidget *redBandPage, *nirBandPage, *processingParametersPage, *ndviOutputPage;
    QLabel *redBandImage, *nirBandImage, *ndviOutputImage, *ndviOutputRange;
    QPushButton *openButton, *processButton, *saveButton, *saveAsButton;
    QLineEdit *redImagePath, *nirImagePath, *numPixelsRed, *numPixelsNIR;

    outputImageGui *outputGui;
    inputImageGui *inputGui;

};

#endif // TINYNDVIGUI_H
