#include "Block.h"

void SetBlockSize(unsigned char* blockPtr, unsigned char size) {
    *blockPtr = size << 1;
}

unsigned char GetBlockSize(unsigned char* blockPtr) { return *blockPtr >> 1; }

unsigned char IsBlockSigned(unsigned char* blockPtr) { return *blockPtr & 1; }

void UnsignBlock(unsigned char* blockPtr) { *blockPtr &= 254; }

void SignBlock(unsigned char* blockPtr) { *blockPtr |= 1; }

unsigned char* GetNextBlockPtr(unsigned char* blockPtr) {
    return blockPtr + GetBlockSize(blockPtr) + 1;
}
