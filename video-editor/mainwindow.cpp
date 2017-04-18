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
    QObject::connect(fileManager, SIGNAL(itemWasClicked(QUrl)),
              player, SLOT(playSelectedItem(QUrl)));
}

MainWindow::~MainWindow()
{
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

void MainWindow::on_onProjectSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr(""), "",
            tr("All Files (*)"));
    StorageService::Instance().saveProject(fileName);

}

void MainWindow::on_onProjectOpen_triggered()
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
