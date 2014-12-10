#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageWidget.h"
#include <QMenu>
#include <QMenuBar>
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
protected:
    void keyPressEvent ( QKeyEvent * event );
signals:

public slots:
    void LoadImage(const QString & path);
    void openFile();
private:
    ImageWidget * m_imageWidget;
    QStringList m_fileList;
    QMenu * m_fileMenu;
    QAction * m_openAction;
    QAction * m_exitAction;
    int m_index;
};

#endif // MAINWINDOW_H
