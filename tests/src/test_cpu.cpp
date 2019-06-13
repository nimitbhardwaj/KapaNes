#include "../include/test_cpu.hpp"


void CPUTest::testFlags() {
    // Zero and Negetive flag
    cpu->setAccumulator(0x00);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    cpu->setAccumulator(0xFF);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    // Carry and Overflow Flag
    cpu->setAccumulator(0x01);
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01101001);
    mem->setByteAt(0x01, 0x01);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

    cpu->setAccumulator(0x01);
    mem->setByteAt(0x02, 0b01101001);
    mem->setByteAt(0x03, 0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

    cpu->setAccumulator(0x7F);
    mem->setByteAt(0x04, 0b01101001);
    mem->setByteAt(0x05, 0x01);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);

    cpu->setAccumulator(0x80);
    mem->setByteAt(0x06, 0b01101001);
    mem->setByteAt(0x07, 0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);
}

// CPU Opcode tests

//ORA
void CPUTest::testOraIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b00000001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11100101);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b00000001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
}

void CPUTest::testOraZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00000101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110110);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110110);

    mem->setByteAt(0x02, 0b00000101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b11111110);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111110);
}

void CPUTest::testOraImm() {
    mem->setByteAt(0x00, 0b00001001);
    mem->setByteAt(0x01, 0b11110000);
    mem->setByteAt(0x02, 0b00001001);
    mem->setByteAt(0x03, 0b10000001);
    cpu->setInstPtr(0x00);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110001);
}

void CPUTest::testOraAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00001101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b01010101);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01010101);

    mem->setByteAt(0x03, 0b00001101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b10101010);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
}

void CPUTest::testOraIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00010001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b01100011);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01100011);
}

void CPUTest::testOraZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b00010101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11100000);

    mem->setByteAt(0x02, 0b00010101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
}

void CPUTest::testOraAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b00011001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
}

void CPUTest::testOraAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b00011101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
}

// AND
void CPUTest::testAndIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b00100001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11100000);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b00100001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01100000);
}

void CPUTest::testAndZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00100101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110110);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110110);

    mem->setByteAt(0x02, 0b00100101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b10110001);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10110000);
}

void CPUTest::testAndImm() {
    mem->setByteAt(0x00, 0b00101001);
    mem->setByteAt(0x01, 0b11110000);
    mem->setByteAt(0x02, 0b00101001);
    mem->setByteAt(0x03, 0b10000001);
    cpu->setInstPtr(0x00);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10000000);
}

void CPUTest::testAndAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00101101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b01010101);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01010101);

    mem->setByteAt(0x03, 0b00101101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01010000);
}

void CPUTest::testAndIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b00110001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b01100011);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01100011);
}

void CPUTest::testAndZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b00110101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100000);
    cpu->setAccumulator(0b00100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00100000);

    mem->setByteAt(0x02, 0b00110101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00100000);
}

void CPUTest::testAndAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b00111001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01110000);
}

void CPUTest::testAndAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b00111101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b10010000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10010000);
}

// EOR
void CPUTest::testEorIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b01000001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00000101);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b01000001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111010);
}

void CPUTest::testEorZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01000101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110110);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00001001);

    mem->setByteAt(0x02, 0b01000101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b10110001);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10111000);
}

void CPUTest::testEorImm() {
    mem->setByteAt(0x00, 0b01001001);
    mem->setByteAt(0x01, 0b11110000);
    mem->setByteAt(0x02, 0b01001001);
    mem->setByteAt(0x03, 0b10000001);
    cpu->setInstPtr(0x00);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00001111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10001110);
}

void CPUTest::testEorAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01001101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b01010101);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10101010);

    mem->setByteAt(0x03, 0b01001101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01011010);
}

void CPUTest::testEorIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01010001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b01100011);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10011100);
}

void CPUTest::testEorZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b01010101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100000);
    cpu->setAccumulator(0b00100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000000);

    mem->setByteAt(0x02, 0b01010101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b00111111);
}

void CPUTest::testEorAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b01011001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10001111);
}

void CPUTest::testEorAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b01011101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b10010000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01101111);
}

// ADC
void CPUTest::testAdcIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b01100001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b01100001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b10110111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);
}

void CPUTest::testAdcZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01100101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);


    mem->setByteAt(0x02, 0b01100101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b10110111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);
}

void CPUTest::testAdcImm() {
    mem->setByteAt(0x00, 0b01101001);
    mem->setByteAt(0x01, 0b11100101);
    mem->setByteAt(0x02, 0b01101001);
    mem->setByteAt(0x03, 0b10110111);
    cpu->setInstPtr(0x00);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);

}

void CPUTest::testAdcAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01101101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

    mem->setByteAt(0x03, 0b01101101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b10110111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);
}

void CPUTest::testAdcIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b01110001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

}

void CPUTest::testAdcZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b01110101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);

    mem->setByteAt(0x02, 0b01110101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b10110111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 1);

}

void CPUTest::testAdcAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b01111001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);
}

void CPUTest::testAdcAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b01111101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11000101);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getOverflowFlag() == 0);
}

// STA
void CPUTest::testStaIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b10000001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->setAccumulator(0b11100100);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0201) == 0b11100100);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b10000001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0011) == 0b11100100);
}

void CPUTest::testStaZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10000101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110110);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x83) == 0b11111111);

    mem->setByteAt(0x02, 0b10000101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b10110001);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x8E) == 0b11111111);
}

void CPUTest::testStaImm() {
    // Always Assert true, there is no instruction with it
    CPPUNIT_ASSERT(true);
}

void CPUTest::testStaAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10001101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b01010101);
    cpu->setAccumulator(0xAB);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0210) == 0xAB);

    mem->setByteAt(0x03, 0b10001101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0011) == 0xAB);
}

void CPUTest::testStaIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10010001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b01100011);
    cpu->setAccumulator(0xAF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0118) == 0xAF);
}

void CPUTest::testStaZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b10010101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100000);
    cpu->setAccumulator(0xAB);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x8A) == 0xAB);

    mem->setByteAt(0x02, 0b10010101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x10) == 0xAB);
}

void CPUTest::testStaAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b10011001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0314) == 0b01111111);
}

void CPUTest::testStaAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b10011101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b10010000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(mem->getByteAt(0x0314) == 0b11111111);
}

// LDA
void CPUTest::testLdaIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b10100001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11100101);
    cpu->setAccumulator(0b11100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11100101);
    
    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b10100001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01111111);
}

void CPUTest::testLdaZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10100101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110110);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110110);

    mem->setByteAt(0x02, 0b10100101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0b10110001);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10110001);
}

void CPUTest::testLdaImm() {
    mem->setByteAt(0x00, 0b10101001);
    mem->setByteAt(0x01, 0b11110000);
    mem->setByteAt(0x02, 0b10101001);
    mem->setByteAt(0x03, 0b10000001);
    cpu->setInstPtr(0x00);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10000001);
}

void CPUTest::testLdaAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10101101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b01010101);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01010101);

    mem->setByteAt(0x03, 0b10101101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0b11110000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
}

void CPUTest::testLdaIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b10110001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b01100011);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b01100011);
}

void CPUTest::testLdaZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b10110101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11100000);
    cpu->setAccumulator(0b00100000);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11100000);

    mem->setByteAt(0x02, 0b10110101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
}

void CPUTest::testLdaAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b10111001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b01111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11110000);
}

void CPUTest::testLdaAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b10111101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b10010000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b10010000);
}

// CMP

void CPUTest::testCmpIndX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x04);
    mem->setByteAt(0x00, 0b11000001);
    mem->setByteAt(0x01, 0x20);
    mem->setByteAt(0x24, 01);
    mem->setByteAt(0x25, 02);
    mem->setByteAt(0x0201, 0b11110000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    cpu->setAccumulator(0x30);

    cpu->setRegX(0x10);
    mem->setByteAt(0x02, 0b11000001);
    mem->setByteAt(0x03, 0xFF);
    mem->setByteAt(0x0F, 0x11);
    mem->setByteAt(0x10, 0x00);
    mem->setByteAt(0x0011, 0x6A);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0x30);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);

}

void CPUTest::testCmpZeroPg() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b11000101);
    mem->setByteAt(0x01, 0x83);
    mem->setByteAt(0x83, 0b11110000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    cpu->setAccumulator(0x30);

    mem->setByteAt(0x02, 0b11000101);
    mem->setByteAt(0x03, 0x8E);
    mem->setByteAt(0x08E, 0x6A);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0x30);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpImm() {
    mem->setByteAt(0x00, 0b11001001);
    mem->setByteAt(0x01, 0b11110000);
    mem->setByteAt(0x02, 0b11001001);
    mem->setByteAt(0x03, 0x6A);
    cpu->setInstPtr(0x00);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0b11111111);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    cpu->setAccumulator(0x30);

    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0x30);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpAbsolute() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b11001101);
    mem->setByteAt(0x01, 0x10);
    mem->setByteAt(0x02, 0x02);
    mem->setByteAt(0x0210, 0b11110000);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0xFF);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    cpu->setAccumulator(0x30);

    mem->setByteAt(0x03, 0b11001101);
    mem->setByteAt(0x04, 0x11);
    mem->setByteAt(0x05, 0x00);
    mem->setByteAt(0x0011, 0x6A);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0x30);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpIndirectY() {
    cpu->setInstPtr(0x00);
    mem->setByteAt(0x00, 0b11010001);
    mem->setByteAt(0x01, 0x24);
    cpu->setRegY(0x06);
    mem->setByteAt(0x24, 0x12);
    mem->setByteAt(0x25, 0x01);
    mem->setByteAt(0x0118, 0b11110000);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0xFF);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpZeroPgX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x08);
    mem->setByteAt(0x00, 0b11010101);
    mem->setByteAt(0x01, 0x82);
    mem->setByteAt(0x8A, 0b11110000);
    cpu->setAccumulator(0xFF);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0xFF);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
    cpu->setAccumulator(0x30);

    mem->setByteAt(0x02, 0b11010101);
    mem->setByteAt(0x03, 0xFF);
    cpu->setRegX(0x11);
    mem->setByteAt(0x10, 0x6A);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0x30);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 0);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 1);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpAbsY() {
    cpu->setInstPtr(0x00);
    cpu->setRegY(0x03);
    mem->setByteAt(0x00, 0b11011001);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0xFF);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}

void CPUTest::testCmpAbsX() {
    cpu->setInstPtr(0x00);
    cpu->setRegX(0x03);
    mem->setByteAt(0x00, 0b11011101);
    mem->setByteAt(0x01, 0x11);
    mem->setByteAt(0x02, 0x03);
    mem->setByteAt(0x0314, 0b11110000);
    cpu->setAccumulator(0b11111111);
    cpu->executeInstruction(*mem);
    CPPUNIT_ASSERT(cpu->getAccumulator() == 0xFF);
    CPPUNIT_ASSERT(cpu->getCarryFlag() == 1);
    CPPUNIT_ASSERT(cpu->getNegetiveFlag() == 0);
    CPPUNIT_ASSERT(cpu->getZeroFlag() == 0);
}
