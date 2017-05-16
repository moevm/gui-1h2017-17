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

    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

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
    ui->pause->setIcon(QIcon(playIcon()));
    ui->stop->setIcon(QIcon(stopIcon()));
    ui->frameForward->setIcon(QIcon(frameForwardIcon()));
    ui->frameBack->setIcon(QIcon(frameBackIcon()));
    ui->pause->setToolTip("Воспроизвести");
    ui->stop->setToolTip("Остановить");
    ui->frameForward->setToolTip("Следующий кадр");
    ui->frameBack->setToolTip("Предыдущий кадр");
    //скроем кнопки для раскадровки
    ui->frameForward->setVisible(false);
    ui->frameBack->setVisible(false);

}

void Player::playSelectedItem(QString item)
{
    wasPlayed = false;
    QString res = item.right(3);
    curItem.url = item;
    mediaPlayer->setMedia(QUrl(item));
    if ((res == "jpg") || (res == "peg") ||
            (res == "jpe") || (res == "fif") ||
            (res == "png") || (res == "bmp") ||
            (res == "dib") || (res == "tif") ||
            (res == "iff") || (res == "wmf") ||
            (res == "emf") || (res == "gif")){
        glass->install(ui->mediaPlayer, item);
    }
    else{
        glass->remove();
        setPlay();
    }
}

void Player::initPlayer(){
    mediaPlayer = new QMediaPlayer(0,QMediaPlayer::VideoSurface);
    mediaPlayer->setVideoOutput(ui->mediaPlayer);
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
    ui->pause->setIcon(QIcon(playIcon()));
    mediaPlayer->pause();
    ui->pause->setToolTip("Воспроизвести");
    this->play = false;
}

void Player::setPlay(){
    ui->pause->setIcon(QIcon(pauseIcon()));
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
    ui->trackW->setMaximum(curItem.end);
    ui->trackW->setMinimum(curItem.begin);
    if (mediaPlayer->position() <= curItem.end){
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
    else{
        on_stop_clicked();
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

void Player::on_cutLeft_clicked()
{
    ui->trackW->setMinimum(ui->trackW->value());
    mediaPlayer->setPosition(ui->trackW->value());
    curItem.begin = ui->trackW->value();
    qDebug() << curItem.begin << curItem.end;
    qDebug() << ui->trackW->minimum() << ui->trackW->maximum();
}

void Player::on_cutRight_clicked()
{
    ui->trackW->setMaximum(ui->trackW->value());
    ui->trackW->update();
    //mediaPlayer->setPosition(curItem.begin);
    mediaPlayer->setPosition(ui->trackW->value());
    curItem.end = ui->trackW->value();
    qDebug() << curItem.begin << curItem.end;
    qDebug() << ui->trackW->minimum() << ui->trackW->maximum();

}

void Player::durationChanged(qint64 dur)
{
        curItem.begin = 0;
        curItem.end = dur;
        qDebug() << curItem.begin << curItem.end;
}

void Player::on_toEditor_clicked()
{

}
