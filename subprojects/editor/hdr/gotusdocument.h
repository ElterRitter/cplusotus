#pragma once
#include "igotuselement.h"
#include "isettingsstorage.h"
#include "rendercontext.h"

#include <QLoggingCategory>

#include <memory>
#include <vector>

Q_DECLARE_LOGGING_CATEGORY(gotusdocument)

namespace otuseditor {

/*!
 * \brief Клвсс GOtusDocument реализует документ, содержащий графические примитивы ( "элементы" )
 */
class GOtusDocument
{
public:
    using SPtr = std::shared_ptr<GOtusDocument>;              ///< "сильный" указатель на документ
    using WPtr = std::weak_ptr<GOtusDocument>;                ///< "слабый" указатель на документ
    using elements = std::vector<IGotusElement::SPtr>;        ///< тип "хранилищя" документов

    /*!
     * \brief create статическая функция загрузки документа
     * \param settings интерфейс настроек, содержащий данные документа
     * \return владеющий указатель на документ
     */
    static SPtr create(const ISettingsStorage::SPtr settings);

    /*!
     * \brief version получение версии документа
     * \return версия документа
     */
    uint32_t version() const { return m_version; };

    /*!
     * \brief setVersion определение версии документа
     * \param value значение версии документа
     */
    void setVersion(const uint32_t &value);

    /*!
     * \brief settingsPathName идентификатор пути сохранения документов
     * \return строка пути, откуда был загружен документ. Если документ создан не из файлы, будет пустая строка
     */
    std::string settingsPathName() const { return m_settingsPath; }

    /*!
     * \brief render функция отрисовки документа в контексте
     * \param context контекст для отрисовки
     */
    void render(RenderContext &context);

    /*!
     * \brief save сохранение документа в предоставляемое хранилище
     * \param settings интерфейс хранилища
     * \return результат попытки сохранения данных документа в хранилище
     */
    bool save(const ISettingsStorage::WPtr settings);

    /*!
     * \brief addElement добавить предостовляемый элемент в документ
     * \param element элемент для добавления
     */
    void addElement(IGotusElement::SPtr element);

    /*!
     * \brief allElements список всех элементов в документе
     * \return константная ссылка на список всех элементов документа
     */
    const elements& allElements() const { return m_elements; };

    /*!
     * \brief removeElement удаления элемента из документа по его идентификатору
     * \param elementId идентификатор документа
     */
    void removeElement(const std::string &elementId);

    /*!
     * \brief removeAllElements удалить все элементы из документа
     */
    void removeAllElements();

private:
    elements m_elements;
    uint32_t m_version;
    std::string m_settingsPath;

    GOtusDocument();
    bool load(const ISettingsStorage::WPtr settings);
    std::string elementTypeAsString(const IGotusElement::Type &type);
};

};
