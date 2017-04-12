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

private:
    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    void setIcons();
    void initPlayer();

};

#endif // PLAYER_H
