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
            QAction* action = new QAction(fileInfo->path, this);
            //todo вот тут непонятная беда
            connect(action, SIGNAL(triggered()), this, SLOT(onProjectFileSelect(fileInfo->path);));
            ui->lastOpenedMenu->addAction(action);
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
            bool isContains = false;
            foreach (MovieMakerFileInfo* cacheFile, cacheLastOpenedFiles) {
                if(cacheFile->path == fileInfo->path){
                    isContains = true;
                    break;
                }
            }
            if(isContains) continue;
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

void MainWindow::onProjectFileSelect(QString projectPath){
    MainWindow::openProject(projectPath);
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
    MainWindow::openProject(fileName);



}

void MainWindow::openProject(QString fileName){
    fileManager->clearAll();
    QList <MovieMakerFileInfo*> files = StorageService::Instance().loadProject(fileName);
    foreach (MovieMakerFileInfo* fileInfo, files) {
        fileManager->addItem(fileInfo->path,fileInfo->imagePath);
    }

    MovieMakerFileInfo* fileInfo = new MovieMakerFileInfo;
    fileInfo->path = fileName;
    StorageService::Instance().addLastOpenedFile(fileInfo);
}

