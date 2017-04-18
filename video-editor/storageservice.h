#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <QWidget>
#include <QStandardItem>
#include <QStringList>
#include <QKeyEvent>
#include <QJsonDocument>

struct MovieMakerFileInfo{
    QString path;
    QString imagePath;
};

class StorageService
{
public:
    static StorageService& Instance()
       {
          static StorageService INSTANCE;
          return INSTANCE;
       }

    void addFileInfo(MovieMakerFileInfo* fileInfo);

    bool saveProject(QString projectName);
    QList <MovieMakerFileInfo*> loadProject(QString projectName);

    void write(QJsonObject &jsonObj);
    QList <MovieMakerFileInfo*> read(QJsonObject &jsonObj);


private:
    StorageService();
    QList <MovieMakerFileInfo*> allFiles;
};

#endif // STORAGESERVICE_H
