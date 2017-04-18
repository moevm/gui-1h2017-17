#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "storageservice.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileManager = new FileManagerWidget(ui->centralWidget);
    setCentralWidget(fileManager);
    player = ui->player_w;
    QObject::connect(fileManager, SIGNAL(itemWasClicked(QUrl)), player, SLOT(playSelectedItem(QUrl)));

    QList <MovieMakerFileInfo*> lastOpenedFiles = StorageService::Instance().loadLastOpenedFiles();
    if(lastOpenedFiles.length() != 0){
        foreach (MovieMakerFileInfo* fileInfo, lastOpenedFiles) {
            ui->lastOpenedMenu->addAction(fileInfo->path);
        }
    }

}

MainWindow::~MainWindow()
{
    QList <MovieMakerFileInfo*> currentSavedFiles = StorageService::Instance().loadLastOpenedFiles();
    QList <MovieMakerFileInfo*> cacheLastOpenedFiles = StorageService::Instance().getCacheLastOpenedFiles();
    if(cacheLastOpenedFiles.length()<5) {

        int difference = 5 - cacheLastOpenedFiles.length();

        foreach (MovieMakerFileInfo* fileInfo, currentSavedFiles) {
            if(difference == 0) break;
            if(cacheLastOpenedFiles.contains(fileInfo)) continue;
            StorageService::Instance().addLastOpenedFile(fileInfo);
            difference--;
        }

    }
    StorageService::Instance().saveLastOpenedFiles();


    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777223){
        fileManager->deleteItem();
    }
}


void MainWindow::resizeEvent(QResizeEvent *event){
    this->fileManager->changeSize();
    player->setSize();
}

void MainWindow::onProjectSaveSelect(){

}

void MainWindow::on_projectSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr(""), "",
            tr("All Files (*)"));
    StorageService::Instance().saveProject(fileName);
}

void MainWindow::on_projectOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr(""), "",
            tr("All Files (*)"));
    fileManager->clearAll();
    QList <MovieMakerFileInfo*> files = StorageService::Instance().loadProject(fileName);
    foreach (MovieMakerFileInfo* fileInfo, files) {
        fileManager->addItem(fileInfo->path,fileInfo->imagePath);
    }


}

