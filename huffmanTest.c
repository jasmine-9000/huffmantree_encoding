# include "huffman.h"
# include <inttypes.h>
# include <stdio.h>
# include "code.h"
int main(void)
{
	treeNode *root = newNode (64,1,64);
	root->left = newNode(16,1,32);
	root->right = newNode(32,0,32);
	//root->left->left = newNode(8,0,8);
	//root->left->right = newNode(4,0,4);
	printf("original root:\n frequency: %" PRIu64 "\n symbol: %d\n", root->count, root->symbol);
	treeNode *temp = root;
	root = join(root->left, root->right);
	free(temp);
	printf("new root:\nfrequency: %" PRIu64 "\n symbol: %d\n", root->count, root->symbol);
	delTree(root);
	return 0;
}
