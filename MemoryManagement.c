#include "MemoryManagement.h"
#include "Block.h"
#include <stdio.h>
#include <stdlib.h>

unsigned char* basePtr;
unsigned char* limitPtr;

void Initialize(int dataHeight) {
    if (dataHeight < 0) {
        return;
    }

    basePtr = (unsigned char*)calloc(dataHeight, 1);
    limitPtr = basePtr + dataHeight;

    unsigned char* scanPtr = basePtr;
    int dataLeft = dataHeight;
    while (scanPtr < limitPtr) {
        unsigned char size = (dataLeft < 128) ? dataLeft : 128;
        SetBlockSize(scanPtr, size - 1);
        dataLeft -= size;
        scanPtr = GetNextBlockPtr(scanPtr);
    }
}

void Deinitialize() {
    limitPtr = basePtr;
    free(limitPtr);
}

unsigned char* GetCurrentBlockPtr(unsigned char* ptr) {
    if (ptr < basePtr || ptr >= limitPtr || ptr == NULL) {
        return NULL;
    }

    unsigned char* scanPtr = basePtr;
    while (scanPtr < limitPtr) {
        unsigned char* nextPtr = GetNextBlockPtr(scanPtr);
        if (nextPtr <= ptr) {
            scanPtr = nextPtr;
            continue;
        }
        return scanPtr;
    }

    return NULL;
}

unsigned char* xmalloc(unsigned char size) {
    if (size > 127) {
        return NULL;
    }

    unsigned char* scanPtr = basePtr;
    unsigned char* retrievePtr = basePtr;
    unsigned char total = 0;
    while (scanPtr < limitPtr) {
        if (IsBlockSigned(scanPtr)) {
            total = 0;
            scanPtr = GetNextBlockPtr(scanPtr);
            retrievePtr = scanPtr;
            continue;
        }

        total += GetBlockSize(scanPtr) + 1;
        if (total <= size) {
            scanPtr = GetNextBlockPtr(scanPtr);
            continue;
        }

        SetBlockSize(retrievePtr, size);
        SignBlock(retrievePtr);
        unsigned char remain = total - size - 1;
        if (remain > 0) {
            SetBlockSize(GetNextBlockPtr(retrievePtr), remain - 1);
        }
        return retrievePtr + 1;
    }

    return NULL;
}

void xfree(unsigned char* ptr) {
    unsigned char* blockPtr = GetCurrentBlockPtr(ptr);
    if (blockPtr != NULL) {
        UnsignBlock(blockPtr);
    }
}

unsigned char* readMemory(unsigned char* ptr, unsigned char size) {
    if (size > 127) {
        return NULL;
    }

    unsigned char* blockPtr = GetCurrentBlockPtr(ptr);
    unsigned char* nextBlockPtr = GetNextBlockPtr(blockPtr);
    size = (size < nextBlockPtr - ptr) ? size : nextBlockPtr - ptr;

    unsigned char* arr = (unsigned char*)malloc(sizeof(unsigned char) * size);
    for (int i = 0; i < size; i++) {
        *(arr + i) = *(ptr + i);
    }
    return arr;
}

void writeMemory(unsigned char* ptr, unsigned char* buf, unsigned char size) {
    if (size > 127) {
        return;
    }

    unsigned char* blockPtr = GetCurrentBlockPtr(ptr);
    unsigned char* nextBlockPtr = GetNextBlockPtr(blockPtr);
    size = (size < nextBlockPtr - ptr) ? size : nextBlockPtr - ptr;

    for (int i = 0; i < size; i++) {
        *(ptr + i) = *(buf + i);
    }
}

void MemoryDump() {
    printf("\n================ MEMORY DUMP ==================");

    int dataHeight = limitPtr - basePtr;
    unsigned char size = 0;
    unsigned char sign = 0;
    unsigned char usage = 0;

    for (int i = 0; i < dataHeight; i++, size--) {
        unsigned char* scanPtr = basePtr + i;

        if (size == 0) {
            size = GetBlockSize(scanPtr) + 1;
            sign = IsBlockSigned(scanPtr);
            if (sign) {
                usage += size + 1;
            }
        }

        if (i % 8 == 0) {
            printf("\n%p      ", scanPtr);
        }

        if (i % 4 == 0) {
            printf("  ");
        }

        if (sign) {
            printf("\033[0;31m%02x \033[0m", *(scanPtr));
        } else {
            printf("\033[0;32m%02x \033[0m", *(scanPtr));
        }
    }

    printf("\n\n");
    printf("Usage %i/%i", usage, dataHeight);
}
