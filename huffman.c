# include "huffman.h"
# include "code.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <inttypes.h>
# include "stack.h"

/* treeNode's members:
 * 
 * uint8_t symbol
 * uint64_t count;
 * bool leaf;
 * treeNode *left;
 * treeNode *right;
 *
 */
treeNode *newNode(uint8_t s, bool l, uint64_t c)
{
	treeNode *n = malloc(sizeof(treeNode));
	n->symbol = s;
	n->count = c;
	n->leaf = l;
	n->left = NIL;
	n->right = NIL;
	// will not assume leftNode and rightNode pointers for now.
	return n;
}
// Dump a d
//stack *huffmanStack = newStack();
// code a = newCode();
void dumpTree(treeNode *t, int file)
{
	// my interpretation:
	// if you start at the top:
	if(t->leaf)
	{
		write(file, "L", 1);
		char c[1];
		c[0] = (char) t->symbol; 
		write(file, c, 1);	 
	}
	else // if interior node
	{ 
		
		dumpTree(t->left, file);
		dumpTree(t->right, file);
		write(file, "I", 1);
	}
	// pop() the stack.
}
// Build a tree from the saved tree.
treeNode *loadTree(uint8_t savedTree[], uint16_t treeBytes)
{
	treeNode *root;// = newNode(1,0,3);
	stack *treeNodePoints = newStack();
	for(uint16_t i = 0; i < treeBytes; i++)
	{
			// savedTree will read in the character for L if it's a leaf,
			// 					    I if it's interior.
		//bool leaf = savedTree[i++]; // postincrement; retrieve the value of i, then increment it.
		uint8_t typeOfNode = savedTree[i];
		bool leaf = (typeOfNode == 'L');
		if(leaf)
		{
			uint8_t symbol = savedTree[++i]; // will be incremented by the end of hte loop.
			uint64_t count = 1; //savedTree[i]; // will be incremented at the end of the loop.
			//printf("symbol: %d, count: %d\n", symbol, count);
			treeNode *l = newNode(symbol, leaf, count);
			// then push it onto the stack.
			push(treeNodePoints, l);
		}
		else if(typeOfNode == 'I')
		{
			// pop the 2 child nodes.
			treeNode *right = pop(treeNodePoints);
			treeNode *left = pop(treeNodePoints);
			treeNode *interior;
			interior = join(left, right);//newNode(symbol, leaf, count);
			push(treeNodePoints, interior);
		}
		else
		{
			printf("ERROR!\n");
			printf("SYMBOL READ: 0x%02x\n", savedTree[i]);
		}
	}
	root = pop(treeNodePoints);
	//push(a, savedTree[0]);
	if(empty(treeNodePoints)) // error checking.
	{
		delStack(treeNodePoints);
	}
	else
	{
		// throws a warning if the stack isn't empty. this means you missed some nodes.
		printf("WARNING: STACK NOT EMPTY BEFORE DELETING AT LOADTREE().\n");
		delStack(treeNodePoints);
	}
	return root;
}
// step through a tree following the code
int32_t stepTree(treeNode *root, treeNode **t, uint32_t code)
{
	// pass in 1 bit at a time. check if it's 1 or 0.
	// 1 -> right
	// 0 -> left;
	if(code)
	{
		(*t) = (*t)->right;
	}
	else
	{
		(*t) = (*t)->left;
	}
	if(*t == NIL) // error checkign.
	{
		//printf("ERROR! HIT A NULL NODE.\n");
		(*t) = root; 
	}
	if((*t)->leaf) // if it's a leaf
	{
		int32_t num = (*t)->symbol;
		(*t) = root; // surface if it's a leaf.
		return num;
	}
	else // else iterate again.
	{
		return -1;
	}

	/*
	printf("Root: %02x, T: %02x, code: %04x  ", root->symbol, t[0]->symbol, code);
	//bool cont = true;
	for(int32_t i = 31; i >= 0; i--)
	{
		uint32_t x = (code & (1 << i)) >> i;
		printf("%d", x);
	}
	printf("\n");
	return -1;
	
	if(root != NIL)
	{
		if(!root->leaf)
		{
			return stepTree(root->left, t, code);
		}
		else
		{
			return root->symbol;
		}
	}
	else
	{
		return -1;
	}
	*/
}
// Parse a Huffman tree to build codes.
void buildCode(treeNode *t, code s, code table[256])
{
	if(t->leaf)
	{
		for(int i = 0; i < 255; i++)
		{
			uint32_t k;
			table[i] = s;
			popCode(&s, &k);
		}
	}
	return;	
}

void *delTree(treeNode *t)
{
	// postoorder traversal deletion.
	if(t->left != NIL)
	{
		delTree(t->left);
	}	
	if(t->right != NIL)
	{
		delTree(t->right);
	}
	delNode(t);
	return NIL;
}

treeNode *join(treeNode *l, treeNode *r)
{
	uint32_t count = 0;
	if(l != NIL) // error checking
	{
		count += l->count;
	}
	if(r != NIL) // error checking.
	{
		count += r->count;
	}
	bool leaf = false; // is not a leaf.
	uint8_t symbol = 0; // has no symbol.
	treeNode *j = newNode(symbol, leaf, count); // has no symbol, has children, is an addition of frequencies.
	// make the left and right pointers equal to the arguments.
	j->left = l;
	j->right = r;
	return j;
}
