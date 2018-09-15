#include "cdgvideowidget.h"
#include <QVideoSurfaceFormat>
#include <QPainter>
#include <QPaintEvent>
#include <QRegion>
#include <QDebug>

extern Settings *settings;

#ifdef USE_GL
CdgVideoWidget::CdgVideoWidget(QWidget *parent) : QGLWidget(parent)
#else
CdgVideoWidget::CdgVideoWidget(QWidget *parent) : QWidget(parent) , surface(0)
#endif
{
    setUpdatesEnabled(true);
    setAutoFillBackground(false);
    setAttribute(Qt::WA_NoSystemBackground, true);
    QPalette palette = this->palette();
    palette.setColor(QPalette::Background, Qt::black);
    setPalette(palette);
}


QSize CdgVideoWidget::sizeHint() const
{
    return QSize(300,216);
}

void CdgVideoWidget::clear()
{
    present(QImage());
}

void CdgVideoWidget::arResize(int w)
{
    int h = w * .5625;
    this->setMinimumSize(QSize(w, h));
    this->adjustSize();
}

void CdgVideoWidget::setSmoothScaling(bool smoothScaling)
{
    this->smoothScaling = smoothScaling;
}

void CdgVideoWidget::present(QImage frame)
{
    this->frameMutex.lock();
    this->currentFrame = frame;
    this->frameMutex.unlock();
    this->update();
}


void CdgVideoWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    emit resized(event->size());
    update();
}

void CdgVideoWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    this->frameMutex.lock();
    if(!this->currentFrame.isNull())
    {
        painter.setRenderHint(this->smoothScaling ? QPainter::SmoothPixmapTransform : QPainter::Antialiasing);
        QRect rect = painter.viewport();
        QSize size = this->currentFrame.size();
        size.scale(rect.size(), Qt::KeepAspectRatio);
        QRect targetRect = QRect(rect.topLeft(), size);
        targetRect.moveCenter(rect.center());
        painter.setViewport(targetRect);
        painter.setWindow(this->currentFrame.rect());
        painter.drawImage(0, 0, this->currentFrame);
    }
    else
    {
        painter.fillRect(event->rect(), QBrush(Qt::black));
    }
    this->frameMutex.unlock();
}


QSize CdgVideoWidget::minimumSizeHint() const
{
    return QSize(300,216);
}

int CdgVideoWidget::heightForWidth(int width) const
{
    return width * .72;
}
