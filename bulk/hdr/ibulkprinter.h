#pragma once
#include "icommandstorage.h"

#include <memory>

namespace Bulk {

/*!
 * \brief Класс IBulkPrinter определяет интерфейс для сериализации
 * накопленного блока команд
 */
class IBulkPrinter
{
public:
    using Ptr = std::shared_ptr<IBulkPrinter>;
    IBulkPrinter() = default;
    virtual ~IBulkPrinter() = default;

    /*!
     * \brief Метод processBulk должен сериализовать юлок команд
     * \param ptrBulk блок команд
     */
    virtual void processBulk(const ICommandStorage::Ptr ptrBulk) = 0;
};

}; // namespace Bulk
