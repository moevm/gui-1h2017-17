#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
    setSize();
    initPlayer();
}

Player::~Player()
{
    delete ui;
    delete mediaPlayer;
}

void Player::setIcons()
{
    ui->play->setIcon(QIcon("../play.png"));
    ui->pause->setIcon(QIcon("../pause.png"));
    ui->stop->setIcon(QIcon("../stop.png"));
}

void Player::setSize(){
     ui->mediaPlayer->setGeometry(0,0,this->width(),this->width()/5*3);
}

void Player::initPlayer(){
    mediaPlayer = new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVideoOutput(ui->mediaPlayer);
    mediaPlayer->setMedia(QUrl("../../gravity.avi"));
    mediaPlayer->play();
}
