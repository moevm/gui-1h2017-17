#include "editorwidget.h"
#include "ui_editorwidget.h"

#include "QtDebug"

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);
    fakePlayer = new QMediaPlayer();
    myQAbstractVideoSurface* vsurface = new myQAbstractVideoSurface(this);
    fakePlayer->setVideoOutput(vsurface);

    connect(vsurface, SIGNAL(fnSurfaceStopped(QPixmap)),
            this, SLOT(onMediaPlayerStop(QPixmap)),Qt::QueuedConnection);


}

EditorWidget::~EditorWidget()
{
    delete ui;
}

void EditorWidget::onMediaPlayerStop(QPixmap pix)
{

}

void EditorWidget::changeSize()
{
    int w = this->geometry().width()-90;
    int h = 130;
    ui->verticalLayoutWidget->setGeometry(70,10,w,h);
}

void EditorWidget::onVideoLoadOnTrack(QString filePath){

    fakePlayer->setMedia(QUrl::fromLocalFile(filePath));

    fakePlayer->setPosition(2*1000);
    fakePlayer->setMuted(true);
    fakePlayer->play();

}

void onMediaPlayerStop(QPixmap image){

}
