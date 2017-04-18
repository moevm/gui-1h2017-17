#include "storageservice.h"
#include <QJsonObject>
#include <QJsonArray>

StorageService::StorageService()
{

}



bool StorageService::saveProject(QString projectName)
{

    QFile saveFile(projectName);

    if (!saveFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QJsonObject projectObject;
    StorageService::Instance().write(projectObject);
    QJsonDocument saveDoc(projectObject);
    saveFile.write(saveDoc.toJson());
    saveFile.close();

    return true;
}

bool StorageService::loadProject(QString projectName)
{

    QFile readFile(projectName);

    if (!readFile.open(QIODevice::ReadWrite)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QByteArray val = readFile.readAll();
    readFile.close();
    QJsonObject object = QJsonDocument::fromJson(val).object();
    StorageService::Instance().allFiles.clear();
    StorageService::Instance().allFiles = StorageService::Instance().read(object);
    return true;
}

void StorageService::write(QJsonObject &jsonObj)
{
    QJsonArray jsonArray;
    foreach (QUrl p, StorageService::Instance().allFiles)
    {
        QJsonObject jsonPerson;
        jsonPerson["path"] = p.path();
        jsonArray.append(jsonPerson);
    }

    jsonObj["allProjectFiles"] = jsonArray;
}

QList <QUrl> StorageService::read(QJsonObject &jsonObj)
{
    QList <QUrl> allFiles;
    QJsonArray jsonArray = jsonObj["allProjectFiles"].toArray();
    foreach(QJsonValue path, jsonArray)
    {
        allFiles.append(path.toString());
    }
    return allFiles;
}
