#include "editorwidget.h"
#include "ui_editorwidget.h"

#include "QtDebug"



EditorWidget::EditorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EditorWidget)
{
    ui->setupUi(this);
}

EditorWidget::~EditorWidget()
{
    delete ui;
}

void EditorWidget::changeSize()
{
    //ui->tableView->setGeometry(10,60, this->size().width()-20, this->size().height()-70);
    qDebug() << "я зашел в чэндж сайз";
    int w =  80;
    int h =  20;
    ui->horizontalSlider->setGeometry(70,10,20,20);
   // ui->verticalLayout->setGeometry(QRect(70,10,w,h));
    //ui->verticalLayoutWidget->setGeometry(70,10,w,h);
}
