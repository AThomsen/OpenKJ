#ifndef CDGVIDEOWIDGET_H
#define CDGVIDEOWIDGET_H

#ifdef USE_GL
    #include <QGLWidget>
#else
    #include <QWidget>
#endif
#include "settings.h"
#include <QMutex>

#ifdef USE_GL
class CdgVideoWidget : public QGLWidget
#else
class CdgVideoWidget : public QWidget
#endif
{
    Q_OBJECT
public:
    explicit CdgVideoWidget(QWidget *parent = 0);
    QSize sizeHint() const;
    void clear();
    void setKeepAspect(bool keep);
    void arResize(int w);
    void setSmoothScaling(bool smoothScaling);
    void present(QImage frame);

private:
    QImage currentFrame;
    QMutex frameMutex;
    bool smoothScaling;
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

signals:
    void resized(QSize size);
    void mouseMoveEvent(QMouseEvent *event);


    // QWidget interface
public:
    QSize minimumSizeHint() const;
    int heightForWidth(int width) const;
};

#endif // CDGVIDEOWIDGET_H
