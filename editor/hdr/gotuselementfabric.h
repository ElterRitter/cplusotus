#pragma once
#include "igotuselement.h"
#include "isettingsstorage.h"


namespace otuseditor {
/*!
 * \brief Класс GotusElementFabric синглтон фабрики элементов документа
 */
class GotusElementFabric
{
public:
    static GotusElementFabric instance()
    {
        static GotusElementFabric fabric;
        return fabric;
    }
    /*!
     * \brief createElementByName функция создания элемента по его имени
     * \param elementId идентификатор элемента
     * \param elemType тип элемента
     * \param settings хранилище настроек создаваемого элемента
     * \return владеющый указатель на созданный элемент
     */
    IGotusElement::SPtr createElementByName(const std::string &elementId,
                                           const std::string &elemType,
                                           const ISettingsStorage::WPtr settings );
    /*!
     * \brief createElement создание элемента по его типу
     * \param type тип создаваемого элемента
     * \param elementId идентификатор элемента. Если пустая строка, то будет создан новый идентификатор
     * \return
     */
    IGotusElement::SPtr createElement(const IGotusElement::Type type, const std::string &elementId = std::string(""));

    /*!
     * \brief makeElementId создание идентификатора для элемента
     * \return идентификатор
     */
    std::string makeElementId() const;

private:
    GotusElementFabric() = default;
};

};
