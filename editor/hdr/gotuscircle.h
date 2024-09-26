#pragma once
#include "igotuselement.h"
#include "internaltypes.h"
#include "isettingsstorage.h"

/*!
 * \brief Класс GOtusCircle является примитивом окружности
 * \details Отрисовывается залитой красным цветом круг
 */

class GOtusCircle : public IGotusElement
{
public:
    using SPtr = std::shared_ptr<GOtusCircle>;
    /*!
     * \brief create функция создания, используется при загрузке документа из файла
     * \param elementId строка - уникальный идентификатор элемента ( может быть GUID )
     * \param settings указатель на хранилище настроек
     * \return умный указатель на созданный элемент
     */
    static GOtusCircle::SPtr create(const std::string &elementId, const ISettingsStorage::WPtr settings);

    /*!
     * \brief GOtusCircle простой конструктор
     * \param posX координата центра окружности по оси X
     * \param posY координата центра окружности по оси Y
     * \param radius радиус окружности
     */
    GOtusCircle(uint32_t posX, uint32_t posY, uint32_t radius);

    // override members
    void render(RenderContext &context) override;
    std::string id() const override final { return m_elementId; }
    IGotusElement::Type type() const override { return IGotusElement::Circle; }
    bool load(ISettingsStorage::WPtr settings) override final;
    void save(ISettingsStorage::WPtr settings) override final;

    /*!
     * \brief center функция определения центра окружности
     * \return SimplePoint структура, содержащая координаты центра окружности
     */
    const SimplePoint& center() const { return m_center; }
    /*!
     * \brief mutableCenter функция определения и изменения центра окружности
     * \return SimplePoint структура, содержащая координаты центра окружности
     */
    SimplePoint& mutableCenter() { return m_center; }
    /*!
     * \brief setCenter функция изменения центра окружности
     * \param x координата центра по оси X
     * \param y координата центра по оси Y
     */
    void setCenter(uint32_t x, uint32_t y);

    /*!
     * \brief radius радиус
     * \return значение радиуса
     */
    uint32_t radius() const { return m_radius; }

    /*!
     * \brief setRadius изменение радиуса
     * \param value новое значение радиуса
     */
    void setRadius(const uint32_t value) { m_radius = value; }

private:
    std::string m_elementId;
    SimplePoint m_center;
    uint32_t m_radius;

    GOtusCircle(const std::string &id);
};
