#include "filemanagerwidget.h"
#include "ui_filemanagerwidget.h"

#include <QFileDialog>
#include <QStandardItem>

#include "QtDebug"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);
    homeDir = "/";

    ui->addAudio->setIcon(QIcon("../addAudio.png"));
    ui->addVideo->setIcon(QIcon("../addVideo.png"));
    ui->addImage->setIcon(QIcon("../addImage.png"));
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}

void FileManagerWidget::on_addAudio_clicked()
{
    QString fileName;
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите аудио файлы",
                            homeDir,
                            "Аудиофайлы (*.mp3 *.m4a *.wav *.aif *.aifc *.aiff *.snd *.au *.mpa *.mp2 *.wma *.asf)");

    foreach (QString filePath, files) {
        fileName = QDir(filePath).dirName();
        audioFiles.append(new QStandardItem(QDir(filePath).dirName()));
    }
    if (files.size() > 0){
        homeDir = files.at(0);
        homeDir.left(homeDir.lastIndexOf("/")+1);
    }
}

void FileManagerWidget::on_addVideo_clicked()
{
    QString fileName;
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите видео файлы",
                            homeDir,
                            "Видео (*.avi *.mpg *.m1v *.mp2 *.mp2v *.mpeg *.mpe *.mpv2 *.wm *wmv *.asf)");

    foreach (QString filePath, files) {
        fileName = QDir(filePath).dirName();
        videoFiles.append(new QStandardItem(QDir(filePath).dirName()));
    }

    if (files.size() > 0){
        homeDir = files.at(0);
        homeDir.left(homeDir.lastIndexOf("/")+1);
    }
}

void FileManagerWidget::on_addImage_clicked()
{
    QString fileName;
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите изображения",
                            homeDir,
                            "Изображения (*.jpg *.jpeg *.jpe *.jfif *.gif *.png *.bmp *.dib *.tif *.tiff *.wmf *.emf)");

    foreach (QString filePath, files) {
        fileName = QDir(filePath).dirName();
        imageFiles.append(new QStandardItem(QDir(filePath).dirName()));
    }
    if (files.size() >0){
        homeDir = files.at(0);
        homeDir.left(homeDir.lastIndexOf("/")+1);
    }
}

