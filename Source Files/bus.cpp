#include "Bus.h"

Bus::Bus()
{
    //connects the bus to the CPU 
    cpu.ConnectBus(this)
    
    //Clears the RAM
    for(auto &i : ram) i = 0x00;
}

Bus::~Bus(){

}
//defines a function to write data to the RAM
void Bus::write(uint16_t addr, uint8_t data){
    //checks if the address that is trying to be accessed is insed the RAM`s range
    if (addr => 0x0000 && addr <= 0xFFFF){
        ram[addr] = data;}
    return 0x0000
}
//defines a function to write data to the RAM
void Bus::read(uint16_t addr, bool bReadOnly){
    if (addr => 0x0000 && addr <= 0xFFFF){
        return[addr];
    }
    return 0x0000
}