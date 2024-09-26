#include "gotusdocument.h"
#include "gotuselementfabric.h"

#include <inttypes.h>

Q_LOGGING_CATEGORY(gotusdocument, "editor.gotusdocument")
#define Debug qDebug(gotusdocument)
#define Warn qWarning(gotusdocument)
#define Info qInfo(gotusdocument)


constexpr uint32_t defaultDocumentVersion = 1;

GOtusDocument::GOtusDocument() : m_version(defaultDocumentVersion)
{

}

GOtusDocument::SPtr GOtusDocument::create(const ISettingsStorage::SPtr settings)
{
    auto ret = std::shared_ptr<GOtusDocument>( new GOtusDocument() );
    ret->load(settings);
    return ret;
}

void GOtusDocument::setVersion(const uint32_t &value)
{
    m_version = value;
}


void GOtusDocument::render(RenderContext &context)
{
    for(const auto &element : m_elements)
    {
        element->render(context);
    }
}

bool GOtusDocument::save(const ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        se->beginGroup("main");
        se->setValue("version", int(defaultDocumentVersion));
        se->endGroup();

        se->beginGroup("elements");
        for(const auto &elem : m_elements)
        {
            auto id = elem->id();
            auto strType = elementTypeAsString(elem->type());
            if(id.empty() || strType.empty())
                continue;

            se->beginGroup(id);
            se->setValue("type", strType);
            elem->save(se);
            se->endGroup();
        }
        se->endGroup();

        return true;
    }

    return false;
}

void GOtusDocument::addElement(IGotusElement::SPtr element)
{
    if(!element)
        return;

    m_elements.emplace_back(element);
}

void GOtusDocument::removeElement(const std::string &elementId)
{
    auto it = std::find_if(m_elements.begin(), m_elements.end(), [elementId](const IGotusElement::SPtr &element) { return element->id() == elementId; });
    if(it == m_elements.end())
        return;

    m_elements.erase(it);
}

void GOtusDocument::removeAllElements()
{
    m_elements.clear();
}

bool GOtusDocument::load(const ISettingsStorage::WPtr settings)
{
    if(auto se = settings.lock())
    {
        std::string defType;
        se->beginGroup("elements");
        auto elems = se->values();
        for(const auto &elem : elems)
        {
            se->beginGroup(elem);
            if(se->values().empty())
                continue;

            auto elemType = se->value("type", defType);
            auto iElem = GotusElementFabric::instance().createElementByName(elem, elemType, settings);
            m_elements.emplace_back(iElem);
            se->endGroup();
        }
        se->endGroup();

        se->beginGroup("main");
        m_version = se->value("version", 1);
        se->endGroup();

        m_settingsPath = se->rawStoragePath();

        return true;
    }
    return false;
}

std::string GOtusDocument::elementTypeAsString(const IGotusElement::Type &type)
{
    switch(type)
    {
    case IGotusElement::Circle: return "Circle"; break;
    case IGotusElement::Point: return "Point"; break;
    }

    return "";
}
