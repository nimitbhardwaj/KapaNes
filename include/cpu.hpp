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
        typedef void (CPU::*opcodeFun)(MemoryUnit &);
        typedef unordered_map<uint8_t, opcodeFun> opcodeMap;

        uint8_t regAcc, regX, regY, flags;
        uint16_t stackPtr, instPtr;
        opcodeMap opCodes;
        unordered_set<uint8_t> opcodeBag;
        unordered_map<string, uint8_t> opcodeNameLookup;

        bool opcodeNotAvailable(uint8_t opcode);
        void insertOpcode(uint8_t opcode, opcodeFun, const string &);
        // Flags Structure: ----VCNZ
        void changeFlags(uint8_t carry = -1, uint8_t overflow=-1);


        // Functions of CPU

        // ORA
        void ora_indirect_x(MemoryUnit &); //000-000-01
        void ora_zeropg(MemoryUnit &); //000-001-01
        void ora_immediate(MemoryUnit &); //000-010-01
        void ora_absolute(MemoryUnit &); //000-011-01
        void ora_indirect_y(MemoryUnit &); //000-100-01
        void ora_zeropg_x(MemoryUnit &r); //000-101-01
        void ora_absolute_y(MemoryUnit &r); //000-110-01
        void ora_absolute_x(MemoryUnit &r); //000-111-01

        // AND
        void and_indirect_x(MemoryUnit &); //001-000-01
        void and_zeropg(MemoryUnit &); //001-001-01
        void and_immediate(MemoryUnit &); //001-010-01
        void and_absolute(MemoryUnit &); //001-011-01
        void and_indirect_y(MemoryUnit &); //001-100-01
        void and_zeropg_x(MemoryUnit &r); //001-101-01
        void and_absolute_y(MemoryUnit &r); //001-110-01
        void and_absolute_x(MemoryUnit &r); //001-111-01

        // EOR
        void eor_indirect_x(MemoryUnit &); //010-000-01
        void eor_zeropg(MemoryUnit &); //010-001-01
        void eor_immediate(MemoryUnit &); //010-010-01
        void eor_absolute(MemoryUnit &); //010-011-01
        void eor_indirect_y(MemoryUnit &); //010-100-01
        void eor_zeropg_x(MemoryUnit &r); //010-101-01
        void eor_absolute_y(MemoryUnit &r); //010-110-01
        void eor_absolute_x(MemoryUnit &r); //010-111-01

        // ADC
        void adc_indirect_x(MemoryUnit &); //011-000-01
        void adc_zeropg(MemoryUnit &); //011-001-01
        void adc_immediate(MemoryUnit &); //011-010-01
        void adc_absolute(MemoryUnit &); //011-011-01
        void adc_indirect_y(MemoryUnit &); //011-100-01
        void adc_zeropg_x(MemoryUnit &r); //011-101-01
        void adc_absolute_y(MemoryUnit &r); //011-110-01
        void adc_absolute_x(MemoryUnit &r); //011-111-01

        // STA
        void sta_indirect_x(MemoryUnit &); //100-000-01
        void sta_zeropg(MemoryUnit &); //100-001-01
        void sta_immediate(MemoryUnit &); //100-010-01
        void sta_absolute(MemoryUnit &); //100-011-01
        void sta_indirect_y(MemoryUnit &); //100-100-01
        void sta_zeropg_x(MemoryUnit &r); //100-101-01
        void sta_absolute_y(MemoryUnit &r); //100-110-01
        void sta_absolute_x(MemoryUnit &r); //100-111-01

        // LDA
        void lda_indirect_x(MemoryUnit &); //101-000-01
        void lda_zeropg(MemoryUnit &); //101-001-01
        void lda_immediate(MemoryUnit &); //101-010-01
        void lda_absolute(MemoryUnit &); //101-011-01
        void lda_indirect_y(MemoryUnit &); //101-100-01
        void lda_zeropg_x(MemoryUnit &r); //101-101-01
        void lda_absolute_y(MemoryUnit &r); //101-110-01
        void lda_absolute_x(MemoryUnit &r); //101-111-01
        
        // CMP
        void cmp_indirect_x(MemoryUnit &); //110-000-01
        void cmp_zeropg(MemoryUnit &); //110-001-01
        void cmp_immediate(MemoryUnit &); //110-010-01
        void cmp_absolute(MemoryUnit &); //110-011-01
        void cmp_indirect_y(MemoryUnit &); //110-100-01
        void cmp_zeropg_x(MemoryUnit &r); //110-101-01
        void cmp_absolute_y(MemoryUnit &r); //110-110-01
        void cmp_absolute_x(MemoryUnit &r); //110-111-01


    public:
        CPU();
        ~CPU();
        bool executeInstruction(MemoryUnit &);
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
        inline uint8_t getNegetiveFlag() const { return (flags & (1<<1))==0?0:1; }
        inline uint8_t getCarryFlag() const { return (flags & (1<<2))==0?0:1; }
        inline uint8_t getOverflowFlag() const { return (flags & (1<<3))==0?0:1; }

        inline void setZeroFlag(uint8_t x) {flags=(x==0)?(flags&(~(1<<0))):(flags|(1<<0));}
        inline void setNegetiveFlag(uint8_t x) {flags=(x==0)?(flags&(~(1<<1))):(flags|(1<<1));}
        inline void setCarryFlag(uint8_t x) {flags=(x==0)?(flags&(~(1<<2))):(flags|(1<<2));}
        inline void setOverflowFlag(uint8_t x) {flags=(x==0)?(flags&(~(1<<3))):(flags|(1<<3));}


};


} // NES
#endif