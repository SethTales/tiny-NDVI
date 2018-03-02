#include "outputimagegui.h"

outputImageGui::outputImageGui(QWidget *parent) :
    QWidget(parent)
{
    //this->setSizePolicy(QSizePolicy::Preferred);

    openButton = createButton("Open");
    saveButton = createButton("Save");
    saveAsButton = createButton("Save As");

    outputImageDisplay = createLabelDisplay();
    outputImageDisplay->setFixedSize(1450, 900);
    ndviKey = createLabelDisplay();
    ndviKey->setFixedSize(500, 50);

    imageProcessProgressBar = createProgressBar();
    imageProcessProgressBar->hide();

    QGridLayout *outputLayout = new QGridLayout;
    outputLayout->addWidget(outputImageDisplay, 4, 4, 40, 40, Qt::AlignCenter);
    outputLayout->addWidget(openButton, 6, 41, 1, 4);
    outputLayout->addWidget(saveButton, 9, 41, 1, 4);
    outputLayout->addWidget(saveAsButton, 12, 41, 1, 4);
    outputLayout->addWidget(ndviKey, 46, 21, 1, 8, Qt::AlignBottom);
    outputLayout->addWidget(imageProcessProgressBar, 22, 23, 1, 4, Qt::AlignCenter);

    setLayout(outputLayout);

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
    return progressBar;
}

void outputImageGui::loadNdviImage(std::string fileName)
{
    QString qFileName = QString::fromStdString(fileName);
    QPixmap pix;
    pix.load(qFileName);
    outputImageDisplay->setPixmap(pix);

}
