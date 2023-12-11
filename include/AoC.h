#ifndef _AOC_H
#define _AOC_H

#include <iostream>

// Day base class
class Day
{
public:
    Day(uint8_t day);
    Day(uint8_t day, char * inputPath);
    ~Day();

    virtual void RunSilver() { return; }
    virtual void RunGold() { return; }
    
    inline uint8_t GetDay(){ return m_day; }
    void InitializeInput(char * inputPath);

private:
    uint8_t m_day = 0;

};

#endif //_AOC_H
