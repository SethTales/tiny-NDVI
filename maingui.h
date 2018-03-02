#ifndef MAINGUI_H
#define MAINGUI_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGridLayout>
#include <QProgressBar>
#include <string>
#include <vector>
#include "inputimagegui.h"
#include "outputimagegui.h"
#include "ndviprocessor.h"

using namespace std;

class mainGui : public QWidget
{
    Q_OBJECT
public:
    explicit mainGui(QWidget *parent = nullptr);
    //ndviProcessor& _refToProcessorInMainGui;

signals:

public slots:

    void createOutputImageTab();
    void storeNdviFilePath(string);


private:
    QTabWidget *pageSelector;
    QVector <outputImageGui*> tabList;

    inputImageGui *inputGui;

    string ndviImageFilePath;

    void loadNdviOutputImage();

};

#endif // MAINGUI_H
