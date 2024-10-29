#include "libasync.h"

#include "commandprocessor.h"
#include "bulkprocessor.h"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>

using std::unordered_map;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using namespace Bulkm;

struct AssociatedProcessors
{
    using Ptr = std::unique_ptr<AssociatedProcessors>;
    CommandProcessor::Ptr commandHandler;
    BulkProcessor::Ptr bulkProcessor;
};

std::unordered_map<processorid, AssociatedProcessors::Ptr> processors;
processorid id;

string printerRootDirectory()
{
    string homePath;
#if defined(OS_WIN)
    const char *pHomeFolder = std::getenv("USERPROFILE");
    if(pHomeFolder != nullptr)
        homePath.assign(pHomeFolder);
#else
    homePath.append("~/");
#endif

    return homePath;
}

processorid connect(const unsigned int blockSize)
{
    AssociatedProcessors::Ptr pProcessor = std::make_unique<AssociatedProcessors>();
    pProcessor->commandHandler = std::make_unique<CommandProcessor>(blockSize);
    pProcessor->bulkProcessor = std::make_unique<BulkProcessor>(printerRootDirectory());

    auto slotPublishBulk = boost::bind(&BulkProcessor::onPublishBulk, pProcessor->bulkProcessor, boost::placeholders::_1);
    pProcessor->commandHandler->publishBulk.connect(slotPublishBulk);

    processors[id] = std::move(pProcessor);
    auto ret = id++;
    return ret;
}

void recieve(processorid processingId, const char *pCommandBuffer, unsigned int bufferSize)
{
    auto it = processors.find(processingId);
    if(it == processors.end())
    {
        cerr << "Can't processing recieved data: invalid processing id";
        return;
    }

    string cmd(pCommandBuffer, bufferSize);
    (*it).second->commandHandler->processingCommand(cmd);
}

void disconnect(const int processingId)
{
    auto it = processors.find(processingId);
    if(it == processors.end())
        return;

    (*it).second->commandHandler->finalize();
    processors.erase(it);
}
