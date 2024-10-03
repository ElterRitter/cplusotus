#include "bulkprinterconsole.h"
#include "command.h"

#include <iostream>

using std::cout;
using std::endl;

using namespace Bulk;

void BulkPrinterConsole::processBulk(const ICommandStorage::Ptr ptrBulk)
{
    if(!ptrBulk)
        return;

    auto cmdCount = ptrBulk->commandsCount();
    for(uint32_t i = 0; i < cmdCount; i++)
    {
        cout << ptrBulk->command(i) << endl;
    }
}
