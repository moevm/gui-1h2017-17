#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "storageservice.h"
#include <QSignalMapper>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileManager = new FileManagerWidget(ui->centralWidget);
    setCentralWidget(fileManager);
    player = ui->player_w;
    editor = ui->editor_w;
    QObject::connect(fileManager, SIGNAL(itemWasClicked(QString)), player, SLOT(playSelectedItem(QString)));


    loadLastOpenedFiles();
}

MainWindow::~MainWindow()
{
    StorageService::Instance().saveLastOpenedProjects();
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
    editor->changeSize();
}

void MainWindow::loadLastOpenedFiles(){
    QList <MovieMakerFileInfo*> lastOpenedFiles = StorageService::Instance().loadLastOpenedFiles();
    ui->lastOpenedMenu->clear();
    if(lastOpenedFiles.length() != 0){
        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        foreach (MovieMakerFileInfo* fileInfo, lastOpenedFiles) {
            QAction* action = new QAction(fileInfo->path, this);
            connect(action, SIGNAL(triggered()), signalMapper, SLOT(map()));
            signalMapper -> setMapping (action, fileInfo->path);
            connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(onProjectFileSelect(QString))) ;
            ui->lastOpenedMenu->addAction(action);
        }
    }
}

void MainWindow::onProjectFileSelect(QString path){
   openProject(path);
}

void MainWindow::on_projectSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr(""), "",
            tr("All Files (*)"));
    if(fileName.isEmpty()) return;
    MovieMakerFileInfo* file = new MovieMakerFileInfo;
    file->path = fileName;
    StorageService::Instance().addLastOpenedFile(file);
    StorageService::Instance().saveLastOpenedProjects();
    loadLastOpenedFiles();
    StorageService::Instance().saveProject(fileName);


}

void MainWindow::on_projectOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr(""), "",
            tr("All Files (*)"));
    if(fileName.isEmpty()) return;
    MainWindow::openProject(fileName);
}

void MainWindow::openProject(QString fileName){
    fileManager->clearAll();
    QList <MovieMakerFileInfo*> files = StorageService::Instance().loadProject(fileName);
    StorageService::Instance().clear();
    foreach (MovieMakerFileInfo* fileInfo, files) {
        fileManager->addItem(fileInfo->path,fileInfo->imagePath);
    }

    MovieMakerFileInfo* fileInfo = new MovieMakerFileInfo;
    fileInfo->path = fileName;

    StorageService::Instance().addLastOpenedFile(fileInfo);
}

