#include "mainwindow.h"
#include <QDir>
#include <QImageReader>
#include <QDebug>
#include <QKeyEvent>
#include <QFileDialog>
#include <QDrag>
#include <QMimeData>
#include <QApplication>
#include <QDesktopWidget>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("SeePICs");
    setAcceptDrops(true);
    setMouseTracking(true);
    m_imageWidget = new ImageWidget(this);
    setCentralWidget(m_imageWidget);
    centralWidget()->setMouseTracking(true);
    m_controlWidget = new ControlWidget(this);
    m_controlWidget->hide();
    m_index = 0;
    m_openAction = new QAction(tr("&Open"), this);
    m_exitAction = new QAction(tr("&Exit"), this);
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_exitAction);
    QObject::connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));
    QObject::connect(m_exitAction, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(m_controlWidget->pushButtonClock(), SIGNAL(clicked()), m_imageWidget, SLOT(clockwise()));
    QObject::connect(m_controlWidget->pushButtonAntiClock(), SIGNAL(clicked()), m_imageWidget, SLOT(anticlockwise()));
    QObject::connect(m_controlWidget->pushButtonFitSize(), SIGNAL(clicked()), m_imageWidget, SLOT(resetSize()));
    QObject::connect(m_controlWidget->pushButtonRight(), SIGNAL(clicked()), this, SLOT(nextImage()));
    QObject::connect(m_controlWidget->pushButtonLeft(), SIGNAL(clicked()), this, SLOT(previousImage()));
}

void MainWindow::LoadImage(const QString & path) {

    QFileInfo info(path);
    QDir dir = info.absoluteDir();
    QList<QByteArray> formats = QImageReader::supportedImageFormats ();
    QStringList formatList;
    for(int i = 0; i < formats.size(); i++) {
        formatList << "*." + formats[i];
    }

    dir.setFilter(QDir::Files | QDir::NoSymLinks);
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
        for(int i = 0; i < m_fileList.size();i++) {
            if(m_fileList[i] == path) {
                m_index = i;
            }
        }
        m_imageWidget->loadImage(path);
        updateTitle();
    }
}

void MainWindow::openFile() {
    QList<QByteArray> formats = QImageReader::supportedImageFormats ();

    QStringList formatList;

    for(int i = 0; i < formats.size(); i++) {
        formatList << "*." + formats[i];
    }

    qDebug()<<formatList;
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", formatList.join(" "));
    if (path != "") {
        LoadImage(path);
    }
}
void MainWindow::nextImage()
{
    if (m_fileList.size() == 0)
        return;

    m_index = (m_index + 1) % m_fileList.size();
    m_imageWidget->loadImage(m_fileList[m_index]);
    updateTitle();
}

void MainWindow::previousImage()
{
    if (m_fileList.size() == 0)
        return;
    m_index --;
    if (m_index < 0) {
        m_index = m_fileList.size() - 1;
    }
    m_imageWidget->loadImage(m_fileList[m_index]);
    updateTitle();
}

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
    if (m_fileList.size() == 0)
        return;
    switch(event->key()) {
        case Qt::Key_Right:
            nextImage();
            break;
        case Qt::Key_Left:
            previousImage();
            break;
        case Qt::Key_Up:
            m_imageWidget->anticlockwise();
            break;
        case Qt::Key_Down:
            m_imageWidget->clockwise();
            break;
        case Qt::Key_Space:
            m_imageWidget->resetSize();
            break;
    }
    updateTitle();
}

void MainWindow::updateTitle()
{
    if(m_fileList.size() > 0) {
        QString fileName = QFileInfo(m_fileList[m_index]).fileName();
        QString title = QString("%1 %2/%3 - SeePICs").arg(fileName).arg(m_index + 1).arg(m_fileList.size());
        setWindowTitle(title);
    }
}

void MainWindow::moveCenter() {

    QWidget * desktop = QApplication::desktop()->screen();
    move((desktop ->width() - width()) / 2,
           (desktop->height() - height()) / 2);
}

void MainWindow::dropEvent(QDropEvent *event)
{
    foreach (QUrl url, event->mimeData()->urls()) {
        qDebug()<<url.toLocalFile();
    }
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void MainWindow::resizeEvent ( QResizeEvent * event )
{
    int x = (rect().width() - m_controlWidget->width()) / 2;
    int y = rect().bottom() - m_controlWidget->height() - 10;
    m_controlWidget->move(x, y);
}

void MainWindow::mouseMoveEvent ( QMouseEvent * event )
{
    int x = (rect().width() - m_controlWidget->width()) / 2;
    int y = rect().bottom() - m_controlWidget->height() - 10;
    int width = m_controlWidget->width();
    int height = m_controlWidget->width();
    x-=10;
    y-=10;
    width += 20;
    height += 20;
    QRect rect(x,y,width,height);
    if(rect.contains(event->pos())) {
        m_controlWidget->show();
    } else {
        m_controlWidget->hide();
    }
}
