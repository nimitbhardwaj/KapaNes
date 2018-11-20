#ifndef CPU_HPP_

#define CPU_HPP_

#include <ram.hpp>

#include <cstdint>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <invalid_opcode_exception.hpp>

using std::string;
using std::unordered_map;

namespace NES 
{

class CPU {
    /*
     * CPU of NES is just a 6502 architecture without the BCD support
     * It has two 16-bit registers namely stack pointer and instruction pointer
     * It has three 8-bit registers namely Accumulator, X-Register and Y-Register
     * A flags register is also there of size 8 bits, having seven flags total
     * one bit is not used.
     * 
     * Any Mnemonic of 8-bit size can be decoded to aaabbbcc bits.
     * Each bit having some specific significance
    */
    private:
        typedef void (CPU::*opcodeFun)(const Ram &);
        typedef unordered_map<uint8_t, opcodeFun> opcodeMap;

        uint8_t regAcc, regX, regY, flags;
        uint16_t stackPtr, instPtr;

        // List of Mnemonics having cc = 01
        opcodeMap opCodes_01;

        uint8_t makeOpCode(uint8_t a, uint8_t b, uint8_t c) const;

        // Functions of CPU
        void ora_indirect_x(const Ram &); //000-000-01
        void ora_zeropg(const Ram &); //000-001-01
        void ora_immediate(const Ram &); //000-010-01
        void ora_absolute(const Ram &); //000-011-01
        void ora_indirect_y(const Ram &); //000-100-01
        void ora_zeropg_x(const Ram &r); //000-101-01
        void ora_absolute_y(const Ram &r); //000-110-01
        void ora_absolute_x(const Ram &r); //000-111-01


    public:
        CPU();
        ~CPU();
        bool executeInstruction(const Ram &);
};


} // NES
#endif