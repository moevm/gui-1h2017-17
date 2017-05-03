#include "glass.h"
#include "QtDebug"
#include <QGraphicsBlurEffect>

Glass::Glass(): defaultMovie(0){
    glass = new QLabel();

// Загрузим анимацию по умолчанию
    defaultMovie = new QMovie("../gifka.gif", QByteArray());
}

// Так как мы не задали родителей для компонент стекла, необходимо
// самостоятельно позаботиться об освобождении памяти
Glass::~Glass() {
    glass->deleteLater();
    defaultMovie->deleteLater();
}

// Теперь реализуем один из самых важных методов. Установку стекла поверх
// виджета
void Glass::install(QWidget* widget) {
// Для начала удалим его с предыдущего виджета
    remove();
    //для коммита

// Установим стекло поверх виджета
    glass->setParent(widget);

    QGraphicsBlurEffect * dse = new QGraphicsBlurEffect();
    dse->setBlurRadius(10);
    glass->setGraphicsEffect(dse);

    glass->setMovie(defaultMovie);
    defaultMovie->start();

    glass->show();
}

// Удаление виджета противоположно установке
void Glass::remove() {
// Если стекло было установлено, то удаляем его
    if (glass->parentWidget() != 0) {
// Перестаем отлавливать события на низлежащем виджете
        glass->parentWidget()->removeEventFilter(this);

// Скрываем все компоненты стекла
        glass->hide();
        glass->setParent(0);
    }
}

