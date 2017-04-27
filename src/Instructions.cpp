//
//  Instructions.cpp
//  SimpleCompiler
//
//  Created by Kaden Wilkinson on 4/15/17.
//
//

#include "Instructions.hpp"


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

// Initialize static class variables
unsigned char InstructionsClass::mCode[MAX_INSTRUCTIONS] = {0};

void HelperPrintInteger(void);

InstructionsClass::InstructionsClass()
: mCurrent(0)
{
    void *p = NULL;
    int pointerSize = sizeof(p);
    if (pointerSize == 4) {
        cout << "Compiling for 32 bit" << endl;
    } else if (sizeof(p) == 8) {
        cout << "Compiling for 64 bit" << endl;
    }

    Encode(PUSH_EBP);
    Encode(MOV_EBP_ESP1);
    Encode(MOV_EBP_ESP2);
}

void InstructionsClass::Encode(unsigned char c) {
    if (mCurrent < MAX_INSTRUCTIONS) {
        InstructionsClass::mCode[mCurrent++] = c;
    } else {
        cerr << "Error. Used up all " << MAX_INSTRUCTIONS << " instructions." << endl;
        exit(1);
    }
}

void InstructionsClass::Encode(int x) {
    if (mCurrent < MAX_INSTRUCTIONS) {
        *((int *)(&(InstructionsClass::mCode[mCurrent]))) = x;
        mCurrent += sizeof(int);
    } else {
        cerr << "Error. Used up all " << MAX_INSTRUCTIONS << " instructions." << endl;
        exit(1);
    }
}

void InstructionsClass::Encode(long long x) {
    if (mCurrent < MAX_INSTRUCTIONS) {
        *((long long*)(&(InstructionsClass::mCode[mCurrent]))) = x;
        mCurrent += sizeof(long long);
    } else {
        cerr << "Error. Used up all " << MAX_INSTRUCTIONS << " instructions." << endl;
        exit(1);
    }
}

void InstructionsClass::Encode(void *p) {
    int pointerSize = sizeof(p);

    if (pointerSize == 4) {
        Encode((int)(long long)p);
    } else if (pointerSize == 8) {
        Encode((long long)p);
    } else {
        assert(false);
    }
}

void InstructionsClass::Finish() {
    Encode(POP_EBP);
    Encode(NEAR_RET);

    cout << "Finished creating " << mCurrent << " bytes of machine code" << endl;
}

void InstructionsClass::Execute() {
    cout << "About to Execute the machine code...\n";

    // http://stackoverflow.com/questions/28015876/what-do-i-have-to-do-to-execute-code-in-data-areas-segment-protection
    //The mmap solution is good, but it doesn't provide us any safety; our mmaped region of code is readable, writable, and executable.
    // It would be better to only allow the memory to be writable while we're putting our code in place, then making it executable only.
    // The following code does just that:
//    const size_t len = sizeof(mCode);
//
//    /* mmap a region for our code */
////    void *p = mmap(NULL, len, PROT_READ|PROT_WRITE|PROT_EXEC,
////                   MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
//    void *p = mmap(NULL, len, PROT_READ|PROT_WRITE,  /* No PROT_EXEC */
//                   MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
//    if (p == MAP_FAILED) {
//        cerr << "mmap() failed\n" << endl;
//        exit(1);
//    }
//
//    /* Copy it in (still not executable) */
//    memcpy(p, mCode, len);
//
//    /* Now make it execute-only */
//    if (mprotect(p, len, PROT_EXEC) < 0) {
//        cerr << "mprotect failed to mark exec-only\n" << endl;
//        exit(1);
//    }
//
//    /* Go! */
//    void (*f)(void);
//    f = (void (*)(void)) p;
//    f();

//    pause();

    // Bart's Method
    void *ptr = InstructionsClass::mCode;
    void (*f)(void);
    f = (void (*)(void)) ptr;
    f(); // call the array as if it were a function
    cout << "There and back again!" << endl;
}

void InstructionsClass::PrintAllMachineCodes() {
    for (int i = 0; i < mCurrent; i++) {
        printf("HEX: %2x  Decimal: %3i\n", (int)InstructionsClass::mCode[i], (int)InstructionsClass::mCode[i]);
    }
}

void InstructionsClass::PushValue(int value) {
    Encode(IMMEDIATE_TO_EAX);
    Encode(value);
    Encode(PUSH_EAX);
}

void InstructionsClass::Call(void *function_address) {
    unsigned char *a1 = (unsigned char *)function_address;
    unsigned char *a2 = (unsigned char *)(&InstructionsClass::mCode[mCurrent + 5]);
    int offset = (int)(a1 - a2);
    Encode(CALL);
    Encode(offset);
}

// A location to store an integer that is about to be printed.
int gPrintInteger = 0; // BSFIX I might need to make this a static class member for 64 bit architectures, as I did for mCode.

// prints the integer value at location gPrintInteger
// This is called by the generated machine language code.
void HelperPrintInteger(void) {
    printf("%i ", gPrintInteger);
}

// Creates machine code that pops a value back off the stack and stores it in gPrintInteger, and prints it to the monitor.
// Then writes machine code that calls HelperPrintInteger
void InstructionsClass::PopAndWrite() {
    Encode(POP_EAX);
    Encode(EAX_TO_MEM);
    Encode(&gPrintInteger);
    Call((void *)HelperPrintInteger);
}

// returns the address corresponding to variable <index>
// in the mData array.
int *InstructionsClass::GetMem(int index) {
    if(index >= MAX_DATA) {
        cerr << "Error in GetMem. index is " << index<< ", but NUM_DATA is only " << MAX_DATA << endl;
        exit(1);
    }
    return  &(mData[index]);
}

// PushVariable takes one integer parameter - the index into mData specifying which integer should be pushed onto the system stack.
// Write machine code to move memory to the EAX register.
// Determine which machine code does that, and nickname it “MEM_TO_EAX.”
// The four bytes following are the RAM address of which integer to move.
// You can find that address by calling the helper method GetMem.
// Then write code to PUSH_EAX. In all, PushVariable should create six bytes of machine code.
void InstructionsClass::PushVariable(unsigned int index) {
    int *variableAddress = GetMem(index);
    Encode(MEM_TO_EAX);
    Encode(variableAddress);
    Encode(PUSH_EAX);
}

// PopAndStore should POP_EAX to move the integer from the top of the stack to the EAX register.
// Then EAX_TO_MEM to move it from the EAX register to the correct RAM address, as found by calling GetMem.
void InstructionsClass::PopAndStore(unsigned int index) {
    int *variableAddress = GetMem(index);
    Encode(POP_EAX);
    Encode(EAX_TO_MEM);
    Encode(variableAddress);
}

void InstructionsClass::PopPushPush() {
    Encode(POP_EAX);
    Encode(PUSH_EAX);
    Encode(PUSH_EAX);
}

void InstructionsClass::Pop() {
    Encode(POP_EAX);
}

// prints a carriage return
// This is called by the generated machine language code.
void HelperPrintEndl(void) {
    cout << endl;
}

void InstructionsClass::WriteEndl() {
    Call((void *)HelperPrintEndl);
}


void InstructionsClass::PopPopAddPush() {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(ADD_EAX_EBX1);
    Encode(ADD_EAX_EBX2);
    Encode(PUSH_EAX);
}

void InstructionsClass::PopPopSubPush() {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(SUB_EAX_EBX1);
    Encode(SUB_EAX_EBX2);
    Encode(PUSH_EAX);
}

void InstructionsClass::PopPopMulPush() {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(MUL_EAX_EBX1);
    Encode(MUL_EAX_EBX2);
    Encode(PUSH_EAX);
}

void InstructionsClass::PopPopDivPush() {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(CDQ);// Necessary to clear the D register for a 64 bit divide.
    Encode(DIV_EAX_EBX1);
    Encode(DIV_EAX_EBX2);
    Encode(PUSH_EAX);
}

void InstructionsClass::PopPopModPush() {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(CDQ);// Necessary to clear the D register for a 64 bit divide.
    Encode(DIV_EAX_EBX1);
    Encode(DIV_EAX_EBX2);
    Encode(PUSH_EDX);
}


void InstructionsClass::PopPopComparePush(unsigned char relationalOperator) {
    Encode(POP_EBX);
    Encode(POP_EAX);
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(IMMEDIATE_TO_EAX); // load A register with 1
    Encode(1);
    Encode(relationalOperator); // Possibly skip setting A register to zero, leaving it at 1.
    Encode((unsigned char)5);
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    Encode(PUSH_EAX); // push 1 or 0
}

void InstructionsClass::PopPopLessPush() {
    PopPopComparePush(JL);
}

void InstructionsClass::PopPopLessEqualPush() {
    PopPopComparePush(JLE);
}

void InstructionsClass::PopPopGreaterPush() {
    PopPopComparePush(JG);
}

void InstructionsClass::PopPopGreaterEqualPush() {
    PopPopComparePush(JGE);
}

void InstructionsClass::PopPopEqualPush() {
    PopPopComparePush(JE);
}

void InstructionsClass::PopPopNotEqualPush() {
    PopPopComparePush(JNE);
}

void InstructionsClass::PopPopAndPush() {
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    Encode(POP_EBX); // load B register with stack item 2
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(POP_EBX); // load B register with stack item 1 (does not affect flags)
    Encode(JE); // if stack item 2 is zero, jump to FALSE code
    Encode((unsigned char)11);
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(JE); // if stack item 1 is zero, jump to FALSE code
    Encode((unsigned char)7);
    // TRUE code:
    Encode(IMMEDIATE_TO_EAX); // load A register with 1
    Encode(1);
    Encode(JUMP_ALWAYS); // Jump around FALSE code
    Encode((unsigned char)5);
    // FALSE code:
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    // Save A to the stack
    Encode(PUSH_EAX); // push 1 or 0
}

void InstructionsClass::PopPopOrPush() {
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    Encode(POP_EBX); // load B register with stack item 2
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(POP_EBX); // load B register with stack item 1 (does not affect flags)
    Encode(JNE); // if stack item 2 is not zero, jump to TRUE code
    Encode((unsigned char)11);
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(JNE); // if stack item 1 is not zero, jump to TRUE code
    Encode((unsigned char)7);
    // FALSE code:
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    Encode(JUMP_ALWAYS); // Jump around TRUE code
    Encode((unsigned char)5);
    // TRUE code:
    Encode(IMMEDIATE_TO_EAX); // load A register with 1
    Encode(1);
    // Save A to the stack
    Encode(PUSH_EAX); // push 1 or 0
}

unsigned char *InstructionsClass::SkipIfZeroStack() {
    Encode(POP_EBX);
    Encode(IMMEDIATE_TO_EAX); // load A register with 0
    Encode(0);
    Encode(CMP_EAX_EBX1);
    Encode(CMP_EAX_EBX2);
    Encode(JE_FAR1); // If stack had zero, skip given number of bytes
    Encode(JE_FAR2);
    unsigned char *addressToFillInLater = GetAddress();
    Encode(0); // the exact number of bytes to skip gets set later,
				// when we know it!  Call SetOffset() to do that.
    return addressToFillInLater;
}

void InstructionsClass::SetOffset(unsigned char *codeAddress, int offset) {
    *((int *)codeAddress) = offset;
}

unsigned char *InstructionsClass::GetAddress() {
    return &(InstructionsClass::mCode[mCurrent]);
}

unsigned char *InstructionsClass::Jump() {
    Encode(JUMP_ALWAYS_FAR);
    unsigned char *addressToFillInLater = GetAddress();
    Encode(0); // the exact number of bytes to jump gets set later,
				// when we know it!  Call SetOffset() to do that.
    return addressToFillInLater;
}




