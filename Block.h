#ifndef BLOCK_HEADER
#define BLOCK_HEADER

void SetBlockSize(unsigned char* blockPtr, unsigned char size);
unsigned char GetBlockSize(unsigned char* blockPtr);
unsigned char IsBlockSigned(unsigned char* blockPtr);
void UnsignBlock(unsigned char* blockPtr);
void SignBlock(unsigned char* blockPtr);
unsigned char* GetNextBlockPtr(unsigned char* blockPtr);

#endif
