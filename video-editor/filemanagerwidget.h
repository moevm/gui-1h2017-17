#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QStandardItem>
#include <QStringList>
#include <QKeyEvent>

#include "storageservice.h"

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
    void addItem(QString filePath, QString imagePath);
    void deleteItem();
    void clearAll();

    QString audioImagePath = ":/images/addAudio.png";
    QString pictureImagePath = ":/images/addImage.png";
    QString videoImagePath = ":/images/addVideo.png";
    QString recordIcon = ":/images/record.png";

private slots:

    void on_addAudio_clicked();
    void on_addVideo_clicked();
    void on_addImage_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

signals:
    void itemWasClicked(QString);

private:
    Ui::FileManagerWidget *ui;
    QStandardItemModel* filesModel;
    QString homeDir;

    void setIcons();
    void tableViewSettings();
    void addItems(QStringList& , QString);


};

#endif // FILEMANAGERWIDGET_H
