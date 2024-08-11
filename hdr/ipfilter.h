#pragma once

#include <vector>
#include <cstdint>
#include <istream>

/*!
 * \brief Класс дз-2 для фильтрации ip-адресов по произвольным параметрам
 */

class IpFilter
{
public:
    /*!
     * \brief iplist псевдоним вектора ip-адресов для удобного сокращения
     */
    using iplist = std::vector<uint32_t>;
    /*!
     * \brief конструктор
     * \param stream поток, содержащий список адресов
     */
    explicit IpFilter(std::istream &stream);

    /*!
     * \brief функция сортировка ip-адресов в порядке возрастания
     * \return копию отсортированного списока
     */
    iplist filter();

    /*!
     * \brief функция фильтрации ip-адресов, первый байт которых равен аргументу
     * \param value значение первого байта, который должен присутствовать в адресе
     * \return список адресов, первый байт которых равен аргументу функции
     */
    iplist filterBySingleValue(const uint32_t value);

    /*!
     * \brief функция фильтрации ip-адресов, по первому и второму байту
     * \param value значение первого и второго байта в ip-адресе
     * \return список адресов, первый и второй байт которых равен аргументу функции
     */
    iplist filterByBytes(const uint16_t value);

    /*!
     * \brief фильтрует список ip-адресов по наличию в адресе байта равного аргументу
     * \param value байт, который должен присутствовать в адресе
     * \return список адресов, где присутствует байт из аргумента
     */
    iplist filterByAnyByte(const uint8_t value);

    /*!
     * \brief функция выводит в стадартный поток вывода ( cout ) переданный ей список ip-адресов в строковом представлении
     * \param value список адресов, которые нужно вывести в стандартный поток
     */
    void print(const iplist&& value);

private:
    iplist m_listAddresses;
};
