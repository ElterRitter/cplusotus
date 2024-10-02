#include "commandprocessor.h"
#include "bulkprinterconsole.h"
#include "bulkprinterfile.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    cout << "Hello world from bulk command processor" << endl;
    uint32_t blockSize = 0;
    string rootLogDirectory;
    po::options_description descr("Avaliable options");
    descr.add_options()
        ("help", "Usage: -n <block_size> --log-dir <root_log_directory>")
        ("bulknumber,n", po::value<uint32_t>(&blockSize)->default_value(1), "size of commands bulk block")
        ("log-dir,d", po::value<string>(&rootLogDirectory)->default_value(""), "Logs root directory");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    std::string homePath;

#if defined(OS_WIN)
    char *pHomeFolder = std::getenv("USERPROFILE");
    if(pHomeFolder != nullptr)
        homePath.assign(pHomeFolder);

#elif defined(OS_UNIX)
    homePath.append("~/");
#endif

    if(rootLogDirectory.empty())
        rootLogDirectory = homePath;

    cout << "Using command processor with block size " << blockSize << endl;
    CommandProcessor proc(blockSize);

    // creating printers
    auto consolePrinter = std::make_shared<BulkPrinterConsole>();
    auto filePrinter = std::make_shared<BulkPrinterFile>(rootLogDirectory);

    // subscribing
    proc.subscribePrinter(consolePrinter);
    proc.subscribePrinter(filePrinter);

    for(std::string str; std::getline(std::cin, str);)
    {
        proc.processingCommand(str);
    }

    proc.finalize();
    proc.unsubscribePrinter(consolePrinter);
    proc.unsubscribePrinter(filePrinter);
}
