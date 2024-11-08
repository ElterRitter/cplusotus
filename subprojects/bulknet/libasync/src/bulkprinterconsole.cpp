#include "bulkprinterconsole.h"
#include "command.h"

#include <iostream>

using std::cout;
using std::endl;

using namespace Bulknet;

std::mutex BulkPrinterConsole::dynBlockMutex;

void BulkPrinterConsole::processBulk(const ICommandStorage::Ptr ptrBulk)
{
    if(!ptrBulk)
        return;

    auto cmdCount = ptrBulk->commandsCount();
    if(ptrBulk->isDynamic())
        dynBlockMutex.lock();

    cout << "bulk: ";
    for(uint32_t i = 0; i < cmdCount; i++)
    {
        cout << ptrBulk->command(i);
        if(i < cmdCount - 1)
            cout << ", ";
    }
    cout << endl;

    if(ptrBulk->isDynamic())
        dynBlockMutex.unlock();
}
