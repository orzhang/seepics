#include "ImageWidget.h"
#include <QImage>
#include <QPainter>
#include <QWheelEvent>
#include <QDebug>
#include <QSize>


#define IMAGE_SCALE_FACTOR (0.02)
#define IMAGE_ZOOM_MAX (4.0)
#define IMAGE_ZOOM_MIN (0.02)

ImageWidget::ImageWidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(640, 480);
    m_rotate = 0;
    m_image = QImage(640, 480, QImage::Format_RGB32);
    m_background = QPixmap (m_image.size());
    m_image.fill(Qt::gray);
    m_cursor = Qt::ArrowCursor;
    m_mousePressed = false;
    fitSize();
    updateCanvas();
    update();
}

ImageWidget::~ImageWidget()
{

}

void ImageWidget::loadImage(const QString &file)
{

    m_image.load(file);
    m_rotate = 0;
    m_zoom = getFitZoom();
    m_fitZoom = getFitZoom();
    resetSize();
    generateBackground(m_image.size()*m_zoom);
}

void ImageWidget::resetSize()
{
    fitSize();
    updateCanvas();
    if (m_image.height() < rect().height() && m_image.width() < rect().width()) {
        setZoom(1);
        updateCanvas();
    }
}

void ImageWidget::clockwise()
{
    m_rotate = 90;
    QTransform myTransform;
    myTransform.rotate(m_rotate);
    m_image = m_image.transformed(myTransform);
    fitSize();
    updateCanvas();
    update();
}

void ImageWidget::anticlockwise()
{
    m_rotate = -90;
    QTransform myTransform;
    myTransform.rotate(m_rotate);
    m_image = m_image.transformed(myTransform);
    fitSize();
    updateCanvas();
    update();
}

void ImageWidget::paintEvent ( QPaintEvent * event )
{
    QPainter p(this);

    p.fillRect(rect(), QBrush(Qt::black));

    if (m_image.hasAlphaChannel()) {
        p.drawPixmap(m_canvas.x(), m_canvas.y(), m_background);
    }

    p.scale(m_zoom, m_zoom);


    p.drawImage(qRound(m_canvas.x() / m_zoom),
                qRound(m_canvas.y() / m_zoom),
                m_image,
                qRound(m_viewPort.x() / m_zoom),
                qRound(m_viewPort.y() / m_zoom),
                qRound(m_viewPort.width() /m_zoom),
                qRound(m_viewPort.height()/m_zoom));

}

void ImageWidget::updateCanvas()
{
    double width = m_image.width() * m_zoom;
    double height = m_image.height() * m_zoom;
    int x = (rect().width() - width) / 2 ;
    int y = (rect().height() - height) /2 ;

    m_canvas.setWidth(rect().width());
    m_canvas.setHeight(rect().height());
    m_viewPort.setWidth(m_canvas.width());
    m_viewPort.setHeight(m_canvas.height());
    setZoom(m_zoom);

    if (x < 0)
        x = 0;
    if (y < 0)
        y = 0;
    m_canvas.setX(x);
    m_canvas.setY(y);
}

void ImageWidget::setZoom(double zoom)
{
    QRectF newViewPort = m_viewPort;
    double oldZoom = m_zoom;
    double scale = 0;
    double min = 1;
    if(zoom < qMin(min, getFitZoom()))
        zoom = qMin(min, getFitZoom());
    if(zoom < IMAGE_ZOOM_MIN) {
        zoom = IMAGE_ZOOM_MIN;
    }
    if (zoom > IMAGE_ZOOM_MAX) {
        zoom = IMAGE_ZOOM_MAX;
    }
    m_zoom = zoom;
    scale = m_zoom / oldZoom;
    double width = m_image.width() * zoom;
    double height = m_image.height() * zoom;

    QPointF center = m_viewPort.center() * scale;

    newViewPort.moveCenter(center);

    if(newViewPort.right() > width) {
        newViewPort.moveRight(width);
    }
    if(newViewPort.left() < 0) {
        newViewPort.moveLeft(0);
    }

    if(newViewPort.bottom() > height) {
        newViewPort.moveBottom(height);
    }
    if(newViewPort.top() < 0) {
        newViewPort.moveTop(0);
    }
    m_viewPort = newViewPort;
    if (m_zoom > getFitZoom()) {
        m_cursor = Qt::OpenHandCursor;
        setCursor(m_cursor);

    } else {
        m_cursor = Qt::ArrowCursor;
        setCursor(m_cursor);
    }
    generateBackground(m_image.size() * m_zoom);
    update();
}

void ImageWidget::wheelEvent ( QWheelEvent * event )
{
    double zoom = m_zoom;
    if(event->delta() > 10){
        zoom -= IMAGE_SCALE_FACTOR;
    } else if (event->delta() < -10){
        zoom += IMAGE_SCALE_FACTOR;
    }
    setZoom(zoom);
    updateCanvas();
}

double ImageWidget::getFitZoom()
{
    double z1;
    double z2;
    double z3;
    z1 = (double)rect().height() / (double) m_image.height();
    z2 = (double)rect().width() / (double) m_image.width();
    int zoom = qMin(z1, z2) * 1000;
    int sub = zoom % static_cast<int>(IMAGE_SCALE_FACTOR * 1000);
    z3 = (zoom - sub) / 1000.0;
    return z3;
}

void ImageWidget::fitSize()
{

    double z0 = getFitZoom();

    if (m_fitZoom <= m_zoom) {
        m_zoom = z0;
    }
    m_fitZoom = z0;

}

void ImageWidget::mouseMoveEvent ( QMouseEvent * event )
{

    QPointF newPoint = event->pos();
    QWidget::mouseMoveEvent(event);
    double dx = (newPoint.x() - m_oldPoint.x()) * m_zoom;
    double dy = (newPoint.y() - m_oldPoint.y()) * m_zoom;
    double width = m_image.width() * m_zoom;
    double height = m_image.height() * m_zoom;
    if (m_mousePressed == false)
        return;
    m_viewPort.moveLeft(m_oldViewPort.left() - dx);

    if (m_viewPort.right() > width) {
        m_viewPort.moveRight(width);
    }

    if (m_viewPort.left() < 0) {
        m_viewPort.moveLeft(0);
    }

    m_viewPort.moveTop(m_oldViewPort.top() - dy);

    if (m_viewPort.bottom() > height) {
        m_viewPort.moveBottom(height);
    }

    if (m_viewPort.top() < 0) {
        m_viewPort.moveTop(0);
    }
    update();
}

void ImageWidget::mousePressEvent ( QMouseEvent * event )
{
    m_mousePressed = true;
    m_oldPoint = event->pos();
    m_oldViewPort = m_viewPort;
    if (m_cursor == Qt::OpenHandCursor) {
        m_cursor = Qt::ClosedHandCursor;
        setCursor(Qt::ClosedHandCursor);
    }
}

void ImageWidget::mouseReleaseEvent ( QMouseEvent * event )
{
    m_mousePressed = false;
    if (m_cursor == Qt::ClosedHandCursor) {
        m_cursor = Qt::OpenHandCursor;
        setCursor(Qt::OpenHandCursor);
    }
}

void ImageWidget::resizeEvent ( QResizeEvent * event )
{
    fitSize();
    updateCanvas();
    generateBackground(m_image.size() * m_zoom);
}


void ImageWidget::generateBackground(const QSize & size)
{
    int bs = 10;
    if (!m_image.hasAlphaChannel())
        return;
    m_background = QPixmap(size);
    QPainter p(&m_background);
    int x = (size.width() + bs) / bs;
    int y = (size.height() + bs) / bs;
    for(int i = 0; i < y; i++) {
        for(int j = 0; j < x; j++) {
            if ((i +j ) % 2){
                p.fillRect(j*bs,i*bs,bs,bs,QBrush(Qt::gray));
            } else {
                p.fillRect(j*bs,i*bs,bs,bs,QBrush(QColor(230,230,230)));
            }
        }
    }
}
