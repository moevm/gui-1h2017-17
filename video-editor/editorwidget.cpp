#include "editorwidget.h"
#include "ui_editorwidget.h"

#include "QtDebug"

EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);
    length = 0;
    length1 = 0;
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
    QWidget* itemWidget = new QWidget();
    itemWidget->setAutoFillBackground(true);
    QPalette pal(palette());
    pal.setColor(QPalette::Background, Qt::gray);
    itemWidget->setPalette(pal);
    ui->tracklist->setAlignment(Qt::AlignLeft);
    ui->audioTrack->setAlignment(Qt::AlignLeft);
    itemWidget->setMinimumWidth((item.end - item.begin)/100);
    itemWidget->setMaximumWidth((item.end - item.begin)/100);

    QLabel* name = new QLabel(itemWidget);
    QString str = item.url.right(item.url.length()-item.url.lastIndexOf('/')-1);
    name->setText(str);
    QString extension = item.url.right(3);
    qDebug() << "length" << length <<length1;
    if(extension == "mp3"){
        ui->audioTrackWidget->setVisible(false);
        ui->audioTrack->addWidget(itemWidget);
        isMedia = false;
        qDebug() << "add" << isMedia << length1;
    }

    if(extension == "avi"){
        ui->widget->setVisible(false);
        ui->tracklist->addWidget(itemWidget);
        isMedia = true;
        qDebug() << "add" << isMedia << length;
    }

    if (isMedia){
        item.absBegin = length;
        length += item.end - item.begin;
    }
    else{
        item.absBegin = length1;
        length1 += (item.end - item.begin);
    }
    item.absEnd = item.absBegin + item.end - item.begin;
    qDebug() << "add1" << isMedia << item.absBegin << item.absEnd <<item.begin <<item.end;
    list.append(item);

}


void EditorWidget::on_pushButton_clicked()
{
    emit playUsersList(list,length,length1);
}
