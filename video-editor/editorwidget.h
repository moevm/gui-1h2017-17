#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QImage>;
#include <QMediaPlayer>;
#include "videoframegrabber.h"

struct VideoSecond{
    int second;
    QImage frames[];
};

namespace Ui {
class EditorWidget;
}

class EditorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EditorWidget(QWidget *parent = 0);
    ~EditorWidget();
    QMediaPlayer* fakePlayer;

    void changeSize();

    void onVideoLoadOnTrack(QString);


private slots:
    void onMediaPlayerStop(QPixmap pix);

private:
    Ui::EditorWidget *ui;
};

#endif // EDITORWIDGET_H
