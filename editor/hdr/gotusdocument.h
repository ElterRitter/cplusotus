#pragma once
#include "igotuselement.h"
#include "isettingsstorage.h"
#include "rendercontext.h"

#include <QLoggingCategory>

#include <memory>
#include <vector>

Q_DECLARE_LOGGING_CATEGORY(gotusdocument)

class GOtusDocument
{
public:
    using SPtr = std::shared_ptr<GOtusDocument>;
    using WPtr = std::weak_ptr<GOtusDocument>;
    using elements = std::vector<IGotusElement::SPtr>;

    static SPtr create(const ISettingsStorage::SPtr settings);

    uint32_t version() const { return m_version; };
    void setVersion(const uint32_t &value);

    std::string settingsPathName() const { return m_settingsPath; }

    void render(RenderContext &context);

    bool save(const ISettingsStorage::WPtr settings);

    void addElement(IGotusElement::SPtr element);
    const elements& allElements() const { return m_elements; };
    void removeElement(const std::string &elementId);
    void removeAllElements();

private:
    elements m_elements;
    uint32_t m_version;
    std::string m_settingsPath;

    GOtusDocument();
    bool load(const ISettingsStorage::WPtr settings);
    std::string elementTypeAsString(const IGotusElement::Type &type);
};
