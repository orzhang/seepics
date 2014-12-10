#include "ImageWidget.h"
#include <QApplication>
#include <QString>
#include <QDir>
#include <QDebug>
#include <QDesktopWidget>
#include "mainwindow.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    if (argc == 2) {
        w.LoadImage(argv[1]);
    }
    w.show();
    w.move((QApplication::desktop()->width() - w.width())/2,
           (QApplication::desktop()->height() - w.height())/2);
    return a.exec();
}
