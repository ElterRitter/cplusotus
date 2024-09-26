#pragma once
#include <QRect>
#include <QPaintDevice>

class RenderContext
{
public:
    explicit RenderContext(const QRect &repaintedRect, QPaintDevice *ptr);

    const QRect rect() const { return m_rect; };
    QPaintDevice* paintDevice() { return m_device; }

private:
    const QRect m_rect;
    QPaintDevice *m_device;
};
