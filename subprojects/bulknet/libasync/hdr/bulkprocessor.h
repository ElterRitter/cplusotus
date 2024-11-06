#pragma once
#include "icommandstorage.h"

#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <string>

namespace Bulknet {

/*!
 * \brief Класс BulkProcessor является обработчиков блоков команд
 * Будет выводить команды из поступившего блока в консоль ( поток cout )
 * и в файлы. Имя файла формируется автоматически
 */

class BulkProcessor
{
public:
    using Ptr = std::shared_ptr<BulkProcessor>;

    /*!
     * \brief Конструктор BulkProcessor
     * \param rootLogDirectory путь к директории, где хранить логи
     */
    BulkProcessor(const std::string &rootLogDirectory);
    ~BulkProcessor();

    /*!
     * \brief onPublishBulk основная функция-обработчик блока команд
     * \param bulkData блок команд для обработки
     */
    void onPublishBulk(ICommandStorage::Ptr bulkData);

private:
    using threadptr = std::unique_ptr<std::thread>;
    std::vector<threadptr> m_threads;

    std::queue<ICommandStorage::Ptr> m_bulks;
    std::mutex m_mutex;
    std::condition_variable m_cv;

    std::queue<ICommandStorage::Ptr> m_consoleBulks;
    std::mutex m_consoleMutex;
    std::condition_variable m_cvConsole;

    bool m_needExit;

    void printerFileThreadFunc(const std::string &rootLogDirectory);
    void printerConsoleThreadFunc();
};

};
