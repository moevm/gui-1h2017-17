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
    bool play = false;
    void setIcons();
    void initPlayer();
    void setPause();
    void setPlay();
    int k;

    QString playIcon = ":/images/play.png";
    QString pauseIcon = ":/images/pause.png";
    QString stopIcon = ":/images/stop.png";
    QString frameForwardIcon = ":/images/frameForward.png";
    QString frameBackIcon = ":/images/frameBack.png";
};

#endif // PLAYER_H
