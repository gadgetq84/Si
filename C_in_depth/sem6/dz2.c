#include <stdio.h>

typedef struct tree
{
	int key;
	struct tree *left, *right, *parent;
} tree;

int calc_sum(tree *);
int main(int argc, char ** argv)
{

	tree t[10]={0};
	
	t[0].left = t+1;
	t[0].right = t+2;
	t[0].key = 10;
	
	t[1].left = t+3;
	t[1].right = t+4;
	t[1].key = 5;
	t[1].parent = t+0;
	
	t[2].left = t+5;
	t[2].right = t+6;
	t[2].key = 15;
	t[2].parent = t+0;
	
	t[3].left = t+7;
	t[3].parent = t+1;
	t[3].key = 3;
	
	t[4].left = t+8;
	t[4].parent = t+1;
	t[4].key = 7;
	
	t[5].key = 13;
	t[5].parent = t+2;
	
	t[6].key = 18;
	t[6].parent = t+2;
	
	t[7].key = 1;
	t[7].parent = t+3;
	
	t[8].key = 6;
	t[8].parent = t+4;
	int sum = 0;
	sum = calc_sum(t);
	printf("%d\n", sum);
}
int calc_sum(tree * root)
{	
	int suml,sumr;
	//printf("%d+%d =",sum,root->key);
	//sum+=root->key;
	//printf("%d\n",sum);

if(root!=NULL)
	{
		if(root->left)//! NULL
		{
			suml=calc_sum(root->left);
		}else
		{
			suml=0;
		}
		if(root->right )//! NULL
		{
			sumr=calc_sum(root->right);
		}else
		{
			sumr = 0;
		}
	return suml+sumr +root->key;
	}
	return 0;
}

