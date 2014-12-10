#include "mainwindow.h"
#include <QDir>
#include <QImageReader>
#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(640, 480);
    m_imageWidget = new ImageWidget(this);
    this->setCentralWidget(m_imageWidget);
    m_index = 0;
    m_openAction = new QAction(tr("&Open"), this);
    m_exitAction = new QAction(tr("&Exit"), this);
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_exitAction);
    QObject::connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
}


void MainWindow::LoadImage(const QString & path) {

    QFileInfo info(path);
    QDir dir = info.absoluteDir();
    QList<QByteArray> formats = QImageReader::supportedImageFormats ();

    QStringList formatList;
    for(int i = 0; i < formats.size(); i++) {
        formatList << "*." + formats[i];
    }

    dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    dir.setSorting(QDir::Name);
    dir.setNameFilters(formatList);

    QFileInfoList list = dir.entryInfoList();
    m_index = 0;
    m_fileList.clear();

    for (int i = 0; i < list.size(); ++i) {
        QFileInfo fileInfo = list.at(i);
        m_fileList << fileInfo.absoluteFilePath();
    }
    if (m_fileList.size() != 0) {
        m_imageWidget->loadImage(m_fileList[m_index]);
        setWindowTitle(QFileInfo(m_fileList[m_index]).fileName() + " - SeePICs");
    }
}

void MainWindow::openFile() {
    QList<QByteArray> formats = QImageReader::supportedImageFormats ();

    QStringList formatList;

    for(int i = 0; i < formats.size(); i++) {
        formatList << "*." + formats[i];
    }
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", formatList.join(" "));
    if (path != "") {
        LoadImage(path);
    }
}

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
    if (m_fileList.size() == 0)
        return;
    switch(event->key()) {
        case Qt::Key_Right:
                m_index = (m_index + 1) % m_fileList.size();
                m_imageWidget->loadImage(m_fileList[m_index]);
            break;
        case Qt::Key_Left:
                m_index --;
                if (m_index < 0) {
                    m_index = m_fileList.size() - 1;
                }
                m_imageWidget->loadImage(m_fileList[m_index]);
            break;
        case Qt::Key_Up:
            m_imageWidget->clockwise();
            break;
        case Qt::Key_Down:
            m_imageWidget->anticlockwise();
            break;
        case Qt::Key_Space:
                m_index = (m_index + 1) % m_fileList.size();
                m_imageWidget->loadImage(m_fileList[m_index]);
            break;
    }
    setWindowTitle(QFileInfo(m_fileList[m_index]).fileName() + " - SeePICs");
}
