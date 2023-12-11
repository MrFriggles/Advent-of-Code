#include "AoC.h"

Day::Day(uint8_t day) : m_day(d)ay
{ 
    std::cout << "Day " << m_day << ".\n\n";
    std::cout << "Running first task...\n";

    RunSilver();

    std::cout << "First done.\n";
    std::cout << "Running second task...\n";

    RunGold();

    std::cout << "Second done.\n";
    std::cout << "Day complete.\n";
}

Day::~Day() {}
