#pragma once

#include <memory>
#include <string>
#include <list>

namespace otuseditor {

/*!
 * \brief Класс ISettingsStorage обеспечивает интерфейс доступа к хранилищу настроек приложения
 */
class ISettingsStorage
{
public:
    using Ptr = std::unique_ptr<ISettingsStorage>;      ///< "уникальный" указатель на хранилище
    using SPtr = std::shared_ptr<ISettingsStorage>;     ///< "сильный" указатель на хранилище
    using WPtr = std::weak_ptr<ISettingsStorage>;       ///< "слабый" указатель на хранилище
    using stringlist = std::list<std::string>;

    ISettingsStorage() = default;
    virtual ~ISettingsStorage() = default;

    /*!
     * \brief value получить целочисленное значение параметра из хранилища
     * \param key название параметра
     * \param defaultValue значение по-умолчанию для параметра
     * \return значение параметра из хранилища или значение по-умолчанию
     */
    virtual int value(const std::string & key, const int &defaultValue) = 0;

    /*!
     * \brief value получить вещественное значение параметра из хранилища
     * \param key название параметра
     * \param defaultValue значение по-умолчанию для параметра
     * \return значение параметра из хранилища или значение по-умолчанию
     */
    virtual double value(const std::string & key, const double &defaultValue) = 0;

    /*!
     * \brief value получить строковое значение параметра из хранилища
     * \param key название параметра
     * \param defaultValue значение по-умолчанию для параметра
     * \return значение параметра из хранилища или значение по-умолчанию
     */
    virtual std::string value(const std::string & key, std::string &defaultValue) = 0;

    /*!
     * \brief setValue записать целочисленное значение в хранилище
     * \param key название параметра
     * \param value значение параметра
     */
    virtual void setValue(const std::string & key, const int &value) = 0;

    /*!
     * \brief setValue записать вещественное значение в хранилище
     * \param key название параметра
     * \param value значение параметра
     */
    virtual void setValue(const std::string & key, const double &value) = 0;

    /*!
     * \brief setValue записать строковое значение в хранилище
     * \param key название параметра
     * \param value значение параметра
     */
    virtual void setValue(const std::string & key, const std::string &value) = 0;

    /*!
     * \brief beginGroup группировка параметров в рамках логической группы
     * \param groupName название группы
     */
    virtual void beginGroup(const std::string &groupName) = 0;
    /*!
     * \brief endGroup завершение группировки параметров в логическую группу
     */
    virtual void endGroup() = 0;

    /*!
     * \brief keys список ключей в хранилище/логической группе
     * \return строковые наименования ключей из хранилища/логической группы
     */
    virtual stringlist keys() = 0;

    /*!
     * \brief rawStoragePath уникальный строковый идентификатор хранища ( путь к файлу настроек и т.п. )
     * \return строковый идентификатор
     */
    virtual std::string rawStoragePath() const = 0;
};

}
