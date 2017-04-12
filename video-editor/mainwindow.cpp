#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileManager = new FileManagerWidget(ui->centralWidget);
    setCentralWidget(fileManager);
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
    ui->editor_w->changeSize();
}
