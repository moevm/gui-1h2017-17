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
    int w = this->geometry().width()-90;
    int h = 130;
    ui->verticalLayoutWidget->setGeometry(70,10,w,h);
}
