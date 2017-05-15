#ifndef GLASS_H
#define GLASS_H

#include <QObject>
#include <QColor>
#include <QMovie>
#include <QLabel>

class Glass: public QObject
{
    Q_OBJECT
public:
    Glass();
    virtual ~Glass();

    //установка и снятие эффекта
    virtual void install(QWidget* widget, QString url);
    virtual void remove();
    void setMovie(QMovie* movie);

    //поля компонентов стекла
    QLabel* glass;
    QMovie* movie;
    QLabel* animationContainer;
};

#endif // GLASS_H
