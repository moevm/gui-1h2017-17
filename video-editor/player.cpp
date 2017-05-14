#include "player.h"
#include "ui_player.h"
#include "QtDebug"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
    initPlayer();

    ui->verticalGroupBox->setStyleSheet("QGroupBox { border: 0px}");
    ui->groupBox_2->setStyleSheet("QGroupBox { border: 0px}");

    k = 0;
    glass = new Glass();
}

Player::~Player()
{
    delete ui;
    delete mediaPlayer;
}

void Player::setIcons()
{
    ui->pause->setIcon(QIcon("../play.png"));
    ui->stop->setIcon(QIcon("../stop.png"));
    ui->frameForward->setIcon(QIcon("../frameForward.png"));
    ui->frameBack->setIcon(QIcon("../frameBack.png"));
    ui->pause->setToolTip("Воспроизвести");
    ui->stop->setToolTip("Остановить");
    ui->frameForward->setToolTip("Следующий кадр");
    ui->frameBack->setToolTip("Предыдущий кадр");

}

void Player::playSelectedItem(QString item)
{
    QString res = item.right(3);
    mediaPlayer->setMedia(QUrl(item));
    if ((res == "jpg") || (res == "peg") ||
            (res == "jpe") || (res == "fif") ||
            (res == "png") || (res == "bmp") ||
            (res == "dib") || (res == "tif") ||
            (res == "iff") || (res == "wmf") ||
            (res == "emf") || (res == "gif")){
        glass->install(ui->mediaPlayer);
    }
    else{
        glass->remove();
        setPlay();
    }

   // glass->install(ui->mediaPlayer);
}

void Player::initPlayer(){
    mediaPlayer = new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVideoOutput(ui->mediaPlayer);
    mediaPlayer->setMedia(QUrl("../../gravity.avi"));
    mediaPlayer->play();

    grabber = new VideoFrameGrabber(this);
    player = new QMediaPlayer(this);
    player->setVideoOutput(grabber);
    connect(grabber, SIGNAL(frameAvailable(QImage)), this, SLOT(processFrame(QImage)));
    player->setMedia(QUrl("../../gravity.avi"));
    player->play();
}

void Player::on_pause_clicked()
{
    this->play = !this->play;
    if (this->play){
        setPlay();
    }
    else{
        setPause();
    }
}

void Player::setPause(){
    ui->pause->setIcon(QIcon("../play.png"));
    mediaPlayer->pause();
    ui->pause->setToolTip("Воспроизвести");
    this->play = false;

        QVideoFrame frame;
        grabber->present(frame);
}

void Player::setPlay(){
    ui->pause->setIcon(QIcon("../pause.png"));
    mediaPlayer->play();
    ui->pause->setToolTip("Приостановить");
    this->play = true;
}

void Player::on_stop_clicked()
{
    mediaPlayer->stop();
    setPause();
}

void Player::updateTime(){
    ui->trackW->setMaximum(mediaPlayer->duration());
    ui->trackW->setValue(mediaPlayer->position());
    int t1 = (mediaPlayer->position())/3600000;
    int t = t1 % 100;
    if (t == 0){
        ui->hh->setText("00");
    }
    else {
        if ((t <= 9) && (t > 0)){
            ui->hh->setText("0" + QString::number(t));
        }
        else{
            ui->hh->setText(QString::number(t));
        }
    }
    t1 = (mediaPlayer->position())/60000;
    t = t1 % 60;
    if (t == 0){
        ui->mm->setText("00");
    }
    else {
        if ((t <= 9) && (t > 0)){
            ui->mm->setText("0" + QString::number(t));
        }
        else{
            ui->mm->setText(QString::number(t));
        }
    }
    t1 = (mediaPlayer->position())/1000;
    t = t1 % 60;
    if (t == 0){
        ui->ss->setText("00");
    }
    else {
        if ((t <= 9) && (t > 0)){
            ui->ss->setText("0" + QString::number(t));
        }
        else{
            ui->ss->setText(QString::number(t));
        }
    }
}

void Player::on_horizontalSlider_sliderMoved(int position)
{
    mediaPlayer->setVolume(position);
}

void Player::on_trackW_sliderMoved(int position)
{
    mediaPlayer->setPosition(position);
}

void Player::processFrame(QImage)
{
    qDebug() << "я в процес фрейм" << k;
    k++;
}

