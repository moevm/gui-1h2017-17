#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QFileDialog>
#include "filemanagerwidget.h"
#include "player.h"
#include "QtDebug"
#include "QSignalMapper"
#include "storageservice.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent *event);

public slots:



private slots:
    void resizeEvent(QResizeEvent*);

    void on_projectSave_triggered();

    void on_projectOpen_triggered();

    //void on_lastOpened_hovered();

    void onProjectFileSelect(QString path);

private:
    Ui::MainWindow *ui;
    FileManagerWidget *fileManager;
    Player* player;

    void openProject(QString fileName);
    void loadLastOpenedFiles();
};

#endif // MAINWINDOW_H
