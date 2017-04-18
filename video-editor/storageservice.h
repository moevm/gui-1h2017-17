#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H
#include <QWidget>
#include <QStandardItem>
#include <QStringList>
#include <QKeyEvent>
#include <QJsonDocument>

class StorageService
{
public:
    static StorageService& Instance()
       {
          static StorageService INSTANCE;
          return INSTANCE;
       }
    QList <QUrl> allFiles;


    bool saveProject(QString projectName);
    bool loadProject(QString projectName);

    void write(QJsonObject &jsonObj);
    QList <QUrl> read(QJsonObject &jsonObj);


private:
    StorageService();

};

#endif // STORAGESERVICE_H
