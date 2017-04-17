#ifndef STORAGESERVICE_H
#define STORAGESERVICE_H


class StorageService
{
public:
    static StorageService& Instance()
       {
          static StorageService INSTANCE;
          return INSTANCE;
       }
private:
    StorageService();
};

#endif // STORAGESERVICE_H
