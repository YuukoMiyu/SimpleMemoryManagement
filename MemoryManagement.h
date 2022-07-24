#ifndef	MEMORY_MANGEMENT_HEADER
#define MEMORY_MANGEMENT_HEADER

void Initialize(int dataHeight);
void Deinitialize();
unsigned char* xmalloc(unsigned char size);
void xfree(unsigned char* ptr);
unsigned char* readMemory(unsigned char* ptr, unsigned char size);
void writeMemory(unsigned char* ptr, unsigned char* buf, unsigned char size);
void MemoryDump();

#endif
