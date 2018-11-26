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
using std::string;

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
        unordered_map<string, uint8_t> opcodeNameLookup;

        uint8_t makeOpCode(uint8_t a, uint8_t b, uint8_t c) const;
        bool opcodeNotAvailable(uint8_t opcode);
        void insertOpcode(uint8_t opcode, opcodeFun, const string &);
        // Flags Structure: -----NZ
        void changeFlags();


        // Functions of CPU

        // ORA
        void ora_indirect_x(const MemoryUnit &); //000-000-01
        void ora_zeropg(const MemoryUnit &); //000-001-01
        void ora_immediate(const MemoryUnit &); //000-010-01
        void ora_absolute(const MemoryUnit &); //000-011-01
        void ora_indirect_y(const MemoryUnit &); //000-100-01
        void ora_zeropg_x(const MemoryUnit &r); //000-101-01
        void ora_absolute_y(const MemoryUnit &r); //000-110-01
        void ora_absolute_x(const MemoryUnit &r); //000-111-01

        //AND
        void and_indirect_x(const MemoryUnit &); //001-000-01
        void and_zeropg(const MemoryUnit &); //001-001-01
        void and_immediate(const MemoryUnit &); //001-010-01
        void and_absolute(const MemoryUnit &); //001-011-01
        void and_indirect_y(const MemoryUnit &); //001-100-01
        void and_zeropg_x(const MemoryUnit &r); //001-101-01
        void and_absolute_y(const MemoryUnit &r); //001-110-01
        void and_absolute_x(const MemoryUnit &r); //001-111-01



    public:
        CPU();
        ~CPU();
        bool executeInstruction(const MemoryUnit &);
        uint8_t getOpcode(const string &) const;

        inline uint8_t getAccumulator() const { return regAcc; }
        inline uint8_t getRegX() const { return regX; }
        inline uint8_t getRegY() const { return regY; }
        inline uint16_t getInstPtr() const { return instPtr; }
        inline uint16_t getStackPtr() const { return stackPtr; }
        inline uint8_t getFlags() const { return flags; }

        inline void setInstPtr(uint16_t x) { instPtr = x; }
        inline void setRegX(uint8_t x) { regX = x; }
        inline void setRegY(uint8_t x) { regY = x; }
        inline void setAccumulator(uint8_t x) { regAcc = x;changeFlags(); }

        inline uint8_t getZeroFlag() const { return (flags&1)==0?0:1; }
        inline uint8_t getNegetive() const { return (flags & (1<<1))==0?0:1; }

};


} // NES
#endif