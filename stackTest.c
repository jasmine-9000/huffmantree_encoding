# include "stack.h"
# include <stdio.h>
# include "huffman.h"
int main(void)
{
	stack *ass = newStack();
	treeNode *asshole = newNode(10,1,10);
	push(ass, asshole);
	asshole = newNode(20,0,20);
	push(ass, asshole);
	treeNode *shit;
	shit = pop(ass);
	printf("symbol: %d\n", shit->symbol);
	free(shit);
	shit = pop(ass);
	printf("symbol: %d\n", shit->symbol);
	free(shit);
	//push(ass, 10);
	//printf("%d\n", pop(ass));
	delStack(ass);	
	return 0;
}
