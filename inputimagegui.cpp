#include "inputimagegui.h"
#include <iostream>

using namespace std;
using namespace cv;

inputImageGui::inputImageGui(ndviProcessor &_refToProcessorInConst, QWidget *parent) :
    _refToProcessorInInput(_refToProcessorInConst), QWidget(parent)
{
    loadRedImageButton = createButton("Load Red Image");
    loadNirImageButton = createButton("Load NIR Image");
    processButton = createButton("Process Images");

    redBandImageDisplay = createLabelDisplay();
    nirBandImageDisplay = createLabelDisplay();

    processType = createComboBox();

    inputExceptionsDisplay = createTextEdit();


    QGridLayout *inputLayout = new QGridLayout;
    inputLayout->addWidget(loadRedImageButton, 0, 0, 1, 4);
    inputLayout->addWidget(loadNirImageButton, 13, 0, 1, 4);
    inputLayout->addWidget(processButton, 13, 28, 1, 4);
    inputLayout->setAlignment(processButton, Qt::AlignRight);
    inputLayout->addWidget(redBandImageDisplay, 1, 0, 12, 12);
    inputLayout->addWidget(nirBandImageDisplay, 20, 0, 12, 12);
    inputLayout->addWidget(processType, 13, 25, 1, 8);
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
    QStringList outputImageTypes;
    outputImageTypes << "NDVI" << "True Color" << "NDWI";
    QComboBox *comboBox = new QComboBox;
    comboBox->addItems(outputImageTypes);
    comboBox->setFixedWidth(250);
    return comboBox;
}

QPlainTextEdit *inputImageGui::createTextEdit()
{
    QPlainTextEdit *textEdit = new QPlainTextEdit;
    textEdit->setPlaceholderText("Input Image Validation");
    textEdit->setFixedSize(600, 400);
    textEdit->setReadOnly(true);
    return textEdit;
}

void inputImageGui::loadRedImage()
{
    inputExceptionsDisplay->clear();
    _refToProcessorInInput.clearRedInputImage();
    const QString& redBandFileName = QFileDialog::getOpenFileName(this, "Open Image", "/home/seth/Documents/LandSat Images", "Image Files (*.tif, *.TIF)");
    _refToProcessorInInput.setRedInputImage(redBandFileName.toStdString());
    QPixmap pix;
    pix.load(QString::fromStdString(_refToProcessorInInput.getRedBandImagePath()));

    pixPerRowRed = _refToProcessorInInput.getRedBandRows();
    pixPerColRed = _refToProcessorInInput.getRedBandCols();
    totalPixRed = _refToProcessorInInput.getRedBandTotalPix();
    numChannelsRed = _refToProcessorInInput.getRedBandChannels();

    redBandImageDisplay->setPixmap(pix);
    checkForInputErrors();
}

void inputImageGui::loadNirImage()
{
    inputExceptionsDisplay->clear();
    _refToProcessorInInput.clearNirInputImage();
    const QString& nirBandFileName = QFileDialog::getOpenFileName(this, "Open Image", "/home/seth/Documents/LandSat Images", "Image Files (*.tif, *.TIF)");
    _refToProcessorInInput.setNirInputImage(nirBandFileName.toStdString());
    QPixmap pix;
    pix.load(QString::fromStdString(_refToProcessorInInput.getNirBandImagePath()));

    pixPerRowNir = _refToProcessorInInput.getNirBandRows();
    pixPerColNir = _refToProcessorInInput.getNirBandCols();
    totalPixNir = _refToProcessorInInput.getNirBandTotalPix();
    numChannelsNir = _refToProcessorInInput.getNirBandChannels();

    nirBandImageDisplay->setPixmap(pix);
    checkForInputErrors();
}

void inputImageGui::checkForInputErrors()
{
    inputExceptionsDisplay->clear();

    QString waiting = "Waiting for second image";
    QString colException = "WARNING: Images have different number of columns";
    QString colMatch = "Images have same number of columns";
    QString rowException = "WARNING: Images have different number of rows";
    QString rowMatch = "Images have same number of rows";
    QString totalPixException = "WARNING: Images have different number of total pixels";
    QString totalPixMatch = "Images have same number of total pixels";
    QString redChannelException = "WARNING: Red band image has greater than 1 channel";
    QString redChannelMatch = "Red band image is single channel";
    QString nirChannelException = "WARNING: Nir band image has greater than 1 channel";
    QString nirChannelMatch = "Nir band image is single channel";
    QString fileTypeException = "WARNING: Images have different file extensions";
    QString fileTypeMatch = "Images have the same file extensions";

    if (redBandImageDisplay->pixmap() == 0 || nirBandImageDisplay->pixmap() == 0)
    {
        inputExceptionsDisplay->clear();
        inputExceptionsDisplay->appendPlainText(waiting);
        return;
    }

    if (_refToProcessorInInput.checkIfColsMatch() == false)
    {
        inputExceptionsDisplay->appendPlainText(colException);
    }

    else if (_refToProcessorInInput.checkIfColsMatch() == true)
    {
        inputExceptionsDisplay->appendPlainText(colMatch);
    }

    if (_refToProcessorInInput.checkIfRowsMatch() == false)
    {
        inputExceptionsDisplay->appendPlainText(rowException);
    }

    else if (_refToProcessorInInput.checkIfRowsMatch() == true)
    {
        inputExceptionsDisplay->appendPlainText(rowMatch);
    }

    if (_refToProcessorInInput.checkIfTotalPixMatch() == false)
    {
        inputExceptionsDisplay->appendPlainText(totalPixException);
    }

    else if (_refToProcessorInInput.checkIfTotalPixMatch() == true)
    {
        inputExceptionsDisplay->appendPlainText(totalPixMatch);
    }

    if (_refToProcessorInInput.checkRedSingleChannel() == false)
    {
        inputExceptionsDisplay->appendPlainText(redChannelException);
    }

    else if (_refToProcessorInInput.checkRedSingleChannel() == true)
    {
        inputExceptionsDisplay->appendPlainText(redChannelMatch);
    }

    if (_refToProcessorInInput.checkNirSingleChannel() == false)
    {
        inputExceptionsDisplay->appendPlainText(nirChannelException);
    }

    else if (_refToProcessorInInput.checkNirSingleChannel() == true)
    {
        inputExceptionsDisplay->appendPlainText(nirChannelMatch);
    }

    if (_refToProcessorInInput.checkIfFileTypesMatch() == false)
    {
        inputExceptionsDisplay->appendPlainText(fileTypeException);
    }

    else if (_refToProcessorInInput.checkIfFileTypesMatch() == true)
    {
        inputExceptionsDisplay->appendPlainText(fileTypeMatch);
    }

}
void inputImageGui::processImages()
{
    if (redBandImageDisplay->pixmap() == 0 || nirBandImageDisplay->pixmap() == 0)
    {
        QMessageBox *messageBox = new QMessageBox;
        messageBox->setWindowTitle("Process Aborted");
        messageBox->setText("Cannot process without two images. Please load images to continue.");
        messageBox->setIcon(QMessageBox::Critical);
        messageBox->exec();
        return;
    }

    _refToProcessorInInput.createProcessingThreads();
}


