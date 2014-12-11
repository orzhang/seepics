#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ImageWidget.h"
#include <QMenu>
#include <QMenuBar>
#include "controlwidget.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    void updateTitle();
    void moveCenter();
protected:
    void keyPressEvent ( QKeyEvent * event );
    void dropEvent(QDropEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void resizeEvent ( QResizeEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
signals:
public slots:
    void LoadImage(const QString & path);
    void openFile();
    void nextImage();
    void previousImage();
private:
    ImageWidget * m_imageWidget;
    ControlWidget * m_controlWidget;
    QStringList m_fileList;
    QMenu * m_fileMenu;
    QAction * m_openAction;
    QAction * m_exitAction;
    int m_index;
};

#endif // MAINWINDOW_H
