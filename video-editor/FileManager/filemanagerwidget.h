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
    explicit FileManagerWidget(QWidget *parent);
    ~FileManagerWidget();

    void changeSize();
    QVector <QUrl> getAllUrls();

signals:
    void itemWasClicked(QUrl url);

private slots:

    void on_addAudio_clicked();
    void on_addVideo_clicked();
    void on_addImage_clicked();

private:


    Ui::FileManagerWidget *ui;

    QVector <QUrl> allUrl;
    QStandardItemModel* filesModel;

    QString homeDir;

    void setIcons();
    void tableViewSettings();
    void addItem(QStringList& , QImage&, QVector <QUrl>&);

};

#endif // FILEMANAGERWIDGET_H
