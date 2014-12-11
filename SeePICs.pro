#-------------------------------------------------
#
# Project created by QtCreator 2014-12-08T12:47:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += qt warn_on thread create_prl link_prl
macx {
LIBS    += -framework Carbon
}
TARGET = SeePics
TEMPLATE = app
QMAKE_INFO_PLIST = Info.plist

SOURCES += main.cpp\
    ImageWidget.cpp \
    mainwindow.cpp \
    picapplication.cpp \
    controlwidget.cpp

HEADERS  += \
    ImageWidget.h \
    mainwindow.h \
    picapplication.h \
    controlwidget.h

RESOURCES += \
    resource.qrc

FORMS += \
    controlwidget.ui
