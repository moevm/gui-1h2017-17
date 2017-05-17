#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <qvideosurfaceformat.h>

#include "glass.h"
#include "playitem.h"



namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

Q_SIGNALS:
    void cutWasClicked(PlayItem item);

public slots:
    void playSelectedItem(QString);
    void updateTime();
    void getPlayList(QList <PlayItem>, qint64);

private slots:

    void on_pause_clicked();
    void on_stop_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_trackW_sliderMoved(int position);

    void on_cutLeft_clicked();
    void on_cutRight_clicked();
    void durationChanged(qint64);

    void on_toEditor_clicked();

private:
    bool isExistCurItem;

    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    Glass* glass;
    bool play; // состояние плеера
    PlayItem curItem; // текущий элемент в плеере
    QMediaPlaylist* playlist;
    QList <PlayItem> list;
    bool isItem; //проверка сейчас в плеере единичный элемент (1) или плейлист (0)
    qint64 length; // длина плейлиста в милисекундах
    qint64 position; // позиция плейлиста
    bool wasStop;
    
    void setIcons();
    void initPlayer();
    void setPause();
    void setPlay();
    int k;

    static QString playIcon() {return ":/images/play.png"; }
    static QString pauseIcon() {return ":/images/pause.png";}
    static QString stopIcon() {return ":/images/stop.png";}
    static QString frameForwardIcon() {return ":/images/frameForward.png";}
    static QString frameBackIcon(){return ":/images/frameBack.png";}

};

#endif // PLAYER_H
