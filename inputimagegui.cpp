#include "inputimagegui.h"
#include <iostream>

using namespace std;
using namespace cv;

inputImageGui::inputImageGui(ndviProcessor &_refToProcessorInConst, QWidget *parent) :
    _refToProcessorInInput(_refToProcessorInConst), QWidget(parent)
{
    //std::cout << &_refToProcessorInInput << std::endl;

    //this->setSizePolicy(QSizePolicy::Preferred);

    loadRedImageButton = createButton("Load Red Image");
    loadNirImageButton = createButton("Load NIR Image");
    processButton = createButton("Process Images");

    pixPerRowRed = createLineEdit("Pixels Per Row");
    pixPerColRed = createLineEdit("Pixels Per Column");
    totalPixRed = createLineEdit("Total Pixels");
    fileImageBandRed = createLineEdit("Spectral Band");

    pixPerRowNir = createLineEdit("Pixels Per Row");
    pixPerColNir = createLineEdit("Pixels Per Column");
    totalPixNir = createLineEdit("Total Pixels");
    fileImageBandNir = createLineEdit("Spectral Band");

    redBandImageDisplay = createLabelDisplay();
    nirBandImageDisplay = createLabelDisplay();

    sourceSatelliteList = createComboBox();

    inputExceptionsDisplay = createTextEdit();


    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(loadRedImageButton, 0, 0, 1, 4);
    inputLayout->addWidget(loadNirImageButton, 13, 0, 1, 4);
    inputLayout->addWidget(processButton, 13, 28, 1, 4);
    inputLayout->setAlignment(processButton, Qt::AlignRight);
    inputLayout->addWidget(redBandImageDisplay, 1, 0, 12, 12);
    inputLayout->addWidget(nirBandImageDisplay, 20, 0, 12, 12);
    inputLayout->addWidget(pixPerRowRed, 1, 8, 1, 1);
    inputLayout->addWidget(pixPerColRed, 3, 8, 1, 1);
    inputLayout->addWidget(totalPixRed, 5, 8, 1, 1);
    inputLayout->addWidget(fileImageBandRed, 7, 8, 1, 1);
    inputLayout->addWidget(pixPerRowNir, 20, 8, 1, 1);
    inputLayout->addWidget(pixPerColNir, 22, 8, 1, 1);
    inputLayout->addWidget(totalPixNir, 24, 8, 1, 1);
    inputLayout->addWidget(fileImageBandNir, 26, 8, 1, 1);
    inputLayout->addWidget(sourceSatelliteList, 13, 25, 1, 8);
    inputLayout->addWidget(inputExceptionsDisplay, 20, 20, 0, 0);

    setLayout(inputLayout);

    QObject::connect(loadRedImageButton, SIGNAL(clicked()), this, SLOT(loadRedImage()));
    QObject::connect(loadNirImageButton, SIGNAL(clicked()), this, SLOT(loadNirImage()));
    QObject::connect(processButton, SIGNAL(clicked()), this, SLOT(processImages()));

}

QPushButton *inputImageGui::createButton(const QString& text)
{
    QPushButton *button = new QPushButton;
    button->setText(text);
    button->setFixedSize(120, 30);
    return button;
}

QLineEdit *inputImageGui::createLineEdit(const QString& text)
{
    QLineEdit *lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText(text);
    lineEdit->setFixedWidth(250);
    return lineEdit;
}

QLabel *inputImageGui::createLabelDisplay()
{
    QLabel *labelDisplay = new QLabel;
    labelDisplay->setFixedSize(650, 450);
    labelDisplay->setFrameStyle(QFrame::Box | QFrame::Sunken);
    labelDisplay->setLineWidth(2);
    labelDisplay->setScaledContents(true);
    return labelDisplay;
}

QComboBox *inputImageGui::createComboBox()
{
    QStringList satellites;
    satellites << "Landsat 1-5, MSS" << "Landsat 4-5, TM" << "Landsat 7, ETM+" << "Landsat 8, OLI/TIRS";
    QComboBox *comboBox = new QComboBox;
    comboBox->addItems(satellites);
    comboBox->setFixedWidth(250);
    return comboBox;
}

QPlainTextEdit *inputImageGui::createTextEdit()
{
    QPlainTextEdit *textEdit = new QPlainTextEdit;
    textEdit->setFixedSize(600, 400);
    textEdit->setReadOnly(true);
    return textEdit;
}

void inputImageGui::loadRedImage()
{
    const QString& redBandFileName = QFileDialog::getOpenFileName(this, "Open Image", "/home/seth/Documents/LandSat Images", "Image Files (*.tiff, *.tif, *.TIF)");
    _refToProcessorInInput.setRedInputImage(redBandFileName.toStdString());
    QPixmap pix;
    pix.load(QString::fromStdString(_refToProcessorInInput.getRedBandImagePath()));

    pixPerRowRed->setText(QString::fromStdString((to_string(_refToProcessorInInput.getRedBandRows()))));
    pixPerColRed->setText(QString::fromStdString((to_string(_refToProcessorInInput.getRedBandCols()))));
    totalPixRed->setText(QString::fromStdString((to_string(_refToProcessorInInput.getRedBandTotalPix()))));

    redBandImageDisplay->setPixmap(pix);
}

void inputImageGui::loadNirImage()
{
    const QString& nirBandFileName = QFileDialog::getOpenFileName(this, "Open Image", "/home/seth/Documents/LandSat Images", "Image Files (*.tiff, *.tif, *.TIF)");
    _refToProcessorInInput.setNirInputImage(nirBandFileName.toStdString());
    QPixmap pix;
    pix.load(QString::fromStdString(_refToProcessorInInput.getNirBandImagePath()));

    pixPerRowNir->setText(QString::fromStdString((to_string(_refToProcessorInInput.getNirBandRows()))));
    pixPerColNir->setText(QString::fromStdString((to_string(_refToProcessorInInput.getNirBandCols()))));
    totalPixNir->setText(QString::fromStdString((to_string(_refToProcessorInInput.getNirBandTotalPix()))));

    nirBandImageDisplay->setPixmap(pix);
}

void inputImageGui::checkForInputErrors()
{

}

void inputImageGui::processImages()
{
    _refToProcessorInInput.processImages();
}

void inputImageGui::checkSourceSatellite()
{

}

bool inputImageGui::checkSourceBands()
{

}


