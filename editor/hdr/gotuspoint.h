#pragma once
#include "igotuselement.h"
#include "isettingsstorage.h"

#include <inttypes.h>

class GOtusPoint : public IGotusElement
{
public:
    using SPtr = std::shared_ptr<GOtusPoint>;
    static GOtusPoint::SPtr create(const std::string &id, const ISettingsStorage::WPtr settings);

    GOtusPoint(uint32_t posX, uint32_t posY);

    // overrided members
    void render(RenderContext &context) override final;
    std::string id() const override final { return m_elementId; }
    IGotusElement::Type type() const override final { return IGotusElement::Point; }
    bool load(const ISettingsStorage::WPtr settings) override final;
    void save(ISettingsStorage::WPtr settings) override final;

    uint32_t x() const { return x_; }
    uint32_t y() const { return y_; }
    void setPoint(uint32_t x, uint32_t y) { x_ = x; y_ = y; };

private:
    std::string m_elementId;
    uint32_t x_;
    uint32_t y_;

    explicit GOtusPoint(const std::string &elementID);
};
