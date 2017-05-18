#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include "playitem.h"
#include <QList>

namespace Ui {
class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT

 Q_SIGNALS:
    void playUsersList(QList <PlayItem>, qint64, qint64);

public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();

    void changeSize();

public slots:
    void addToPlayList(PlayItem);

private slots:
    void on_pushButton_clicked();

private:
    Ui::EditorWidget *ui;
    QList <PlayItem> list;
    qint64 length;
    qint64 length1;
    bool isMedia;

    static QString playIcon() {return ":/images/play.png"; }
};

#endif // EDITORWIDGET_H
