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
    void resizeEvent(QResizeEvent* event);
    ~Player();

public slots:
    void playSelectedItem(QUrl);
    void changeSize();

private slots:
    void on_play_clicked();
    void on_pause_clicked();
    void on_stop_clicked();

private:
    Ui::Player *ui;
    QMediaPlayer* mediaPlayer;
    void setIcons();
    void initPlayer();

signals:
    sizeOfPlayerWasChanged();
};

#endif // PLAYER_H
