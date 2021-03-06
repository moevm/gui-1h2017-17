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
    bool isContains = false;
    foreach (MovieMakerFileInfo* file, lastOpenedFiles) {
        if(file->path == fileInfo->path){
            isContains = true;
            break;
        }
    }
    if(!isContains)lastOpenedFiles.enqueue(fileInfo);
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

void StorageService::clear(){
    allProjectFiles.clear();
}

MovieMakerFileInfo* StorageService::at(int index)
{
    MovieMakerFileInfo* temp;
    return allProjectFiles.at(index);
}

void StorageService::removeAt(int position)
{
    allProjectFiles.removeAt(position);
}

bool StorageService::saveLastOpenedFiles()
{
    QString lastOpenedFilesContainerPath = lastOpenedFilesPath();
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

    QFile readFile(lastOpenedFilesPath());

    if (!readFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return QList <MovieMakerFileInfo*>();
    }

    QByteArray val = readFile.readAll();
    readFile.close();
    QJsonObject object = QJsonDocument::fromJson(val).object();
    return read(object);
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

void StorageService::saveLastOpenedProjects(){
    QList <MovieMakerFileInfo*> currentSavedFiles = loadLastOpenedFiles();
    QList <MovieMakerFileInfo*> cacheLastOpenedFiles = getCacheLastOpenedFiles();
    if(cacheLastOpenedFiles.length()<5) {

        int difference = 5 - cacheLastOpenedFiles.length();

        foreach (MovieMakerFileInfo* fileInfo, currentSavedFiles) {
            if(difference == 0) break;
            bool isContains = false;
            foreach (MovieMakerFileInfo* cacheFile, cacheLastOpenedFiles) {
                if(cacheFile->path == fileInfo->path){
                    isContains = true;
                    break;
                }
            }
            if(isContains) continue;
            addLastOpenedFile(fileInfo);
            difference--;
        }

    }
    saveLastOpenedFiles();
}
