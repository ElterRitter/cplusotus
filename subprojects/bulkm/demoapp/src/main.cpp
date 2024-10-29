#include <libasync.h>

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
        ("bulknumber,n", po::value<uint32_t>(&blockSize)->default_value(1), "size of commands bulk block ( default 1 )")
        ("log-dir,d", po::value<string>(&rootLogDirectory)->default_value(""), "Logs root directory ( default UserHome/log");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    cout << "Using command processor with block size " << blockSize << endl;
    auto processorItem = connect(blockSize);

    for(std::string str; std::getline(std::cin, str);)
    {
        recieve(processorItem, str.c_str(), str.size());
    }

    disconnect(processorItem);

    return 0;
}
