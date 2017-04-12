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

//void EditorWidget::changeSize()
//{
//    int w = this->width() - 80;
//    int h = this->height() - 20;
//    ui->verticalLayoutWidget->setGeometry(70,10,w,h);
//}
