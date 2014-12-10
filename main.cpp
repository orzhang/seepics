#include "ImageWidget.h"
#include <QApplication>
#include <QString>
#include <QDir>
#include <QDebug>
#include "mainwindow.h"
#include "picapplication.h"
int main(int argc, char *argv[])
{
    PicApplication a(argc, argv);
    MainWindow w;
    QObject::connect(&a, SIGNAL(eventLoadFile(const QString&)),
                     &w,SLOT(LoadImage(const QString&)));
    w.show();
    w.moveCenter();
    return a.exec();
}
