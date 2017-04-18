#include "storageservice.h"
#include <QJsonObject>
#include <QJsonArray>

StorageService::StorageService()
{

}



bool StorageService::saveProject(QString projectName)
{

    QFile saveFile(projectName);

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Доступ к файлу заблокирован.");
        return false;
    }

    QJsonObject projectObject;
    StorageService::Instance().write(projectObject);
    QJsonDocument saveDoc(projectObject);
    saveFile.write(saveDoc.toJson());

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
