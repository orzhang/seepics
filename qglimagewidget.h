#ifndef QGLIMAGEWIDGET_H
#define QGLIMAGEWIDGET_H

#include <QGLWidget>
#include <QImage>
class QGLImageWidget : public QGLWidget
{
public:
    QGLImageWidget(QWidget *parent = 0);
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    QImage m_orignalImage;
    GLuint img;
};

#endif // QGLIMAGEWIDGET_H
