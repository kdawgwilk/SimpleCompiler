//
//  MachineCodes.hpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 4/27/17.
//
//

#ifndef MachineCodes_hpp
#define MachineCodes_hpp

#pragma once

struct MachineCode {
    const string mName;
    const unsigned char mCode;

public:
    MachineCode(const string name, const unsigned char code) : mName(name), mCode(code) {}
};

//auto PUSH_EBP            = MachineCode("PUSH_EBP",         0x55);
//auto MOV_EBP_ESP1        = MachineCode("MOV_EBP_ESP1",     0x8B);
//auto MOV_EBP_ESP2        = MachineCode("MOV_EBP_ESP2",     0xEC);
//auto POP_EBP             = MachineCode("POP_EBP",          0x5D);
//auto NEAR_RET            = MachineCode("NEAR_RET",         0xC3); // C3 hex, 195 decimal, 11000011 binary
//auto IMMEDIATE_TO_EAX    = MachineCode("IMMEDIATE_TO_EAX", 0xB8); // followed by 4 byte value.
//auto PUSH_EAX            = MachineCode("PUSH_EAX",         0x50);
//auto PUSH_EDX            = MachineCode("PUSH_EDX",         0x52);
//auto CALL                = MachineCode("CALL",             0xE8); // call within segment, Add 4 byte offset in reverse order
//auto POP_EAX             = MachineCode("POP_EAX",          0x58);
//auto EAX_TO_MEM          = MachineCode("EAX_TO_MEM",       0xA3); // A3 hex, Add 4 (or 8) byte address value in reverse order
//auto MEM_TO_EAX          = MachineCode("MEM_TO_EAX",       0xA1); // A1 hex, Add 4 (or 8) byte address value in reverse order
//
//auto POP_EBX             = MachineCode("POP_EBX",          0x5B);
//auto ADD_EAX_EBX1        = MachineCode("ADD_EAX_EBX1",     0x03);
//auto ADD_EAX_EBX2        = MachineCode("ADD_EAX_EBX2",     0xC3);
//auto SUB_EAX_EBX1        = MachineCode("SUB_EAX_EBX1",     0x2B);
//auto SUB_EAX_EBX2        = MachineCode("SUB_EAX_EBX2",     0xC3);
//auto MUL_EAX_EBX1        = MachineCode("MUL_EAX_EBX1",     0xF7);
//auto MUL_EAX_EBX2        = MachineCode("MUL_EAX_EBX2",     0xEB);
//auto DIV_EAX_EBX1        = MachineCode("DIV_EAX_EBX1",     0xF7);
//auto DIV_EAX_EBX2        = MachineCode("DIV_EAX_EBX2",     0xFB);
//auto CDQ                 = MachineCode("CDQ",              0x99);
//auto CMP_EAX_EBX1        = MachineCode("CMP_EAX_EBX1",     0x3B); // compares A and B registers.
//auto CMP_EAX_EBX2        = MachineCode("CMP_EAX_EBX2",     0xC3);
//auto JUMP_ALWAYS         = MachineCode("JUMP_ALWAYS",      0xEB);
//auto JL                  = MachineCode("JL",               0x7C);
//auto JLE                 = MachineCode("JLE",              0x7E);
//auto JG                  = MachineCode("JG",               0x7F);
//auto JGE                 = MachineCode("JGE",              0x7D);
//auto JE                  = MachineCode("JE",               0x74);
//auto JNE                 = MachineCode("JNE",              0x75);
//
////auto JE_WORD             = MachineCode("JE_WORD",          0x84); // 2 byte jump does NOT work!
//auto JE_FAR1             = MachineCode("JE_FAR1",          0x0f); // 4 byte jump
//auto JE_FAR2             = MachineCode("JE_FAR2",          0x84); // 4 byte jump
//auto JUMP_ALWAYS_FAR     = MachineCode("JUMP_ALWAYS_FAR",  0xE9); // 4 byte jump (NOT 2 byte!


const unsigned char PUSH_EBP = 0x55;
const unsigned char MOV_EBP_ESP1 = 0x8B;
const unsigned char MOV_EBP_ESP2 = 0xEC;
const unsigned char POP_EBP = 0x5D;
const unsigned char NEAR_RET = 0xC3; // C3 hex, 195 decimal, 11000011 binary
const unsigned char IMMEDIATE_TO_EAX = 0xB8; // followed by 4 byte value.
const unsigned char PUSH_EAX = 0x50;
const unsigned char PUSH_EDX = 0x52;
const unsigned char CALL = 0xE8; // call within segment, Add 4 byte offset in reverse order
const unsigned char POP_EAX = 0x58;
const unsigned char EAX_TO_MEM = 0xA3; // A3 hex, Add 4 (or 8) byte address value in reverse order
const unsigned char MEM_TO_EAX = 0xA1; // A1 hex, Add 4 (or 8) byte address value in reverse order

const unsigned char POP_EBX = 0x5B;
const unsigned char ADD_EAX_EBX1 = 0x03;
const unsigned char ADD_EAX_EBX2 = 0xC3;
const unsigned char SUB_EAX_EBX1 = 0x2B;
const unsigned char SUB_EAX_EBX2 = 0xC3;
const unsigned char MUL_EAX_EBX1 = 0xF7;
const unsigned char MUL_EAX_EBX2 = 0xEB;
const unsigned char DIV_EAX_EBX1 = 0xF7;
const unsigned char DIV_EAX_EBX2 = 0xFB;
const unsigned char CDQ = 0x99;
const unsigned char CMP_EAX_EBX1 = 0x3B; // compares A and B registers.
const unsigned char CMP_EAX_EBX2 = 0xC3;
const unsigned char JUMP_ALWAYS = 0xEB;
const unsigned char JL = 0x7C;
const unsigned char JLE = 0x7E;
const unsigned char JG = 0x7F;
const unsigned char JGE = 0x7D;
const unsigned char JE = 0x74;
const unsigned char JNE = 0x75;

//const unsigned char JE_WORD = 0x84; // 2 byte jump does NOT work!
const unsigned char JE_FAR1 = 0x0f; // 4 byte jump
const unsigned char JE_FAR2 = 0x84; // 4 byte jump
const unsigned char JUMP_ALWAYS_FAR = 0xE9; // 4 byte jump (NOT 2 byte!


#endif /* MachineCodes_hpp */
