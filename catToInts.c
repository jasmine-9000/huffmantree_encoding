# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdint.h>

int main(void)
{
	int input = open("testFile.txt", O_RDONLY);
	if(input < 0)
	{
		write(2, "ASS\n", 4);
		return 1;
	}
	char buffer[100];
	int i = read(input, buffer, 100);
	for(int j = 0; j < i; j++)
	{
		printf("%02x\n", (uint8_t) buffer[j]); 
	}
	return 0;
}
