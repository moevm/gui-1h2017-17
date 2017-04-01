#include "editorwidget.h"
#include "ui_editorwidget.h"

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
