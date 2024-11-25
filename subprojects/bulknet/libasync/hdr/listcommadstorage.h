#pragma once
#include "icommandstorage.h"

#include <vector>

namespace Bulknet {

/*!
 * \brief Класс ListCommadStorage реализует сохранение блока команд в вектор
 */
class ListCommadStorage : public ICommandStorage
{
public:
    /*!
     * \brief Конструктор ListCommadStorage
     * \param bulkSize размер блока команд
     */
    ListCommadStorage(const size_t bulkSize);
    //virtual ~ListCommadStorage();

    // override members of ICommandStorage
    virtual bool appendCommand( const ICommand::Ptr &cmd ) override final;
    virtual std::size_t bulkSize() const noexcept override final { return m_bulkSize; }
    virtual std::size_t commandsCount() const noexcept override final;
    virtual ICommand::WPtr command(const size_t idx) noexcept override final;
    virtual bool isDynamic() const noexcept override final;
    virtual void clear() override final { m_storage.clear(); }
    virtual Ptr clone() override final;

private:
    std::vector<ICommand::Ptr> m_storage;
    std::size_t m_bulkSize;
};

};
