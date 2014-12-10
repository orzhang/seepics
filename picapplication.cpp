#include "picapplication.h"
#include <QEvent>
#include <QDebug>
#include <QFileOpenEvent>
#include <QMessageBox>
PicApplication::PicApplication(int &argc, char **argv) :
    QApplication(argc, argv)
{
}

void PicApplication::loadFile(const QString &file) {
    emit eventLoadFile(file);
}

bool PicApplication::event(QEvent * event) {
    switch (event->type()) {
    case QEvent::FileOpen:
        loadFile(static_cast<QFileOpenEvent*>(event)->file());
        return true;
    default:
        return QApplication::event(event);
    }
}
