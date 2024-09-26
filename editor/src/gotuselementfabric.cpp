#include "gotuselementfabric.h"

#include "gotuspoint.h"
#include "gotuscircle.h"

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

IGotusElement::SPtr GotusElementFabric::createElementByName(const std::string &elementId,
                                                           const std::string &elemType,
                                                           const ISettingsStorage::WPtr settings)
{
    IGotusElement::SPtr ret;
    if(elemType == "Point")
        ret = GOtusPoint::create(elementId, settings);
    else if(elemType == "Circle")
        ret = GOtusCircle::create(elementId, settings);

    return ret;
}

IGotusElement::SPtr GotusElementFabric::createElement(const IGotusElement::Type type, const std::string &elementId)
{
    IGotusElement::SPtr ret;
    ISettingsStorage::WPtr empty_settings;

    using namespace boost::uuids;
    std::string id = elementId.empty() ? to_string(random_generator()()) : elementId;
    switch(type)
    {
    case IGotusElement::Point:
        ret = GOtusPoint::create(id, empty_settings);
        break;
    case IGotusElement::Circle:
        ret = GOtusPoint::create(id, empty_settings);
        break;
    }

    return ret;
}
