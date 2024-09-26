#include "gotuspoint.h"
#include "uuidgenerator.h"

#include <QPainter>
#include <QBrush>

constexpr auto keyX = "x";
constexpr auto keyY = "y";

GOtusPoint::GOtusPoint(const std::string &elementID) :
    m_elementId{elementID}, x_{50}, y_{10}
{

}

GOtusPoint::SPtr GOtusPoint::create(const std::string &id, const ISettingsStorage::WPtr settings)
{
    auto ret = std::shared_ptr<GOtusPoint>( new GOtusPoint(id) );
    if(!settings.expired())
        return ret->load(settings) ? ret : nullptr;
    else
        return ret;
}

GOtusPoint::GOtusPoint(uint32_t posX, uint32_t posY) :
    x_(posX), y_(posY)
{
    m_elementId = uuidgenerator::makeID();
}

void GOtusPoint::render(RenderContext &context)
{
    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    QPainter painter;
    painter.begin(context.paintDevice());
    painter.setBrush(brush);
    painter.drawRect(QRect(x_, y_, 4, 4));
    painter.end();
}

bool GOtusPoint::load(const ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        x_ = se->value(keyX, 0);
        y_ = se->value(keyY, 0);
        return true;
    }

    return false;
}

void GOtusPoint::save(ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        se->setValue(keyX, int(x_));
        se->setValue(keyY, int(y_));
    }
}
