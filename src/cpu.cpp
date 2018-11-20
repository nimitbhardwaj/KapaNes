#include <cpu.hpp>

using std::pair;
using std::make_pair;

namespace NES
{
    // Constructor
    CPU::CPU() {
        // Initials of registers
        regAcc = regX = regY = flags = 0;
        stackPtr = instPtr = 0;

        // ORA
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b000, 0b01), (opcodeFun)&
                            CPU::ora_indirect_x));
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b001, 0b01), (opcodeFun)&
                            CPU::ora_zeropg));                            
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b010, 0b01), (opcodeFun)&
                            CPU::ora_immediate));                            
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b011, 0b01), (opcodeFun)&
                            CPU::ora_absolute));                            
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b100, 0b01), (opcodeFun)&
                            CPU::ora_indirect_y));                            
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b101, 0b01), (opcodeFun)&
                            CPU::ora_zeropg_x));  
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b110, 0b01), (opcodeFun)&
                            CPU::ora_absolute_y));                            
        opCodes_01.insert(make_pair(makeOpCode(0b000, 0b111, 0b01), (opcodeFun)&
                            CPU::ora_absolute_x));                            
                          

    }

    // Destructor
    CPU::~CPU() {

    }

    // privates
    uint8_t CPU::makeOpCode(uint8_t a, uint8_t b, uint8_t c) const{
        uint8_t ret = 0;
        ret = ret | (a<<5);
        ret = ret | (b<<2);
        ret = ret | (c);
        return ret;
    }


    // OPCodes Starts here, the definitions of all the opcodes

    //ORA
    void CPU::ora_indirect_x(const Ram &r) {
        // Bitwise OR with Accumulator: Indirect Reg-X addressing
        // PC += 2

        instPtr++;
        uint16_t alpha = regX, beta = r.getByteAt(instPtr);
        instPtr++;
        uint8_t addr = ((alpha+beta)&0xFF);
        uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
        uint16_t finalAddr = (kapa | (napa << 8));
        regAcc = regAcc|r.getByteAt(finalAddr);
    }
    
    void CPU::ora_zeropg(const Ram &r) {
        // Bitwise OR with Accumulator: Zero Page Addressing
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc|r.getByteAt(alpha);
    }
    
    void CPU::ora_immediate(const Ram &r) {
        // Bitwise OR with Accumulator: Immediate addressing
        // PC += 2
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc|alpha;
    }

    void CPU::ora_absolute(const Ram &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 3

        instPtr++;
        uint16_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint16_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        regAcc = regAcc|r.getByteAt(addr);
    }

    void CPU::ora_indirect_y(const Ram &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 2

        instPtr++;
        uint16_t alpha = regY, beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
        uint16_t addr = kapa|(napa<<8);
        regAcc = regAcc|r.getByteAt(addr);
    }

    void CPU::ora_zeropg_x(const Ram &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr), beta = regX;
        instPtr++;
        uint16_t addr = (alpha + regX)%256;
        regAcc = regAcc|r.getByteAt(alpha);
    }

    void CPU::ora_absolute_y(const Ram &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regY;
        regAcc = regAcc|r.getByteAt(addr);
    }

    void CPU::ora_absolute_x(const Ram &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regX;
        regAcc = regAcc|r.getByteAt(addr);
    }

    // publics
    bool CPU::executeInstruction(const Ram &r) {
        // Runs the opcode after fetching from RAM
        try {
            // opcodeFun fun = opCodes_01.find(makeOpCode(000, 000, 1))->second;
            // (this->*fun)(r);
            return true;
        } catch (InvalidOpcodeException &e) {
            printf("Warning: %s\n", e.what());
            return false;
        }
    }
    

} // NES
