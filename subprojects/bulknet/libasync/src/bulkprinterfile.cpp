#include "bulkprinterfile.h"
#include "command.h"

#include <fstream>
#include <iostream>

using std::string;
using std::ofstream;
using std::ios_base;
using std::endl;

using namespace Bulknet;

std::mutex BulkPrinterFile::fileDynamicMutex;

static uint32_t threadCounter = 1;

BulkPrinterFile::BulkPrinterFile(const std::string &rootFolder) :
    m_rootFolder{rootFolder}
    , m_threadId(threadCounter++)
{

}

void BulkPrinterFile::processBulk(ICommandStorage::Ptr ptrBulk)
{
    if(!ptrBulk)
        return;

    if(ptrBulk->commandsCount() == 0)
        return;

    ofstream file;
    size_t cmdCount = ptrBulk->commandsCount();
    if(ptrBulk->isDynamic())
        fileDynamicMutex.lock();

    for(size_t i = 0; i < cmdCount; i++)
    {
        auto cmd = ptrBulk->command(i);
        if(!file.is_open())
        {
            string fileNamePath = m_rootFolder + makeFileName(cmd);
            file.open(fileNamePath, ios_base::out);
            if(!file.is_open())
            {
                std::cerr << "Can't open file " << fileNamePath << ". Output in file for this bulk not avaliable" << endl;
                return;
            }
            file << "bulk: ";
        }

        file << cmd << " ";
    }

    file << endl;

    if(ptrBulk->isDynamic())
        fileDynamicMutex.unlock();
}

string BulkPrinterFile::makeFileName(const ICommand::WPtr &cmd) const
{
    auto ptr = cmd.lock();
    if(!ptr)
        return "";

    auto commonCmd = std::static_pointer_cast<CommonCommand>(ptr);
    if(!commonCmd)
        return string();

    string fname("/log");
    string timeStamp = std::to_string(commonCmd->timestamp());
    string threadId = "_thread" + std::to_string(m_threadId);
    return fname.append(timeStamp).append(threadId).append(".log");
}
