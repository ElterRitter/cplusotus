#include "rendercontext.h"

RenderContext::RenderContext(const QRect &repaintedRect, QPaintDevice *ptr) :
    m_rect{repaintedRect},
    m_device{ptr}
{

}
