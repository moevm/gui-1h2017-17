#include "filemanagerwidget.h"
#include "ui_filemanagerwidget.h"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}
