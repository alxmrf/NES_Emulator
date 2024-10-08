#pragma once 
#include <vector>
#include<string>
#include<map>
#include <stdio.h>



class olc6502
{

//essentials to the making of the CPU class
public:

    //declaring the constructor
    olc6502();
    //declaring the deconstructor
    ~olc6502();
    //makes the connection to the bus
    void ConnectBus(Bus *n){ bus = n;}

//Declaring the CPU registers and flags, used in the internal functioning of the CPU 
public:

    //Declaration of the CPU flags
    enum FLAGS6502
    {
        C = (1<<0), //Bit that represents carrying in a rithmetic operation
        Z = (1<<1), //bit that represents if the last operation was a zero
        I = (1<<2), //bit that disables interrupts
        D = (1<<3), //decimal mode (unused in this implementation)
        B = (1<<4), //Bit that represents a Break
        U = (1<<5), //Unused
        V = (1<<6), //Bit that represents if an operation overflows
        N = (1<<7), //Bit that represents oiif the result of an operation is negative
    }

    //registers
    uint8_t a = 0x00 // accumulator register
    uint8_t x = 0x00 // X register
    uint8_t y = 0x00// Y register
    uint8_t stkp = 0x00 //Stack pointer (Points to a location in the stack)
    uint16_t pc = 0x0000 //Program counter
    uint8_t status = 0x00 // Status Register

//declaring fuctions and connections that are related to the Bus 
private:

    BUS *buspnt = nullptr; //Pointer to the BUS


    //functions that read and write data from/to the bus 
    uint8_t read(uint16_t addr);
    void write(uint_16 addr, uint8_t data);

//Declares the Struct that instructions to the CPU must follow 
private:
    struct INSTRUCTION
    {
        std::string name; //name of the instruction
        uint8_t(olc6502::*operate)(void) = nullptr; //pointer to which operator the instruction will call
        uint8_t(olc6502::*addrmode)(void) = nullptr; //pointe to which addressing mode the CPU will use 
        uint8_t cycles= 0;//indicator of how many Cycles the CPU will take to realize the instruction   
    };
    

private:
    //CPU addressing modes 

    uint8_t IMP();	uint8_t IMM();	
	uint8_t ZP0();	uint8_t ZPX();	
	uint8_t ZPY();	uint8_t REL();
	uint8_t ABS();	uint8_t ABX();	
	uint8_t ABY();	uint8_t IND();	
	uint8_t IZX();	uint8_t IZY();

private:
    //ALL OPCODES availiable in the cpu
    uint8_t ADC();	uint8_t AND();	uint8_t ASL();	uint8_t BCC();
	uint8_t BCS();	uint8_t BEQ();	uint8_t BIT();	uint8_t BMI();
	uint8_t BNE();	uint8_t BPL();	uint8_t BRK();	uint8_t BVC();
	uint8_t BVS();	uint8_t CLC();	uint8_t CLD();	uint8_t CLI();
	uint8_t CLV();	uint8_t CMP();	uint8_t CPX();	uint8_t CPY();
	uint8_t DEC();	uint8_t DEX();	uint8_t DEY();	uint8_t EOR();
	uint8_t INC();	uint8_t INX();	uint8_t INY();	uint8_t JMP();
	uint8_t JSR();	uint8_t LDA();	uint8_t LDX();	uint8_t LDY();
	uint8_t LSR();	uint8_t NOP();	uint8_t ORA();	uint8_t PHA();
	uint8_t PHP();	uint8_t PLA();	uint8_t PLP();	uint8_t ROL();
	uint8_t ROR();	uint8_t RTI();	uint8_t RTS();	uint8_t SBC();
	uint8_t SEC();	uint8_t SED();	uint8_t SEI();	uint8_t STA();
	uint8_t STX();	uint8_t STY();	uint8_t TAX();	uint8_t TAY();
	uint8_t TSX();	uint8_t TXA();	uint8_t TXS();	uint8_t TYA();


    //Catches all the illegal opcodes that may be accessed
    uint8_t XXX();


    void clock(); // performs one cycle`s worth of updates (Works like the clock of the CPU)
    void reset(); // fuction that forces the CPU into a known state
    void irq();// interrupt request: Executes an unterrupt ant a specific location(can be ignored depending wether the interrupt enabled flag is on or off)
    void nmi();// Non mascable interrupts: function like the standard interrupt request except these can never be ignored no mather if the interrupt flag is not enabled


    //assistive variables to facilitate emulation
    uint8_t fetched = 0x00;
    uint16_t temp = 0x0000;
    uint16_t addr_abs = 0x0000;
    uint16_t addr_rel = 0x0000;
    uint8_t OPCODE = 0x00;
    uint8_t cycles = 0; // cycles of the clock function
    uint32_t clock_count = 0;

//MISC functions
private:
    //Convenience function to access status registers
    uint8_t GetFlag(FLAGS6502 f);
    void SetFlag(FLAGS6502 f, bool v);

    //function to facilitate emulation 
    uint8_t fetch();



}