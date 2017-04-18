#include "filemanagerwidget.h"
#include "ui_filemanagerwidget.h"
#include "storageservice.h"
#include <QFileDialog>
#include <QTableWidgetItem>

#include "QtDebug"

FileManagerWidget::FileManagerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FileManagerWidget)
{
    ui->setupUi(this);
    homeDir = "../../../!Musik/Depeche Mode";

    StorageService::Instance();


    tableViewSettings();
    setIcons();
}

FileManagerWidget::~FileManagerWidget()
{
    delete ui;
}

void FileManagerWidget::on_addAudio_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите аудио файлы",
                            homeDir,
                            "Аудиофайлы (*.mp3 *.m4a *.wav *.aif *.aifc *.aiff *.snd *.au *.mpa *.mp2 *.wma *.asf)");

    QImage image = QImage("../addAudio.png");
    addItem(files, image);
}

void FileManagerWidget::on_addVideo_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите видео файлы",
                            homeDir,
                            "Видео (*.avi *.mpg *.m1v *.mp2 *.mp2v *.mpeg *.mpe *.mpv2 *.wm *wmv *.asf)");

    QImage image = QImage("../addVideo.png");
    addItem(files, image);
}

void FileManagerWidget::on_addImage_clicked()
{
    QStringList files = QFileDialog::getOpenFileNames(
                            this,
                            "Выберите изображения",
                            homeDir,
                            "Изображения (*.jpg *.jpeg *.jpe *.jfif *.gif *.png *.bmp *.dib *.tif *.tiff *.wmf *.emf)");
    QImage image = QImage("../addImage.png");
    addItem(files, image);
}

void FileManagerWidget::setIcons()
{
    ui->addAudio->setIcon(QIcon("../addAudio.png"));
    ui->addVideo->setIcon(QIcon("../addVideo.png"));
    ui->addImage->setIcon(QIcon("../addImage.png"));
    ui->record->setIcon(QIcon("../record.png"));
}

void FileManagerWidget::tableViewSettings()
{
    filesModel = new QStandardItemModel(this);
    ui->tableView->setModel(filesModel);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setFocusPolicy(Qt::NoFocus);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void FileManagerWidget::addItem(QStringList & files, QImage & image)
{

    QString fileName;
    foreach (QString filePath, files) {
        image = image.scaled(35,35);
        QStandardItem *itemImage = new QStandardItem();
        itemImage->setData(QVariant(QPixmap::fromImage(image)), Qt::DecorationRole);
        filesModel->setItem(filesModel->rowCount(), 0, itemImage);

        fileName = QDir(filePath).dirName();
        QStandardItem *item = new QStandardItem(fileName);

        StorageService::Instance().allFiles.append(filePath);

        filesModel->setItem(filesModel->rowCount()-1, 1,item);
        ui->tableView->setRowHeight(filesModel->rowCount()-1,40);
    }
    if (files.size() > 0){
        homeDir = files.at(0);
        homeDir.left(homeDir.lastIndexOf("/")+1);
    }
    ui->tableView->setColumnWidth(0,40);
}

void FileManagerWidget::changeSize()
{
    ui->tableView->setGeometry(10,60, this->size().width()-20, this->size().height()-70);
    ui->line->setGeometry(10, 40,this->size().width()-20, 16);
}

void FileManagerWidget::deleteItem()
{
    int size = ui->tableView->selectionModel()->selectedRows().size();
    for(int i = size-1; i >= 0;i--){
        int numb = ui->tableView->selectionModel()->selectedRows().at(i).row();
        filesModel->removeRow(numb);
        StorageService::Instance().allFiles.removeAt(numb);
    }
}

void FileManagerWidget::on_tableView_doubleClicked(const QModelIndex &index)
{
    qDebug() << StorageService::Instance().allFiles.at(index.row());
    emit itemWasClicked(StorageService::Instance().allFiles.at(index.row()));
}
