#include <iostream>
#include <string>

#include "AoC.h"

const std::string USAGE = "AoC [-d/--day=<day> | -a/--all]";

int main(int argc, char *argv[])
{
    if (argc < 1)
    {
        std::cerr << USAGE << '\n';
        return -1;
    }

    if (argc == 2)
    {
        
    }

    return 0;
}
