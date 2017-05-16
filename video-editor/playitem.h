#ifndef PLAYITEM_H
#define PLAYITEM_H

struct PlayItem{
    int begin;
    int end;
    QString url;
    qint64 absBegin;
    qint64 absEnd;
};

#endif // PLAYITEM_H
