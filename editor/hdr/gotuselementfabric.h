#pragma once
#include "igotuselement.h"
#include "isettingsstorage.h"


namespace otuseditor {
class GotusElementFabric
{
public:
    static GotusElementFabric instance()
    {
        static GotusElementFabric fabric;
        return fabric;
    }

    IGotusElement::SPtr createElementByName(const std::string &elementId,
                                           const std::string &elemType,
                                           const ISettingsStorage::WPtr settings );
    IGotusElement::SPtr createElement(const IGotusElement::Type type, const std::string &elementId = std::string(""));
    std::string makeElementId() const;

private:
    GotusElementFabric() = default;
};

};
