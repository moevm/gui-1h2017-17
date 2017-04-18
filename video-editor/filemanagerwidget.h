#ifndef FILEMANAGERWIDGET_H
#define FILEMANAGERWIDGET_H

#include <QWidget>
#include <QStandardItem>
#include <QStringList>
#include <QKeyEvent>

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
    void deleteItem();

private slots:

    void on_addAudio_clicked();
    void on_addVideo_clicked();
    void on_addImage_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

signals:
    void itemWasClicked(QUrl);

private:
    Ui::FileManagerWidget *ui;



    QStandardItemModel* filesModel;

    QString homeDir;

    void setIcons();
    void tableViewSettings();
    void addItem(QStringList& , QImage&);

};

#endif // FILEMANAGERWIDGET_H
