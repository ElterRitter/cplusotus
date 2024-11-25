#include "bulkserver.h"
#include "netcommandprocessor.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

namespace po = boost::program_options;

int main(int argc, char** argv)
{
    cout << "Hello world from bulk network command processor" << endl;

    uint16_t listenPort = 0;
    uint32_t blockSize = 0;
    string rootLogDirectory;
    po::options_description descr("Avaliable options");
    descr.add_options()
        ("help", "Usage: -n <block_size> --log-dir <root_log_directory> --port <server_listen_port>")
        ("bulknumber,n", po::value<uint32_t>(&blockSize)->default_value(1), "size of commands bulk block ( default 1 )")
        ("log-dir,d", po::value<string>(&rootLogDirectory)->default_value(""), "Logs root directory ( default UserHome/log")
        ("port,p", po::value<uint16_t>(&listenPort)->default_value(10000), "listen port");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    cout << "Using NetworkBulkProcessor with block size " << blockSize << " and log directory " << rootLogDirectory << endl;
    NetCommandProcessor bulkProcessor(blockSize, rootLogDirectory);
    auto onNewConnection = std::bind(&NetCommandProcessor::onAcceptedNewConnection, bulkProcessor, std::placeholders::_1);

    cout << "Starting server for 0.0.0.0:" << listenPort << endl;
    BulkServer srv(onNewConnection);
    bool ret = srv.listen("0.0.0.0", listenPort);
    cout << "Server listening ret " << ret << endl;
    cout << "To close server press any key and enter" << endl;

    auto ciget = std::cin.get();

    cout << "Server stopped" << endl;

    return 0;
}
