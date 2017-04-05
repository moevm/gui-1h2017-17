#include "player.h"
#include "ui_player.h"

Player::Player(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player)
{
    ui->setupUi(this);
    setIcons();
}

Player::~Player()
{
    delete ui;
}

void Player::setIcons()
{
    ui->play->setIcon(QIcon("../play.png"));
    ui->pause->setIcon(QIcon("../pause.png"));
    ui->stop->setIcon(QIcon("../stop.png"));
}
