#pragma once
#include "icommandstorage.h"
#include <boost/signals2.hpp>
namespace Bulkm {

/*!
 * \brief Интерфейс IBulkPublisher реализует методы
 */
class IBulkPublisher
{
public:
    IBulkPublisher() = default;
    virtual ~IBulkPublisher() = default;

    using sigBulk = boost::signals2::signal<void(ICommandStorage::Ptr)>;
    sigBulk publishBulk;

};

};  // namespace Bulk
