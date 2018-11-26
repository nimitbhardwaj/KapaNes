#ifndef INVALID_OPCODE_EXCEPTION_HPP
#define INVALID_OPCODE_EXCEPTION_HPP

#include <exception>
#include <cstdint>
#include <string>

using std::exception;

namespace NES
{
    class InvalidOpcodeException : public exception {
    private:
        uint8_t opCode;
    public:
    InvalidOpcodeException(uint8_t x)
        :opCode(x) {}
        virtual const char *what() throw() {
            std::string S = "Invalid OpCode: Unknown Opcode "+std::to_string(int(opCode));
            return S.c_str();
        } 
};

} // NES



#endif