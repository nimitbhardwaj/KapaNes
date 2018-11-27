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
        insertOpcode(0b00000001, &CPU::ora_indirect_x, "ORA_IND_X");
        insertOpcode(0b00000101, &CPU::ora_zeropg, "ORA_ZEROPG");
        insertOpcode(0b00001001, &CPU::ora_immediate, "ORA_IMM");
        insertOpcode(0b00001101, &CPU::ora_absolute, "ORA_ABS");
        insertOpcode(0b00010001, &CPU::ora_indirect_y, "ORA_IND_Y");
        insertOpcode(0b00010101, &CPU::ora_zeropg_x, "ORA_ZEROPG_X");
        insertOpcode(0b00011001, &CPU::ora_absolute_y, "ORA_ABS_Y");
        insertOpcode(0b00011101, &CPU::ora_absolute_x, "ORA_ABS_X");

        // AND
        insertOpcode(0b00100001, &CPU::and_indirect_x, "AND_IND_X");
        insertOpcode(0b00100101, &CPU::and_zeropg, "AND_ZEROPG");
        insertOpcode(0b00101001, &CPU::and_immediate, "AND_IMM");
        insertOpcode(0b00101101, &CPU::and_absolute, "AND_ABS");
        insertOpcode(0b00110001, &CPU::and_indirect_y, "AND_IND_Y");
        insertOpcode(0b00110101, &CPU::and_zeropg_x, "AND_ZEROPG_X");
        insertOpcode(0b00111001, &CPU::and_absolute_y, "AND_ABS_Y");
        insertOpcode(0b00111101, &CPU::and_absolute_x, "AND_ABS_X");

        // EOR
        insertOpcode(0b01000001, &CPU::eor_indirect_x, "EOR_IND_X");
        insertOpcode(0b01000101, &CPU::eor_zeropg, "EOR_ZEROPG");
        insertOpcode(0b01001001, &CPU::eor_immediate, "EOR_IMM");
        insertOpcode(0b01001101, &CPU::eor_absolute, "EOR_ABS");
        insertOpcode(0b01010001, &CPU::eor_indirect_y, "EOR_IND_Y");
        insertOpcode(0b01010101, &CPU::eor_zeropg_x, "EOR_ZEROPG_X");
        insertOpcode(0b01011001, &CPU::eor_absolute_y, "EOR_ABS_Y");
        insertOpcode(0b01011101, &CPU::eor_absolute_x, "EOR_ABS_X");

           

    }

    // Destructor
    CPU::~CPU() {

    }

    // privates
    
    void CPU::insertOpcode(uint8_t opcode, opcodeFun fun, const string &S) {
        opCodes.insert(make_pair(opcode, fun));
        opcodeBag.insert(opcode);
        opcodeNameLookup.insert(make_pair(S, opcode));
    }


    bool CPU::opcodeNotAvailable(uint8_t opcode) {
        if (opcodeBag.find(opcode) == opcodeBag.end()) {
            return true;
        } else {
            return false;
        }
    }

    void CPU::changeFlags() {
        const uint8_t x = regAcc;
        // ZeroFlag
        if (x == 0) {
            flags = flags | (1<<0);
        } else {
            flags = flags & (~(1<<0));
        }
        
        // Negetive flag
        if (x & (1<<7) != 0) {
            flags = flags | (1<<1);
        } else {
            flags = flags & (~(1<<1));
        }
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

    // AND
    void CPU::and_indirect_x(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Indirect Reg-X addressing
        // PC += 2

        instPtr++;
        uint16_t alpha = regX, beta = r.getByteAt(instPtr);
        instPtr++;
        uint8_t addr = ((alpha+beta)&0xFF);
        uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
        uint16_t finalAddr = (kapa | (napa << 8));
        regAcc = regAcc&r.getByteAt(finalAddr);
        changeFlags();
    }
    
    void CPU::and_zeropg(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Zero Page Addressing
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc&r.getByteAt(alpha);
        changeFlags();
    }
    
    void CPU::and_immediate(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Immediate addressing
        // PC += 2
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc&alpha;
        changeFlags();
    }

    void CPU::and_absolute(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Absolute addressing
        // PC += 3

        instPtr++;
        uint16_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint16_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        regAcc = regAcc&r.getByteAt(addr);
        changeFlags();
    }

    void CPU::and_indirect_y(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Zero Page Y indexed
        // PC += 2

        instPtr++;
        uint16_t alpha = regY, beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
        uint16_t addr = kapa|(napa<<8);
        regAcc = regAcc&r.getByteAt(addr+alpha);
        changeFlags();
    }

    void CPU::and_zeropg_x(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Zero Page X Indexed
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr), beta = regX;
        instPtr++;
        uint16_t addr = (alpha + regX)%256;
        regAcc = regAcc&r.getByteAt(addr);
        changeFlags();
    }

    void CPU::and_absolute_y(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Absolute addressing indexed Y
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regY;
        regAcc = regAcc&r.getByteAt(addr);
        changeFlags();
    }

    void CPU::and_absolute_x(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Absolute addressing indexed X
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regX;
        regAcc = regAcc&r.getByteAt(addr);
        changeFlags();
    }


    // EOR
    void CPU::eor_indirect_x(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Indirect Reg-X addressing
        // PC += 2

        instPtr++;
        uint16_t alpha = regX, beta = r.getByteAt(instPtr);
        instPtr++;
        uint8_t addr = ((alpha+beta)&0xFF);
        uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
        uint16_t finalAddr = (kapa | (napa << 8));
        regAcc = regAcc^r.getByteAt(finalAddr);
        changeFlags();
    }
    
    void CPU::eor_zeropg(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Zero Page Addressing
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc^r.getByteAt(alpha);
        changeFlags();
    }
    
    void CPU::eor_immediate(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Immediate addressing
        // PC += 2
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        regAcc = regAcc^alpha;
        changeFlags();
    }

    void CPU::eor_absolute(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Absolute addressing
        // PC += 3

        instPtr++;
        uint16_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint16_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        regAcc = regAcc^r.getByteAt(addr);
        changeFlags();
    }

    void CPU::eor_indirect_y(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Zero Page Y indexed
        // PC += 2

        instPtr++;
        uint16_t alpha = regY, beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
        uint16_t addr = kapa|(napa<<8);
        regAcc = regAcc^r.getByteAt(addr+alpha);
        changeFlags();
    }

    void CPU::eor_zeropg_x(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Zero Page X Indexed
        // PC += 2

        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr), beta = regX;
        instPtr++;
        uint16_t addr = (alpha + regX)%256;
        regAcc = regAcc^r.getByteAt(addr);
        changeFlags();
    }

    void CPU::eor_absolute_y(const MemoryUnit &r) {
        // Bitwise AND with Accumulator: Absolute addressing indexed Y
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regY;
        regAcc = regAcc^r.getByteAt(addr);
        changeFlags();
    }

    void CPU::eor_absolute_x(const MemoryUnit &r) {
        // Bitwise Exclusive-OR with Accumulator: Absolute addressing indexed X
        // PC += 3
        instPtr++;
        uint8_t alpha = r.getByteAt(instPtr);
        instPtr++;
        uint8_t beta = r.getByteAt(instPtr);
        instPtr++;
        uint16_t addr = (alpha|(beta<<8));
        addr += regX;
        regAcc = regAcc^r.getByteAt(addr);
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

    uint8_t CPU::getOpcode(const string &S) const {
        return opcodeNameLookup.find(S)->second;
    }
    

} // NES
