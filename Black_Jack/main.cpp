#include "BJ_window.h"

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QtWidgets/QApplication>
#include <QResource>
#include <iostream>



int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    BJwindow* mainWindow = new BJwindow();
    mainWindow->setWindowTitle("Black Jack");
    mainWindow->setWindowIcon(QIcon("zhabka.jpg"));
    mainWindow->show();
    return a.exec();
}


