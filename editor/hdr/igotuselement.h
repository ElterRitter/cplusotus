#pragma once
#include "rendercontext.h"
#include "isettingsstorage.h"
#include <memory>
#include <string>

namespace otuseditor {
/*!
 * \brief Интерфейс IGotusElement элемента
 */
class IGotusElement
{
public:
    using SPtr = std::shared_ptr<IGotusElement>;    ///< владеющий указатель
    using WPtr = std::weak_ptr<IGotusElement>;      ///< невладеющий указатель

    IGotusElement() = default;
    virtual ~IGotusElement() = default;

    enum Type
    {
        Point,  ///< тип элемента "точка"
        Circle  ///< тип элемента "окружность"
    };

    /*!
     * \brief render функция отрисовки элемента в контексте
     * \param context контекст, где нужно нарисовать элемент
     */
    virtual void render(RenderContext &context) = 0;

    /*!
     * \brief id идентификатор элемента
     * \return строковое представление идентификатора элемента
     */
    virtual std::string id() const = 0;

    /*!
     * \brief type тип элемента
     * \return тип элемента
     */
    virtual Type type() const = 0;

    /*!
     * \brief load загружает элемент из хранилища
     * \param settings
     * \return результат загрузки элемента ( false, например, если данные в хранилище повреждены )
     */
    virtual bool load(const ISettingsStorage::WPtr settings) = 0;

    /*!
     * \brief save сохраняет ( сериализует ) элемент в предоставляемое хранилище
     * \param settings интерфейс хранилища
     */
    virtual void save(ISettingsStorage::WPtr settings) = 0;
};

};
