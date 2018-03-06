#ifndef OUTPUTIMAGEGUI_H
#define OUTPUTIMAGEGUI_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QFileDialog>
#include <QPixmap>
#include <QGridLayout>
#include <string>

class outputImageGui : public QWidget
{
    Q_OBJECT
public:
    explicit outputImageGui(QWidget *parent = nullptr);
    void loadNdviImage(std::string);

signals:

public slots:

    void saveButtonClicked();
    void saveAsButtonClicked();

private:
    QPushButton *saveButton, *saveAsButton;
    QLabel *outputImageDisplay, *ndviKey;
    QProgressBar *progressBar;
    QGridLayout *outputLayout;

    QPushButton *createButton(const QString& text);
    QLabel *createLabelDisplay();
    QProgressBar *createProgressBar();

};

#endif // OUTPUTIMAGEGUI_H
