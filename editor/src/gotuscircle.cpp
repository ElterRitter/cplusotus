#include "gotuscircle.h"
#include "uuidgenerator.h"

#include <QPainter>
#include <QBrush>



constexpr auto keyRadius = "radius";
constexpr int defaultRadius = 30;
constexpr auto keyCenterX = "x";
constexpr int defaultX = 0;
constexpr auto keyCenterY = "y";
constexpr int defaultY = 0;

GOtusCircle::SPtr GOtusCircle::create(const std::string &elementId, const ISettingsStorage::WPtr settings)
{
    auto ret = std::shared_ptr<GOtusCircle>(new GOtusCircle(elementId) );
    if(!settings.expired())
        return ret->load(settings) ? ret : nullptr;
    else
        return ret;
}

GOtusCircle::GOtusCircle(const std::string &id) :
    m_elementId{id},
    m_center(0, 0),
    m_radius(0)
{

}

GOtusCircle::GOtusCircle(uint32_t posX, uint32_t posY, uint32_t radius) :
    m_center(posX, posY)
    , m_radius(radius)
{
    m_elementId = uuidgenerator::makeID();
}

void GOtusCircle::render(RenderContext &context)
{
    QBrush brush(Qt::SolidPattern);
    brush.setColor(Qt::red);

    QRect rect(m_center.x_ - m_radius, m_center.y_ - m_radius, m_radius*2, m_radius*2);

    QPainter painter;
    painter.begin(context.paintDevice());
    painter.setBrush(brush);
    painter.drawEllipse(rect);
    painter.end();
}

bool GOtusCircle::load(ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        m_center.x_ = se->value(keyCenterX, defaultX);
        m_center.y_ = se->value(keyCenterY, defaultY);
        m_radius = se->value(keyRadius, defaultRadius);
        return true;
    }

    return false;
}

void GOtusCircle::save(ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        se->setValue(keyCenterX, int(m_center.x_));
        se->setValue(keyCenterY, int(m_center.y_));
        se->setValue(keyRadius, int(m_radius));
    }
}

void GOtusCircle::setCenter(uint32_t x, uint32_t y)
{
    m_center.x_ = x;
    m_center.y_ = y;
}
