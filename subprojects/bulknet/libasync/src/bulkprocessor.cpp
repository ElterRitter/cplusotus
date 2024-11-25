#include "bulkprocessor.h"
#include "bulkprinterconsole.h"
#include "bulkprinterfile.h"

#include <chrono>

using namespace std::chrono_literals;
using std::unique_lock;
using std::mutex;

using namespace Bulknet;

BulkProcessor::BulkProcessor(const std::string& rootLogDirectory) :
    m_needExit{false}
{
    auto pThread = std::make_unique<std::thread>(&BulkProcessor::printerFileThreadFunc, this, std::ref(rootLogDirectory));
    m_threads.push_back(std::move(pThread));

    pThread = std::make_unique<std::thread>(&BulkProcessor::printerFileThreadFunc, this, std::ref(rootLogDirectory));
    m_threads.push_back(std::move(pThread));

    pThread = std::make_unique<std::thread>(&BulkProcessor::printerConsoleThreadFunc, this);
    m_threads.push_back(std::move(pThread));
}

BulkProcessor::~BulkProcessor()
{
    m_needExit = true;
    m_cv.notify_all();
    m_cvConsole.notify_all();

    for(const auto &thrd : m_threads)
        thrd->join();
}

void BulkProcessor::onPublishBulk(const ICommandStorage::Ptr bulkData)
{
    std::unique_lock<std::mutex> lg(m_mutex);
    m_bulks.push(bulkData);
    m_cv.notify_one();
    lg.unlock();

    // std::async(std::launch::async, [&bulkData]() {
    //     auto printerConsole = std::make_unique<BulkPrinterConsole>();
    //     printerConsole->processBulk(bulkData);
    // });

   std::unique_lock<std::mutex> lc(m_consoleMutex);
   m_consoleBulks.push(bulkData);
   m_cvConsole.notify_one();
   lc.unlock();

}

void BulkProcessor::printerFileThreadFunc(const std::string &rootLogDirectory)
{
    auto printerFile = std::make_unique<Bulknet::BulkPrinterFile>(rootLogDirectory);
    std::queue<Bulknet::ICommandStorage::Ptr> que;

    while(!m_needExit)
    {
        unique_lock<mutex> lg(m_mutex);
        if(m_bulks.empty() && m_cv.wait_for(lg, 500ms) == std::cv_status::timeout)
            continue;

        que.swap(m_bulks);
        lg.unlock();

        while(!que.empty())
        {
            printerFile->processBulk(que.front());
            que.pop();

            if(m_needExit)
                break;
        }
    }
}

void BulkProcessor::printerConsoleThreadFunc()
{
    auto printerConsole = std::make_unique<BulkPrinterConsole>();
    std::queue<ICommandStorage::Ptr> que;

    while(!m_needExit)
    {
        unique_lock<mutex> lg(m_consoleMutex);
        if(m_consoleBulks.empty() && m_cvConsole.wait_for(lg, 500ms) == std::cv_status::timeout)
            continue;

        que.swap(m_consoleBulks);
        lg.unlock();

        while(!que.empty())
        {
            printerConsole->processBulk(que.front());
            que.pop();

            if(m_needExit)
                break;
        }
    }
}

