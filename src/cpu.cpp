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

    // ADC
    insertOpcode(0b01100001, &CPU::adc_indirect_x, "ADC_IND_X");
    insertOpcode(0b01100101, &CPU::adc_zeropg, "ADC_ZEROPG");
    insertOpcode(0b01101001, &CPU::adc_immediate, "ADC_IMM");
    insertOpcode(0b01101101, &CPU::adc_absolute, "ADC_ABS");
    insertOpcode(0b01110001, &CPU::adc_indirect_y, "ADC_IND_Y");
    insertOpcode(0b01110101, &CPU::adc_zeropg_x, "ADC_ZEROPG_X");
    insertOpcode(0b01111001, &CPU::adc_absolute_y, "ADC_ABS_Y");
    insertOpcode(0b01111101, &CPU::adc_absolute_x, "ADC_ABS_X");

    // STA
    insertOpcode(0b10000001, &CPU::sta_indirect_x, "STA_IND_X");
    insertOpcode(0b10000101, &CPU::sta_zeropg, "STA_ZEROPG");
    insertOpcode(0b10001001, &CPU::sta_immediate, "STA_IMM");
    insertOpcode(0b10001101, &CPU::sta_absolute, "STA_ABS");
    insertOpcode(0b10010001, &CPU::sta_indirect_y, "STA_IND_Y");
    insertOpcode(0b10010101, &CPU::sta_zeropg_x, "STA_ZEROPG_X");
    insertOpcode(0b10011001, &CPU::sta_absolute_y, "STA_ABS_Y");
    insertOpcode(0b10011101, &CPU::sta_absolute_x, "STA_ABS_X");
    
    // LDA
    insertOpcode(0b10100001, &CPU::lda_indirect_x, "LDA_IND_X");
    insertOpcode(0b10100101, &CPU::lda_zeropg, "LDA_ZEROPG");
    insertOpcode(0b10101001, &CPU::lda_immediate, "LDA_IMM");
    insertOpcode(0b10101101, &CPU::lda_absolute, "LDA_ABS");
    insertOpcode(0b10110001, &CPU::lda_indirect_y, "LDA_IND_Y");
    insertOpcode(0b10110101, &CPU::lda_zeropg_x, "LDA_ZEROPG_X");
    insertOpcode(0b10111001, &CPU::lda_absolute_y, "LDA_ABS_Y");
    insertOpcode(0b10111101, &CPU::lda_absolute_x, "LDA_ABS_X");
    
    // CMP
    insertOpcode(0b11000001, &CPU::cmp_indirect_x, "CMP_IND_X");
    insertOpcode(0b11000101, &CPU::cmp_zeropg, "CMP_ZEROPG");
    insertOpcode(0b11001001, &CPU::cmp_immediate, "CMP_IMM");
    insertOpcode(0b11001101, &CPU::cmp_absolute, "CMP_ABS");
    insertOpcode(0b11010001, &CPU::cmp_indirect_y, "CMP_IND_Y");
    insertOpcode(0b11010101, &CPU::cmp_zeropg_x, "CMP_ZEROPG_X");
    insertOpcode(0b11011001, &CPU::cmp_absolute_y, "CMP_ABS_Y");
    insertOpcode(0b11011101, &CPU::cmp_absolute_x, "CMP_ABS_X");


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

void CPU::changeFlags(uint8_t carry, uint8_t overflow) {
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

    // Carry Flag
    if (carry == 0) {
        flags = flags & (~(1<<2));
    } else if (carry == 1){
        flags = flags | (1<<2);
    }
    //
    if (overflow == 0) {
        flags = flags & (~(1<<3));
    } else if(overflow == 1) {
        flags = flags | (1<<3);
    }
}

// OPCodes Starts here, the definitions of all the opcodes


//ORA
void CPU::ora_indirect_x(MemoryUnit &r) {
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

void CPU::ora_zeropg(MemoryUnit &r) {
    // Bitwise OR with Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc|r.getByteAt(alpha);
    changeFlags();
}

void CPU::ora_immediate(MemoryUnit &r) {
    // Bitwise OR with Accumulator: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc|alpha;
    changeFlags();
}

void CPU::ora_absolute(MemoryUnit &r) {
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

void CPU::ora_indirect_y(MemoryUnit &r) {
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

void CPU::ora_zeropg_x(MemoryUnit &r) {
    // Bitwise OR with Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    regAcc = regAcc|r.getByteAt(addr);
    changeFlags();
}

void CPU::ora_absolute_y(MemoryUnit &r) {
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

void CPU::ora_absolute_x(MemoryUnit &r) {
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
void CPU::and_indirect_x(MemoryUnit &r) {
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

void CPU::and_zeropg(MemoryUnit &r) {
    // Bitwise AND with Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc&r.getByteAt(alpha);
    changeFlags();
}

void CPU::and_immediate(MemoryUnit &r) {
    // Bitwise AND with Accumulator: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc&alpha;
    changeFlags();
}

void CPU::and_absolute(MemoryUnit &r) {
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

void CPU::and_indirect_y(MemoryUnit &r) {
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

void CPU::and_zeropg_x(MemoryUnit &r) {
    // Bitwise AND with Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    regAcc = regAcc&r.getByteAt(addr);
    changeFlags();
}

void CPU::and_absolute_y(MemoryUnit &r) {
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

void CPU::and_absolute_x(MemoryUnit &r) {
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
void CPU::eor_indirect_x(MemoryUnit &r) {
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

void CPU::eor_zeropg(MemoryUnit &r) {
    // Bitwise Exclusive-OR with Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc^r.getByteAt(alpha);
    changeFlags();
}

void CPU::eor_immediate(MemoryUnit &r) {
    // Bitwise Exclusive-OR with Accumulator: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = regAcc^alpha;
    changeFlags();
}

void CPU::eor_absolute(MemoryUnit &r) {
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

void CPU::eor_indirect_y(MemoryUnit &r) {
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

void CPU::eor_zeropg_x(MemoryUnit &r) {
    // Bitwise Exclusive-OR with Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    regAcc = regAcc^r.getByteAt(addr);
    changeFlags();
}

void CPU::eor_absolute_y(MemoryUnit &r) {
    // Bitwise Exclusive with Accumulator: Absolute addressing indexed Y
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

void CPU::eor_absolute_x(MemoryUnit &r) {
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

// ADC
void CPU::adc_indirect_x(MemoryUnit &r) {
    // Add to the Accumulator: Indirect Reg-X addressing
    // PC += 2

    instPtr++;
    uint16_t alpha = regX, beta = r.getByteAt(instPtr);
    instPtr++;
    uint8_t addr = ((alpha+beta)&0xFF);
    uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
    uint16_t finalAddr = (kapa | (napa << 8));
    uint8_t m=regAcc, n=r.getByteAt(finalAddr), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

void CPU::adc_zeropg(MemoryUnit &r) {
    // Add to the Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t m=regAcc, n=r.getByteAt(alpha), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

void CPU::adc_immediate(MemoryUnit &r) {
    // Add to Accumulator: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint16_t zeta = uint16_t(regAcc)+uint16_t(alpha)+\
                    uint16_t(getCarryFlag());
    uint8_t m=regAcc, n=alpha, res;
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

void CPU::adc_absolute(MemoryUnit &r) {
    // Add to the Accumulator: Absolute addressing
    // PC += 3

    instPtr++;
    uint16_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint16_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    uint8_t m=regAcc, n=r.getByteAt(addr), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

void CPU::adc_indirect_y(MemoryUnit &r) {
    // Add to Accumulator: Zero Page Y indexed
    // PC += 2

    instPtr++;
    uint16_t alpha = regY, beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
    uint16_t addr = kapa|(napa<<8);
    uint8_t m=regAcc, n=r.getByteAt(addr+alpha), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

void CPU::adc_zeropg_x(MemoryUnit &r) {
    // Add to the Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    uint8_t m=regAcc, n=r.getByteAt(addr), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);

}

void CPU::adc_absolute_y(MemoryUnit &r) {
    // Add to the Accumulator: Absolute addressing indexed Y
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regY;
    uint8_t m=regAcc, n=r.getByteAt(addr), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);

}

void CPU::adc_absolute_x(MemoryUnit &r) {
    // Add to the Accumulator: Absolute addressing indexed X
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regX;
    uint8_t m=regAcc, n=r.getByteAt(addr), res;

    uint16_t zeta = uint16_t(regAcc)+uint16_t(n)+\
                    uint16_t(getCarryFlag());
    regAcc = zeta%256;
    res = regAcc;
    uint8_t overflow=!((m^n)&0x80)&&((m^res)&0x80), carry=0;
    carry = zeta/256;
    changeFlags(carry, overflow);
}

// STA
void CPU::sta_indirect_x(MemoryUnit &r) {
    // Store contents of accumulator to address: Indirect Reg-X addressing
    // PC += 2

    instPtr++;
    uint16_t alpha = regX, beta = r.getByteAt(instPtr);
    instPtr++;
    uint8_t addr = ((alpha+beta)&0xFF);
    uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
    uint16_t finalAddr = (kapa | (napa << 8));
    r.setByteAt(finalAddr, regAcc);
}

void CPU::sta_zeropg(MemoryUnit &r) {
    // Store contents of accumulator to address: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    r.setByteAt(alpha, regAcc);
}

void CPU::sta_immediate(MemoryUnit &r) {
    // An invalid instruction
    throw InvalidOpcodeException(0b10001001);
}

void CPU::sta_absolute(MemoryUnit &r) {
    // Store contents of accumulator to address: Absolute addressing
    // PC += 3

    instPtr++;
    uint16_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint16_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    r.setByteAt(addr, regAcc);
}

void CPU::sta_indirect_y(MemoryUnit &r) {
    // Store contents of accumulator to address: Zero Page Y indexed
    // PC += 2

    instPtr++;
    uint16_t alpha = regY, beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
    uint16_t addr = kapa|(napa<<8);
    r.setByteAt(addr+alpha, regAcc);
}

void CPU::sta_zeropg_x(MemoryUnit &r) {
    // Store contents of accumulator to address: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    r.setByteAt(addr, regAcc);
}

void CPU::sta_absolute_y(MemoryUnit &r) {
    // Store contents of accumulator to address: Absolute addressing indexed Y
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regY;
    r.setByteAt(addr, regAcc);
}

void CPU::sta_absolute_x(MemoryUnit &r) {
    // Store contents of accumulator to address: Absolute addressing indexed X
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regX;
    r.setByteAt(addr, regAcc);
}

// LDA
void CPU::lda_indirect_x(MemoryUnit &r) {
    // Load Accumulator: Indirect Reg-X addressing
    // PC += 2

    instPtr++;
    uint16_t alpha = regX, beta = r.getByteAt(instPtr);
    instPtr++;
    uint8_t addr = ((alpha+beta)&0xFF);
    uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
    uint16_t finalAddr = (kapa | (napa << 8));
    regAcc = r.getByteAt(finalAddr);
    changeFlags();
}

void CPU::lda_zeropg(MemoryUnit &r) {
    // Load Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = r.getByteAt(alpha);
    changeFlags();
}

void CPU::lda_immediate(MemoryUnit &r) {
    // Load Accumulator: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    regAcc = alpha;
    changeFlags();
}

void CPU::lda_absolute(MemoryUnit &r) {
    // Load Accumulator: Absolute addressing
    // PC += 3

    instPtr++;
    uint16_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint16_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    regAcc = r.getByteAt(addr);
    changeFlags();
}

void CPU::lda_indirect_y(MemoryUnit &r) {
    // Load Accumulator: Zero Page Y indexed
    // PC += 2

    instPtr++;
    uint16_t alpha = regY, beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
    uint16_t addr = kapa|(napa<<8);
    regAcc = r.getByteAt(addr+alpha);
    changeFlags();
}

void CPU::lda_zeropg_x(MemoryUnit &r) {
    // Load Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    regAcc = r.getByteAt(addr);
    changeFlags();
}

void CPU::lda_absolute_y(MemoryUnit &r) {
    // Load Accumulator: Absolute addressing indexed Y
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regY;
    regAcc = r.getByteAt(addr);
    changeFlags();
}

void CPU::lda_absolute_x(MemoryUnit &r) {
    // Load Accumulator: Absolute addressing indexed X
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regX;
    regAcc = r.getByteAt(addr);
    changeFlags();
}

// CMP
void CPU::cmp_indirect_x(MemoryUnit &r) {
    // Compare Accumulator and Memory: Indirect X
    // PC += 2
    instPtr++;
    uint16_t alpha = regX, beta = r.getByteAt(instPtr);
    instPtr++;
    uint8_t addr = ((alpha+beta)&0xFF);
    uint8_t kapa = r.getByteAt(addr), napa = r.getByteAt(addr+1);
    uint16_t finalAddr = (kapa | (napa << 8));
    uint8_t val = regAcc-r.getByteAt(finalAddr);
    
    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_zeropg(MemoryUnit &r) {
    // Compare Accumulator: Zero Page Addressing
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t val = regAcc-r.getByteAt(alpha);
    
    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_immediate(MemoryUnit &r) {
    // Compare: Immediate addressing
    // PC += 2
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t val = regAcc-alpha;
    
    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_absolute(MemoryUnit &r) {
    // Compare Accumulator: Absolute addressing
    // PC += 3

    instPtr++;
    uint16_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint16_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    uint8_t val = regAcc-r.getByteAt(addr);
    
    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_indirect_y(MemoryUnit &r) {
    // Compare Accumulator: Zero Page Y indexed
    // PC += 2

    instPtr++;
    uint16_t alpha = regY, beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t kapa = r.getByteAt(beta), napa = r.getByteAt((beta+1)%256);
    uint16_t addr = kapa|(napa<<8);
    uint8_t val = regAcc-r.getByteAt(addr+alpha);

    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_zeropg_x(MemoryUnit &r) {
    // Compare Accumulator: Zero Page X Indexed
    // PC += 2

    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr), beta = regX;
    instPtr++;
    uint16_t addr = (alpha + regX)%256;
    uint8_t val = regAcc-r.getByteAt(addr);

    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_absolute_y(MemoryUnit &r) {
    // Compare Accumulator: Absolute addressing indexed Y
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regY;
    uint8_t val = regAcc-r.getByteAt(addr);

    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

void CPU::cmp_absolute_x(MemoryUnit &r) {
    // Compare Accumulator: Absolute addressing indexed X
    // PC += 3
    instPtr++;
    uint8_t alpha = r.getByteAt(instPtr);
    instPtr++;
    uint8_t beta = r.getByteAt(instPtr);
    instPtr++;
    uint16_t addr = (alpha|(beta<<8));
    addr += regX;
    uint8_t val = regAcc-r.getByteAt(addr);

    if (val&(1<<7)) {
        setNegetiveFlag(1);
    } else {
        setNegetiveFlag(0);
    }

    if (val < 0x100) {
        setCarryFlag(1);
    } else {
        setCarryFlag(0);
    }

    if (val == 0) {
        setZeroFlag(1);
    } else {
        setZeroFlag(0);
    }
}

// publics
bool CPU::executeInstruction(MemoryUnit &r) {
    // Runs the opcode after fetching from RAM
    uint8_t opcode = r.getByteAt(instPtr);
    try {
        if (opcodeNotAvailable(opcode)) throw InvalidOpcodeException(opcode);
        opcodeFun fun = opCodes.find(opcode)->second;
        (this->*fun)(r);
        return true;
    } catch (InvalidOpcodeException &e) {
        printf("Warning: %s: %u\n", e.what(), opcode);
        throw e;
    }
}

uint8_t CPU::getOpcode(const string &S) const {
    return opcodeNameLookup.find(S)->second;
}


} // NES
