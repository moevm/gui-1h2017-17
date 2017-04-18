#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <QWidget>
#include <QStandardItem>
#include <QStringList>
#include <QKeyEvent>
#include <QQueue>
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

    void addProjectFileInfo(MovieMakerFileInfo* fileInfo);
    void addLastOpenedFile(MovieMakerFileInfo* fileInfo);

    bool saveProject(QString projectName);
    QList <MovieMakerFileInfo*> loadProject(QString projectName);

    bool saveLastOpenedFiles();
    QList <MovieMakerFileInfo*> loadLastOpenedFiles();
    QList <MovieMakerFileInfo*> getCacheLastOpenedFiles();

    void write(QJsonObject &jsonObj, QList <MovieMakerFileInfo*> fileInfos);
    QList <MovieMakerFileInfo*> read(QJsonObject &jsonObj);


private:
    QString lastOpenedFilesPath = "../lastOpened";

    StorageService();
    QList <MovieMakerFileInfo*> allProjectFiles;

    QQueue <MovieMakerFileInfo*> lastOpenedFiles;
};

#endif // STORAGESERVICE_H
