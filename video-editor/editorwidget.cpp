#include "editorwidget.h"
#include "ui_editorwidget.h"

#include "QtDebug"

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);
    length = 0;
    ui->pushButton->setIcon(QIcon(this->playIcon()));
}

EditorWidget::~EditorWidget()
{
    delete ui;
}

void EditorWidget::changeSize()
{
    int w = this->geometry().width()-90;
    int h = 130;
    ui->verticalLayoutWidget->setGeometry(70,10,w,h);
}

void EditorWidget::addToPlayList(PlayItem item)
{
    qDebug() << "editor" << item.begin << item.end;

    item.absBegin = length + 1;
    item.absEnd = item.absBegin + item.end - item.begin;
    list.append(item);
    length += (item.end - item.begin);

    QWidget* itemWidget = new QWidget();
    itemWidget->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    itemWidget->setPalette(pal);

    QLabel* name = new QLabel(itemWidget);
    QString str = item.url.right(item.url.length()-item.url.lastIndexOf('/')-1);
    name->setText(str);
    QString extension = item.url.right(3);
    if(extension == "mp3"){
        ui->audioTrackWidget->setVisible(false);
        ui->audioTrack->addWidget(itemWidget);
    }

    if(extension == "mp4"){
         ui->widget->setVisible(false);
        ui->tracklist->addWidget(itemWidget);
    }


    qDebug() << item.absBegin << item.absEnd << item.begin << item.end;
}


void EditorWidget::on_pushButton_clicked()
{
    emit playUsersList(list,length);
}
