#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QStandardItem>
#include <QStringList>

namespace Ui {
class FileManagerWidget;
}

class FileManagerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FileManagerWidget(QWidget *parent = 0);
    ~FileManagerWidget();

    void changeSize();

private slots:

    void on_addAudio_clicked();

    void on_addVideo_clicked();

    void on_addImage_clicked();

private:
    Ui::FileManagerWidget *ui;
    QList <QStandardItem *> audioFiles;
    QList <QStandardItem *> videoFiles;
    QList <QStandardItem *> imageFiles;

    QStandardItemModel* filesModel;

    QString homeDir;

    void setIcons();
    void tableViewSettings();

    void addItem(QStringList& , QImage&, QList <QStandardItem*>&);

};

#endif // FILEMANAGERWIDGET_H
