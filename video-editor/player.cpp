#include "player.h"
#include "ui_player.h"
#include "QtDebug"
#include <QTime>

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
    initPlayer();
    isItem = true;
    isExistCurItem = false;

    wasStop = false;
    ui->verticalGroupBox->setStyleSheet("QGroupBox { border: 0px}");
    ui->groupBox_2->setStyleSheet("QGroupBox { border: 0px}");

    connect(mediaPlayer, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    k = 0;
    glass = new Glass();

    position = 0;

}

Player::~Player()
{
    delete ui;
    delete mediaPlayer;
    delete glass;
    delete playlist;
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
    isExistCurItem = true;
    isItem = true;
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
    if (wasStop){
        qDebug() << wasStop << isItem;
        if (isItem){
            mediaPlayer->setPosition(curItem.begin);
        }
        else{
            if (list.size() > 0){
                mediaPlayer->setPosition(list.at(0).begin);
            }
        }
        wasStop = false;
    }
    mediaPlayer->play();
    ui->pause->setToolTip("Приостановить");
    this->play = true;
}

void Player::on_stop_clicked()
{
    mediaPlayer->stop();
    setPause();
    wasStop = true;
    if (!isItem){
        playlist->setCurrentIndex(0);
        position = 0;
        ui->trackW->setValue(position);
    }
}

void Player::updateTime(){
    if (isItem){
        position = 0;
        ui->trackW->setMaximum(curItem.end);
        ui->trackW->setMinimum(curItem.begin);
        if (mediaPlayer->position() <= curItem.end){
            qint64 position = mediaPlayer->position();

            int seconds = (position/1000) % 60;
            int minutes = (position/60000) % 60;
            int hours = (position/3600000) % 24;

            QTime time(hours, minutes,seconds);

            ui->time->setText(time.toString());
            ui->trackW->setValue(mediaPlayer->position());
        }
        else{
            on_stop_clicked();
        }
    }
    else{
        if (this->play){
            if (playlist->currentIndex() >= 0){
                ui->trackW->setMaximum(length);
                ui->trackW->setMinimum(0);
                ui->trackW->setValue(position);

                int seconds = (position/1000) % 60;
                int minutes = (position/60000) % 60;
                int hours = (position/3600000) % 24;

                QTime time(hours, minutes,seconds);
                ui->time->setText(time.toString());

                int curMedia = playlist->currentIndex();

                if (position > (list.at(curMedia).absEnd)){

                    if (list.size() - 1 == curMedia){
                        on_stop_clicked();
                    }
                    playlist->next();
                    if (curMedia + 1 == list.size()){
                        on_stop_clicked();
                    }
                    else{
                        mediaPlayer->setPosition(list.at(curMedia + 1).begin);
                    }
                }
                position++;
            }
        }
    }
}

void Player::getPlayList(QList<PlayItem> list1, qint64 l)
{
    QList<PlayItem> audiolist = QList<PlayItem>();
    QList<PlayItem> videolist = QList<PlayItem>();
    foreach (PlayItem item, list1) {
        if(item.url.right(3)=="avi"){
            videolist.append(item);
        }

        if(item.url.right(3)=="mp3"){
            audiolist.append(item);
        }
    }

    isExistCurItem = false;
    length = l;
    list = videolist;
    isItem = false;
    playlist = new QMediaPlaylist(mediaPlayer);
    for (int i = 0; i < list.size() ; i++){
        playlist->addMedia(QUrl(list.at(i).url));
    }
    mediaPlayer->setPlaylist(playlist);
    if (list.size() > 0){
        mediaPlayer->setPosition(list.at(0).begin);
        setPlay();
    }

    isItem = false;
    audioPlayList = new QMediaPlaylist(audioPlayer);
    for (int i = 0; i < audiolist.size() ; i++){
        audioPlayList->addMedia(QUrl(audiolist.at(i).url));
    }
    audioPlayer->setPlaylist(audioPlayList);
    if (list.size() > 0){
        audioPlayer->setPosition(list.at(0).begin);
        setPlay();
    }
}

void Player::on_horizontalSlider_sliderMoved(int position)
{
    mediaPlayer->setVolume(position);
}

void Player::on_trackW_sliderMoved(int position)
{
    if (isItem){
        mediaPlayer->setPosition(position);
    }
    else{
        for (int i = 0; i < list.size(); i++){
            if (list.at(i).absEnd > position){
                playlist->setCurrentIndex(i);
                mediaPlayer->setPosition(position - list.at(i).absBegin);
            }
        }
    }
}

//левая граница проигрывания
void Player::on_cutLeft_clicked()
{
    ui->trackW->setMinimum(ui->trackW->value());
    mediaPlayer->setPosition(ui->trackW->value());
    curItem.begin = ui->trackW->value();
}

//правая граница проигрывания
void Player::on_cutRight_clicked()
{
    ui->trackW->setMaximum(ui->trackW->value());
    mediaPlayer->setPosition(curItem.begin);
    curItem.end = ui->trackW->value();
    setPlay();
}


//определяет длину загруженного трека/видео
void Player::durationChanged(qint64 dur)
{
        curItem.begin = 0;
        curItem.end = dur;
}


//отправление текущего элемента в editor
void Player::on_toEditor_clicked()
{   
   if (isExistCurItem){
       emit cutWasClicked(curItem);
   }
}
