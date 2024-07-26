#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>


class Bus
{
    public:
    Bus();
    ~Bus();

    public:
    //Devices that are on the motherboard bus
    
    //CPU 
    olc6592 cpu;
    //RAM
    std::array<uint8_t, 64 * 1024> ram;


    public:
    void write(uint16_t addr, uint8_t data);
    uint8_t read(uint16_t addr,bool bReadOnly = false);

};