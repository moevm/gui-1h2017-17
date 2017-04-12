#include "player.h"
#include "ui_player.h"
#include <qvideosurfaceformat.h>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
    setSize();

   // mediaPlayer = new QMediaPlayer(0, QMediaPlayer::VideoSurface);
    //playList = new QMediaPlaylist(mediaPlayer);
}

Player::~Player()
{
    delete ui;
    delete mediaPlayer;
}

//void Player::setPlaylist(QVector<QUrl>)
//{
//    mediaPlayer->setPlaylist(playList);          // Устанавливаем плейлист в плеер
//    mediaPlayer->setVolume(50);                    // Устанавливаем громкость воспроизведения треков
//    mediaPlayer->setVideoOutput(ui->mediaPlayer);

//    QUrl url = QUrl("../Andrew Belle - Pieces.mp3");

//    playList->addMedia(url);
//    url = QUrl("../Way Down We Go.mp3");
//    playList->addMedia(url);
    //mediaPlayer->setMedia(url);
    //mediaPlayer->play();
//}

void Player::setIcons()
{
    ui->play->setIcon(QIcon("../play.png"));
    ui->pause->setIcon(QIcon("../pause.png"));
    ui->stop->setIcon(QIcon("../stop.png"));
}

void Player::setSize(){
    ui->mediaPlayer->setGeometry(0,0,this->width(),this->width()/5*3);
}
