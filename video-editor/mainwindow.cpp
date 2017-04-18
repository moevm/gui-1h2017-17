#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    fileManager = new FileManagerWidget(ui->centralWidget);
    setCentralWidget(fileManager);
    player = ui->player_w;
    QObject::connect(fileManager, SIGNAL(itemWasClicked(QUrl)), player, SLOT(playSelectedItem(QUrl)));

    //QObject::connect(player, SIGNAL(sizeOfPlayerWasChanged()),fileManager, SLOT(changeSize()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete player;
    delete fileManager;
    delete editor;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == 16777223){
        fileManager->deleteItem();
    }
}


void MainWindow::resizeEvent(QResizeEvent *event){
    event->accept();//прост бесит ворнинг :(
    this->fileManager->changeSize();
    this->editor->changeSize();
}



