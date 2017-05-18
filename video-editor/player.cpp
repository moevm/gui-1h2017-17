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
    audioPlayer = new QMediaPlayer();
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
    if ((!isItem) && (list1.size() >0)){
            audioPlayer->pause();
    }
    ui->pause->setToolTip("Воспроизвести");
    this->play = false;
}

void Player::setPlay(){
    ui->pause->setIcon(QIcon(pauseIcon()));
    if (wasStop){
        if (isItem){
            mediaPlayer->setPosition(curItem.begin);
        }
        else{
            if (!list.isEmpty()){
                mediaPlayer->setPosition(list.at(0).begin);
                if (!list1.isEmpty()){
                    audioPlayer->setPosition(list1.at(0).begin);
                }
            }
        }
        wasStop = false;
    }
    mediaPlayer->play();
    if ((!isItem) && (!list1.isEmpty())){
            audioPlayer->play();
    }
    ui->pause->setToolTip("Приостановить");
    this->play = true;
}

void Player::on_stop_clicked()
{
    setPause();
    mediaPlayer->stop();
    audioPlayer->stop();
    wasStop = true;
    if (!isItem){
        if (!list.isEmpty()) playlist->setCurrentIndex(0);
        if (!list1.isEmpty()) playlist1->setCurrentIndex(0);
        position = 0;
        ui->trackW->setValue(position);
    }
    QTime time (0,0,0);
    ui->time->setText(time.toString());
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
        if (!wasStop){
                bool isMediaLongest; // 1 - длиннее видео, 0 - длиннее аудио
                if (length > length1){
                    ui->trackW->setMaximum(length);
                    isMediaLongest = true;
                }
                else{
                    isMediaLongest = false;
                    ui->trackW->setMaximum(length1);
                }
                ui->trackW->setMinimum(0);
                ui->trackW->setValue(position);

                int seconds = (position/1000) % 60;
                int minutes = (position/60000) % 60;
                int hours = (position/3600000) % 24;

                QTime time(hours, minutes,seconds);
                ui->time->setText(time.toString());

                int curMedia = playlist->currentIndex();
                int curAudio = playlist1->currentIndex();

                if (position > (list.at(curMedia).absEnd)){
                    if (list.size() - 1 == curMedia){
                        if (isMediaLongest){
                            on_stop_clicked();
                        }
                        else{
                            mediaPlayer->stop();
                        }
                    }
                    else{
                        playlist->next();
                        if (curMedia + 1 == list.size()){
                            if (isMediaLongest){
                                on_stop_clicked();
                            }
                            else{
                                mediaPlayer->stop();
                            }
                        }
                        else{
                            mediaPlayer->setPosition(list.at(curMedia + 1).begin);
                        }
                    }
                }

                if (position > (list1.at(curAudio).absEnd)){
                    if (list1.size() - 1 == curAudio){
                        if (!isMediaLongest){
                            on_stop_clicked();
                        }
                        else{
                            audioPlayer->stop();
                        }
                    }
                    else{
                        playlist1->next();
                        if (curAudio + 1 == list1.size()){
                            if (!isMediaLongest){
                                on_stop_clicked();
                            }
                            else{
                                audioPlayer->stop();
                            }
                        }
                        else{
                            audioPlayer->setPosition(list1.at(curAudio + 1).begin);
                        }
                    }
                }
                position++;
        }
    }
}

void Player::getPlayList(QList<PlayItem> list2, qint64 l, qint64 l1)
{
    if (!list2.isEmpty()){
        foreach (PlayItem item, list2) {
            if(item.url.right(3)=="avi"){
                list.append(item);
            }

            if(item.url.right(3)=="mp3"){
                list1.append(item);
            }
        }

        isExistCurItem = false;
        length = l;
        length1 = l1;
        isItem = false;
        playlist = new QMediaPlaylist(mediaPlayer);
        playlist1 = new QMediaPlaylist(audioPlayer);
        if (!list.isEmpty()){
            for (int i = 0; i < list.size() ; i++){
                playlist->addMedia(QUrl(list.at(i).url));
            }
            mediaPlayer->setPlaylist(playlist);
            if (list.size() > 0){
                mediaPlayer->setPosition(list.at(0).begin);
            }
        }
        if (!list1.isEmpty()){
            for (int i = 0; i < list1.size() ; i++){
                playlist1->addMedia(QUrl(list1.at(i).url));
            }
            audioPlayer->setPlaylist(playlist1);
            if (list1.size() > 0){
                audioPlayer->setPosition(list1.at(0).begin);
            }
        }
        setPlay();
    }
}

void Player::on_horizontalSlider_sliderMoved(int position)
{
    mediaPlayer->setVolume(position);
    audioPlayer->setVolume(position);
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
