#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <qvideosurfaceformat.h>

#include "glass.h"
#include "videoframegrabber.h"

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();

public slots:
    void playSelectedItem(QString);
    void updateTime();

private slots:

    void on_pause_clicked();
    void on_stop_clicked();
    void on_horizontalSlider_sliderMoved(int position);
    void on_trackW_sliderMoved(int position);

    void processFrame(QImage);

private:
    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    QMediaPlayer* player;
    VideoFrameGrabber* grabber;
    Glass* glass;
    bool play;
    
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
