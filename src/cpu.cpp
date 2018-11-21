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
        insertOpcode(makeOpCode(0b000, 0b000, 0b01), &CPU::ora_indirect_x);
        insertOpcode(makeOpCode(0b000, 0b001, 0b01), &CPU::ora_zeropg);
        insertOpcode(makeOpCode(0b000, 0b010, 0b01), &CPU::ora_immediate);
        insertOpcode(makeOpCode(0b000, 0b011, 0b01), &CPU::ora_absolute);
        insertOpcode(makeOpCode(0b000, 0b100, 0b01), &CPU::ora_indirect_y);
        insertOpcode(makeOpCode(0b000, 0b101, 0b01), &CPU::ora_zeropg_x);
        insertOpcode(makeOpCode(0b000, 0b110, 0b01), &CPU::ora_absolute_y);
        insertOpcode(makeOpCode(0b000, 0b111, 0b01), &CPU::ora_absolute_x);
                          

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

    void CPU::insertOpcode(uint8_t opcode, opcodeFun fun) {
        opCodes.insert(make_pair(opcode, fun));
        opcodeBag.insert(opcode);
    }


    bool CPU::opcodeNotAvailable(uint8_t opcode) {
        if (opcodeBag.find(opcode) == opcodeBag.end()) {
            return true;
        } else {
            return false;
        }
    }

    void CPU::changeFlags() {

    }

    // OPCodes Starts here, the definitions of all the opcodes

    //ORA
    void CPU::ora_indirect_x(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Indirect Reg-X addressing
        // PC += 2

        instPtr++;
        uint16_t alpha = regX, beta = r.getByteAt(instPtr);
        instPtr++;
        uint8_t addr = ((alpha+beta)&0xFF);
        uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
        uint16_t finalAddr = (kapa | (napa << 8));
        regAcc = regAcc|r.getByteAt(finalAddr);
        changeFlags();
    }
    
    void CPU::ora_zeropg(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Zero Page Addressing
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc|r.getByteAt(alpha);
        changeFlags();
    }
    
    void CPU::ora_immediate(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Immediate addressing
        // PC += 2
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc|alpha;
        changeFlags();
    }

    void CPU::ora_absolute(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Absolute addressing
        // PC += 3

        instPtr++;
        uint16_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint16_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        regAcc = regAcc|r.getByteAt(addr);
        changeFlags();
    }

    void CPU::ora_indirect_y(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Zero Page Y indexed
        // PC += 2

        instPtr++;
        uint16_t alpha = regY, beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
        uint16_t addr = kapa|(napa<<8);
        regAcc = regAcc|r.getByteAt(addr+alpha);
        changeFlags();
    }

    void CPU::ora_zeropg_x(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Zero Page X Indexed
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr), beta = regX;
        instPtr++;
        uint16_t addr = (alpha + regX)%256;
        regAcc = regAcc|r.getByteAt(addr);
        changeFlags();
    }

    void CPU::ora_absolute_y(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Absolute addressing indexed Y
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regY;
        regAcc = regAcc|r.getByteAt(addr);
        changeFlags();
    }

    void CPU::ora_absolute_x(const MemoryUnit &r) {
        // Bitwise OR with Accumulator: Absolute addressing indexed X
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regX;
        regAcc = regAcc|r.getByteAt(addr);
        changeFlags();
    }

    // publics
    bool CPU::executeInstruction(const MemoryUnit &r) {
        // Runs the opcode after fetching from RAM
        uint8_t opcode = r.getByteAt(instPtr);
        try {
            if (opcodeNotAvailable(opcode)) throw InvalidOpcodeException(opcode);
            opcodeFun fun = opCodes.find(opcode)->second;
            (this->*fun)(r);
            return true;
        } catch (InvalidOpcodeException &e) {
            printf("Warning: %s\n", e.what());
            return false;
        }
    }
    

} // NES
