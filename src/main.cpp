#include "versionInfo.h"

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char **argv)
{
    cout << "Hello world!" << endl;
    cout << "Current build is " << versionInfo() << endl;

    return 0;
}
