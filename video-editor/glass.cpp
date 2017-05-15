#include "glass.h"
#include "QtDebug"
#include <QGraphicsBlurEffect>

Glass::Glass(): movie(0){
    glass = new QLabel();
    animationContainer = new QLabel();
// Загрузим анимацию по умолчанию
}

// Так как мы не задали родителей для компонент стекла, необходимо
// самостоятельно позаботиться об освобождении памяти
Glass::~Glass() {
    glass->deleteLater();
    movie->deleteLater();
    animationContainer->deleteLater();
}

// Теперь реализуем один из самых важных методов. Установку стекла поверх
// виджета
void Glass::install(QWidget* widget, QString url) {
// Для начала удалим его с предыдущего виджета
    remove();

// Установим стекло поверх виджета
    glass->setParent(widget);
    animationContainer->setParent(glass);
    movie = new QMovie(url, QByteArray(), animationContainer);

    /*QGraphicsBlurEffect * dse = new QGraphicsBlurEffect();
    dse->setBlurRadius(10);
    glass->setGraphicsEffect(dse);*/

    glass->setMovie(movie);

    glass->resize(glass->parentWidget()->width(), glass->parentWidget()->height());
    qDebug() << glass->width() <<glass->height();
    qDebug() << glass->parentWidget()->width()<< glass->parentWidget()->height();
    int glassWidth = glass->width();
    int glassHeight = glass->height();
    int movieWidth = movie->scaledSize().width();
    int movieHeight = movie->scaledSize().height();
    double k = movieHeight/movieWidth;

    if (glassWidth < glassHeight){
        movieWidth = glassWidth;
        movieHeight = (int) (movieWidth * k);
    }
    else{
        movieHeight = glassHeight;
        movieWidth = (int) (movieHeight / k);
    }

    glass->setAlignment(Qt::AlignCenter);
    movie->setScaledSize(QSize(movieWidth,movieHeight));

    movie->start();
    glass->show();
    animationContainer->show();
}

void Glass::remove() {
// Если стекло было установлено, то удаляем его
    if (glass->parentWidget() != 0) {

// Скрываем все компоненты стекла
        glass->hide();
        glass->setParent(0);
        animationContainer->hide();
        animationContainer->setParent(0);
    }
}
