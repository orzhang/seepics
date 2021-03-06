#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QCursor>
#include <QDropEvent>
#include <QDragEnterEvent>
class ImageWidget : public QWidget
{
    Q_OBJECT

public:
    ImageWidget(QWidget *parent = 0);
    ~ImageWidget();
    void loadImage(const QString & file);
    void fitSize();
    void updateCanvas();
    double getFitZoom();
    void generateBackground(const QSize & size);
protected:
    void paintEvent ( QPaintEvent * event );
    void wheelEvent ( QWheelEvent * event );
    void resizeEvent ( QResizeEvent * event );
    void mouseMoveEvent ( QMouseEvent * event );
    void mousePressEvent ( QMouseEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event );

public slots:
    void resetSize();
    void setZoom(double zoom);
    void clockwise();
    void anticlockwise();
private:


private:
    QRectF m_viewPort;
    QRectF m_oldViewPort;
    QRectF m_canvas;
    QImage m_image;
    QPixmap  m_background;
    QPointF m_oldPoint;
    double m_zoom;
    double m_fitZoom;
    bool m_mousePressed;
    int m_rotate;
    Qt::CursorShape m_cursor;
};

#endif // WIDGET_H
