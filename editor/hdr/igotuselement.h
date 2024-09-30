#pragma once
#include "rendercontext.h"
#include "isettingsstorage.h"
#include <memory>
#include <string>

namespace otuseditor {
class IGotusElement
{
public:
    using SPtr = std::shared_ptr<IGotusElement>;
    using WPtr = std::weak_ptr<IGotusElement>;

    IGotusElement() = default;
    virtual ~IGotusElement() = default;

    enum Type
    {
        Point,
        Circle
    };

    virtual void render(RenderContext &context) = 0;
    virtual std::string id() const = 0;
    virtual Type type() const = 0;
    virtual bool load(const ISettingsStorage::WPtr settings) = 0;
    virtual void save(ISettingsStorage::WPtr settings) = 0;
};

};
