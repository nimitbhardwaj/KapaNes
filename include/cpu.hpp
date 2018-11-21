#ifndef CPU_HPP_

#define CPU_HPP_

#include <memory_unit.hpp>

#include <cstdint>
#include <string>
#include <cstdio>
#include <unordered_map>
#include <unordered_set>
#include <invalid_opcode_exception.hpp>

using std::string;
using std::unordered_map;
using std::unordered_set;

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
        typedef void (CPU::*opcodeFun)(const MemoryUnit &);
        typedef unordered_map<uint8_t, opcodeFun> opcodeMap;

        uint8_t regAcc, regX, regY, flags;
        uint16_t stackPtr, instPtr;

        opcodeMap opCodes;
        unordered_set<uint8_t> opcodeBag;

        uint8_t makeOpCode(uint8_t a, uint8_t b, uint8_t c) const;
        bool opcodeNotAvailable(uint8_t opcode);
        void insertOpcode(uint8_t opcode, opcodeFun);
        void changeFlags();


        // Functions of CPU
        void ora_indirect_x(const MemoryUnit &); //000-000-01
        void ora_zeropg(const MemoryUnit &); //000-001-01
        void ora_immediate(const MemoryUnit &); //000-010-01
        void ora_absolute(const MemoryUnit &); //000-011-01
        void ora_indirect_y(const MemoryUnit &); //000-100-01
        void ora_zeropg_x(const MemoryUnit &r); //000-101-01
        void ora_absolute_y(const MemoryUnit &r); //000-110-01
        void ora_absolute_x(const MemoryUnit &r); //000-111-01


    public:
        CPU();
        ~CPU();
        bool executeInstruction(const MemoryUnit &);
};


} // NES
#endif