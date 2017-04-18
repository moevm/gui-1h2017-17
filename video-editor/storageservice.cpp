#include "storageservice.h"
#include <QJsonObject>
#include <QJsonArray>
#include <QQueue>

StorageService::StorageService()
{

}

void StorageService::addProjectFileInfo(MovieMakerFileInfo* fileInfo){
    //todo проверить на существование
    allProjectFiles.append(fileInfo);
}

void StorageService::addLastOpenedFile(MovieMakerFileInfo* fileInfo){
    if(lastOpenedFiles.length() > 5){
        lastOpenedFiles.dequeue();
    }
    lastOpenedFiles.enqueue( fileInfo);

}

bool StorageService::saveProject(QString projectName)
{

    QFile saveFile(projectName);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QJsonObject projectObject;
    write(projectObject, allProjectFiles);
    QJsonDocument saveDoc(projectObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    return true;
}

bool StorageService::saveLastOpenedFiles()
{
    QString lastOpenedFilesContainerPath = lastOpenedFilesPath;
    QFile saveFile(lastOpenedFilesContainerPath);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QJsonObject projectObject;
    write(projectObject, lastOpenedFiles);
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
    allProjectFiles.clear();
    allProjectFiles = read(object);
    return allProjectFiles;
}

QList <MovieMakerFileInfo*> StorageService::loadLastOpenedFiles()
{

    QFile readFile(lastOpenedFilesPath);

    if (!readFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return QList <MovieMakerFileInfo*>();
    }

    QByteArray val = readFile.readAll();
    readFile.close();
    QJsonObject object = QJsonDocument::fromJson(val).object();
    allProjectFiles.clear();
    allProjectFiles = read(object);
    return allProjectFiles;
}

QList <MovieMakerFileInfo*> StorageService::getCacheLastOpenedFiles(){
    return lastOpenedFiles;
}

void StorageService::write(QJsonObject &jsonObj, QList <MovieMakerFileInfo*> fileInfos)
{
    QJsonArray jsonArray;
    foreach (MovieMakerFileInfo* p, fileInfos)
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
