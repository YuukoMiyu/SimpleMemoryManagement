#include <stdio.h>
#include "MemoryManagement.h"

int main() {
    Initialize(300);

	unsigned char* a = xmalloc(60);
	unsigned char* b = xmalloc(125);

	unsigned char c[] = {'h', 'i', '\n', '\0'};
	writeMemory(a, c, 4);
	unsigned char* d = readMemory(a, 4);
	writeMemory(b, d, 4);

	xfree(a);
	//xfree(b);

	MemoryDump();
	Deinitialize();
    
	printf("\n");
    return 0;
}
