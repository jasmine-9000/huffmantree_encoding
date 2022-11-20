# include "queue.h"
# include <stdio.h>

int main(void)
{
	queue *ass = newQueue(50);
	treeNode shit;
	shit.leaf = 1;
	shit.count = 50;
	shit.symbol = (uint8_t) '0';
	
	if(enqueue(ass, shit))
	{
		printf("SUCCESS\n");
	}
	item a;
	if(dequeue(ass, &a))
	{
		printf("%d\n", a.leaf);
	}
	
	return 0;
}
