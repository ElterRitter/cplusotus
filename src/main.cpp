#include "versionInfo.h"
#include "ipfilter.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    uint32_t lessionNumber = -1;
    po::options_description descr("Avaliable options");
    descr.add_options()
        ("help", "Usage: -l<number> lession number")
        ("lession,l", po::value<uint32_t>(&lessionNumber)->default_value(1), "lession number");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        cout << "Hello world!" << endl;
        cout << "Current build is " << versionInfo() << endl;
        cout << descr << endl;
        return 0;
    }

    switch(lessionNumber)
    {
    case 1: {
        auto pFilter = std::make_unique<IpFilter>();
        auto ret = pFilter->filter();
        pFilter->print(std::move(ret));
    }
    break;
    default:
        cout << "invalid options. Usage " << descr << endl;
        return 0;
    }

    return 0;
}
