#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QFileDialog>
#include "filemanagerwidget.h"
#include "player.h"
#include "QtDebug"

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

private slots:
    void resizeEvent(QResizeEvent*);
    void onProjectSaveSelect();

    void on_projectSave_triggered();

    void on_projectOpen_triggered();

    void on_lastOpened_hovered();

private:
    Ui::MainWindow *ui;
    FileManagerWidget *fileManager;
    Player* player;
};

#endif // MAINWINDOW_H
