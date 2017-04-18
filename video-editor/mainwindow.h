#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include "filemanagerwidget.h"
#include "player.h"
#include "editorwidget.h"
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

private:
    Ui::MainWindow *ui;
    FileManagerWidget *fileManager;
    Player* player;
    EditorWidget* editor;
};

#endif // MAINWINDOW_H
