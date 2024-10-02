#include "bulkprinterfile.h"
#include "command.h"

#include <fstream>
#include <iostream>

using std::string;
using std::ofstream;
using std::ios_base;
using std::endl;

BulkPrinterFile::BulkPrinterFile(const std::string &rootFolder) :
    m_rootFilder{rootFolder}
{

}

void BulkPrinterFile::processBulk(ICommandStorage::Ptr ptrBulk)
{
    if(!ptrBulk)
        return;

    if(ptrBulk->commandsCount() == 0)
        return;

    ofstream file;
    uint32_t cmdCount = ptrBulk->commandsCount();
    for(uint32_t i = 0; i < cmdCount; i++)
    {
        auto cmd = ptrBulk->command(i);
        if(!file.is_open())
        {
            string fileNamePath = m_rootFilder + makeFileName(cmd);
            file.open(fileNamePath, ios_base::out);
            if(!file.is_open())
            {
                std::cerr << "Can't open file " << fileNamePath << ". Output in file for this bulk not avaliable" << endl;
                return;
            }
        }

        file << cmd << endl;
    }
}

string BulkPrinterFile::makeFileName(const ICommand::Ptr &cmd)
{
    auto commonCmd = std::static_pointer_cast<CommonCommand>(cmd);
    if(!commonCmd)
        return string();

    string fname("/log");
    return fname.append(std::to_string(commonCmd->timestamp())).append(".log");
}
