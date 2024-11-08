#include "libasync.h"

#include "commandprocessor.h"
#include "bulkprocessor.h"

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::unordered_map;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using namespace Bulknet;

struct AssociatedProcessors
{
    using Ptr = std::unique_ptr<AssociatedProcessors>;
    CommandProcessor::Ptr commandHandler;
    BulkProcessor::Ptr bulkProcessor;
};

std::unordered_map<processorid, AssociatedProcessors::Ptr> processors;
processorid id;

// string printerRootDirectory()
// {
//     string homePath;
// #if defined(OS_WIN)
//     const char *pHomeFolder = std::getenv("USERPROFILE");
//     if(pHomeFolder != nullptr)
//         homePath.assign(pHomeFolder);
// #else
//     homePath.append("~/");
// #endif

//     return homePath;
// }

processorid bulk_connect(const unsigned int blockSize, const char *pRootDirectory, unsigned int rootDirectoryLen)
{
    std::string rootLogdir(pRootDirectory, rootDirectoryLen);
    AssociatedProcessors::Ptr pProcessor = std::make_unique<AssociatedProcessors>();
    pProcessor->commandHandler = std::make_unique<CommandProcessor>(blockSize);
    pProcessor->bulkProcessor = std::make_unique<BulkProcessor>(rootLogdir);

    auto slotPublishBulk = boost::bind(&BulkProcessor::onPublishBulk, pProcessor->bulkProcessor, boost::placeholders::_1);
    pProcessor->commandHandler->publishBulk.connect(slotPublishBulk);

    processors[id] = std::move(pProcessor);
    auto ret = id++;
    return ret;
}

void bulk_recieve(processorid processingId, const char *pCommandBuffer, unsigned int bufferSize)
{
    auto it = processors.find(processingId);
    if(it == processors.end())
    {
        cerr << "Can't processing recieved data: invalid processing id";
        return;
    }

    string dataString(pCommandBuffer, bufferSize);
    std::stringstream ss(dataString);
    std::string cmd;
    while(std::getline(ss, cmd, '\n'))
        (*it).second->commandHandler->processingCommand(cmd);
}

void bulk_disconnect(const int processingId)
{
    auto it = processors.find(processingId);
    if(it == processors.end())
        return;

    (*it).second->commandHandler->finalize();
    processors.erase(it);
}
