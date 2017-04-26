#include "mainwindow.h"
#include <QApplication>

#include <QProcess>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

//    QProcess _FFMPEG;
//    QString _process = "ffmpeg";
//    QStringList _paramList;
//    _paramList << "-i"
//               << "-gravity.avi"
//               << "-acodec"
//               << "pcm_s16le"
//               << "outputAudioFile.wav";
//    _FFMPEG.start((_process, _paramList));
//    if (!(_FFMPEG.waitForFinished())){
//        qDebug() << "Conversion failed:" << _FFMPEG.errorString();
//    }
//    else{
//        qDebug() << "Conversion output:" << _FFMPEG.readAll();
//    }

    return a.exec();
}
