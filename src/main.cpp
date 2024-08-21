#include "versionInfo.h"
#include "ipfilter.h"
#include "sfinaelesson.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <memory>

using std::cout;
using std::endl;

namespace po = boost::program_options;

int main(int argc, char **argv)
{
    uint32_t lessonNumber = -1;
    po::options_description descr("Avaliable options");
    descr.add_options()
        ("help", "Usage: -l<number> lession number")
        ("lession,l", po::value<uint32_t>(&lessonNumber)->default_value(0), "lession number");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, descr), vm);
    po::notify(vm);

    if(vm.count("help") || (lessonNumber == 0))
    {
        cout << "Hello world!" << endl;
        cout << "Current build is " << versionInfo() << endl;
        cout << descr << endl;
        return 0;
    }

    switch(lessonNumber)
    {
    case 1: {
        auto pFilter = std::make_unique<IpFilter>(std::cin);
        auto ret = pFilter->filter();
        pFilter->print(std::move(ret));
        ret = pFilter->filterBySingleValue(0x01);
        pFilter->print(std::move(ret));
        ret = pFilter->filterByBytes(0x2e46);
        pFilter->print(std::move(ret));
        ret = pFilter->filterByAnyByte(0x2e);
        pFilter->print(std::move(ret));
    }
    break;
    case 2: {
    }
    break;
    case 3:
        sfinae::print_ip(uint8_t(-1));
        sfinae::print_ip(uint16_t{0});
        sfinae::print_ip(int32_t{2130706433});
        sfinae::print_ip(int64_t{8875824491850138409});
        sfinae::print_ip( std::string{"Hello, World!"} );         // Hello, World!
        sfinae::print_ip( std::vector<int>{100, 200, 300, 400} ); // 100.200.300.400
        sfinae::print_ip( std::list<short>{400, 300, 200, 100} ); // 400.300.200.100
        sfinae::print_ip( std::make_tuple(123, 456, 789, 0) );    // 123.456.789.0
    break;
    default:
        cout << "invalid options. Usage " << descr << endl;
        return 0;
    }

    return 0;
}
