#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QMediaPlayer>
#include <qvideosurfaceformat.h>

namespace Ui {
class Player;
}

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = 0);
    ~Player();
    void setSize();

public slots:
    void playSelectedItem(QString);

private slots:
    void on_play_clicked();

    void on_pause_clicked();

    void on_stop_clicked();

private:
    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    void setIcons();
    void initPlayer();

};

#endif // PLAYER_H
