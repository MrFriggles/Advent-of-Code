#include <iostream>
#include <string>

#include "AoC.h"

const std::string USAGE = "AoC [-d/--day=<day> | -a/--all]";

/*
 * What should main do?
 * - Probably should set up an array of all the days List<Day> for example.
 * - For each day in the list, run its own overide functions RunSilver() and RunGold()
 * - Perhaps a delimiter between days with obvious outputs.
 */

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
