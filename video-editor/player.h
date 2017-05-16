#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <qvideosurfaceformat.h>

#include "glass.h"
#include "videoframegrabber.h"

struct CurItem{
    int begin;
    int end;
    QString url;
};


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
    void cutWasClicked();

public slots:
    void playSelectedItem(QString);
    void updateTime();

private slots:

    void on_pause_clicked();
    void on_stop_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_trackW_sliderMoved(int position);

    void processFrame(QImage);

    void on_cutLeft_clicked();
    void on_cutRight_clicked();
    void durationChanged(qint64);

    void on_toEditor_clicked();

private:

    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    Glass* glass;
    bool play; // состояние плеера
    CurItem curItem; // текущий элемент в плеере
    bool wasPlayed;



    
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
