#include "window.h"

#include <QMediaPlayer>
#include <QAudioOutput>

#include <QtWidgets/QApplication>
#include <QResource>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    BJ::window* mainWindow = new BJ::window();
    mainWindow->setWindowTitle("Black Jack");
    mainWindow->setWindowIcon(QIcon("zhabka.jpg"));
    mainWindow->show();
    return a.exec();
}


