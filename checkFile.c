# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <inttypes.h>
# include <ctype.h>
# include <stdint.h>

# define MAX 10000
uint8_t buffer[MAX];
void breakTime(void)
{
	printf("JOLLY RANCHERS AND SKITTLES\n");
	return;
}
int main(int argc, char **argv)
{
	int c;
	char *inputFileName = "";
	char *outputFileName = "";
	bool verboseMode = false; // this enables verbose mode.
	while((c = getopt(argc, argv, "vi:o:")) != -1)
	{
		switch(c)
		{
			case 'i':
				inputFileName = strdup(optarg);
				break;
			case 'o':
				outputFileName = strdup(optarg);
				break;
			case 'v':
				verboseMode = true;
				break;
		}
	}
	if(verboseMode)
		printf("verbose mode turned on.\n");
	int input = open(inputFileName, O_RDONLY);
	int output = open(outputFileName, O_RDONLY);
	read(input, buffer, MAX);
	breakTime();
	close(input);
	close(output);
//	free(inputFileName);
//	free(outputFileName);
}
