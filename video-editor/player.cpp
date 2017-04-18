#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
    changeSize();
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

void Player::changeSize(){
    qDebug() << "я пытаюсь поменять размер но у меня по ходу нихера не выходит";
    ui->mediaPlayer->setGeometry(0,0,this->width(),this->width()/5*3);
}

void Player::playSelectedItem(QUrl item)
{
    mediaPlayer->setMedia(item);
    mediaPlayer->play();
}

void Player::initPlayer(){
    mediaPlayer = new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVideoOutput(ui->mediaPlayer);
    //QImage img("../../1.jpg");
    //img.save("../../1.avi");
    qDebug() << "try to play 1.avi";
    //mediaPlayer->setMedia(QUrl("../../1.avi"));
    mediaPlayer->play();
}

void Player::resizeEvent(QResizeEvent *event)
{
    emit sizeOfPlayerWasChanged();
}

void Player::on_play_clicked()
{
    mediaPlayer->play();
}

void Player::on_pause_clicked()
{
    mediaPlayer->pause();
}

void Player::on_stop_clicked()
{
    mediaPlayer->stop();
}
