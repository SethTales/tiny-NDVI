#include "outputimagegui.h"

outputImageGui::outputImageGui(QWidget *parent) :
    QWidget(parent)
{
    //this->setSizePolicy(QSizePolicy::Preferred);

    saveButton = createButton("Save");
    saveAsButton = createButton("Save As");

    outputImageDisplay = createLabelDisplay();
    outputImageDisplay->setFixedSize(1450, 900);
    ndviKey = createLabelDisplay();
    ndviKey->setFixedSize(500, 50);

    outputLayout = new QGridLayout;
    outputLayout->addWidget(outputImageDisplay, 4, 4, 40, 40, Qt::AlignCenter);
    outputLayout->addWidget(saveButton, 9, 41, 1, 4);
    outputLayout->addWidget(saveAsButton, 12, 41, 1, 4);
    outputLayout->addWidget(ndviKey, 46, 21, 1, 8, Qt::AlignBottom);
    progressBar = createProgressBar();
    outputLayout->addWidget(progressBar, 22, 23, 1, 4, Qt::AlignCenter);

    setLayout(outputLayout);

    QObject::connect(saveAsButton, SIGNAL(clicked()), this, SLOT(saveAsButtonClicked()));
}

QPushButton *outputImageGui::createButton(const QString& text)
{
    QPushButton *button = new QPushButton;
    button->setText(text);
    button->setFixedSize(120, 30);
    return button;
}

QLabel *outputImageGui::createLabelDisplay()
{
    QLabel *labelDisplay = new QLabel;
    labelDisplay->setFrameStyle(QFrame::Box | QFrame::Sunken);
    labelDisplay->setLineWidth(2);
    labelDisplay->setScaledContents(true);
    return labelDisplay;
}

QProgressBar *outputImageGui::createProgressBar()
{
    QProgressBar *progressBar = new QProgressBar;
    progressBar->setFixedSize(250, 50);
    progressBar->setMinimum(0);
    progressBar->setMaximum(0);
    return progressBar;
}

void outputImageGui::loadNdviImage(std::string fileName)
{
    progressBar->hide();
    QString qFileName = QString::fromStdString(fileName);
    QPixmap pix;
    pix.load(qFileName);
    outputImageDisplay->setPixmap(pix);
}

void outputImageGui::saveAsButtonClicked()
{
    QString saveFileName = QFileDialog::getSaveFileName(this, "Save File", "/home/seth/Documents/LandSat Images/untitled.tif",
                                                        "Images (*.tif, *.tiff, *.TIF, *.TIFF)");

    if (saveFileName.isEmpty())
    {
        return;
    }
    else
    {
        QImage image = outputImageDisplay->pixmap()->toImage();
        image.save(saveFileName);
    }
}

void outputImageGui::saveButtonClicked()
{

}
