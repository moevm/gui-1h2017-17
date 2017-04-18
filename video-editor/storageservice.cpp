#include "storageservice.h"
#include <QJsonObject>
#include <QJsonArray>

StorageService::StorageService()
{

}

void StorageService::addFileInfo(MovieMakerFileInfo* fileInfo){
    //todo проверить на существование
    allFiles.append(fileInfo);
}

bool StorageService::saveProject(QString projectName)
{

    QFile saveFile(projectName);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QJsonObject projectObject;
    write(projectObject);
    QJsonDocument saveDoc(projectObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    return true;
}

QList <MovieMakerFileInfo*> StorageService::loadProject(QString projectName)
{

    QFile readFile(projectName);

    if (!readFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return QList <MovieMakerFileInfo*>();
    }

    QByteArray val = readFile.readAll();
    readFile.close();
    QJsonObject object = QJsonDocument::fromJson(val).object();
    allFiles.clear();
    allFiles = read(object);
    return allFiles;
}

void StorageService::write(QJsonObject &jsonObj)
{
    QJsonArray jsonArray;
    foreach (MovieMakerFileInfo* p, allFiles)
    {
        QJsonObject jsonPerson;
        jsonPerson["path"] = p->path;
        jsonPerson["imagePath"] = p->imagePath;
        jsonArray.append(jsonPerson);
    }

    jsonObj["allProjectFiles"] = jsonArray;
}

QList <MovieMakerFileInfo*> StorageService::read(QJsonObject &jsonObj)
{
    QList <MovieMakerFileInfo*> allFiles;
    QJsonArray jsonArray = jsonObj["allProjectFiles"].toArray();
    foreach(QJsonValue object, jsonArray)
    {
        QJsonObject jsonObject = object.toObject();
        MovieMakerFileInfo* info = new MovieMakerFileInfo;
        info->imagePath = jsonObject["imagePath"].toString();
        info->path = jsonObject["path"].toString();
        allFiles.append(info);
    }
    return allFiles;
}
