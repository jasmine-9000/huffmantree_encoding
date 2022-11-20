//# include "encode.h"
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <stdint.h>
// just a test.
int main(void)
{
	int output = open("testFile.txt", O_WRONLY | O_APPEND | O_CREAT | O_EXCL);
	if (output < 0) {
		write(2, "ASS\n", 4);
		return 1;
	}
	char a[4];
	a[0] = (char) 0xde;
	a[1] = (char) 0xad;
	a[2] = (char) 0xd0;
	a[3] = (char) 0x0d;
	write(output, a, 4);
	char b[16];
	//uint64_t x = 0x0123456789ABCDEF;
	uint64_t x = 0xFEDCBA9876543210;
	for(int i = 0; i < 16; i++)
	{
		b[i] = (char) (x & 0xF);	
		x = x >> 4;
	}
	write(output, b, 16);
	//close(output);
	return 0;
}
