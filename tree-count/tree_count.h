#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct tnode { /* the tree node: */
	char *word; /* points to the text */
	int count; /* number of occurrences */
	struct tnode *left; /* left child */
	struct tnode *right; /* right child */
};

struct htnode {// node of a wordhead tree
	char *head; // the string that make the wordhead
	int count; 
	struct tnode *headroot; // the root of a tree of only the words starting with this head
	struct htnode *left;
	struct htnode *right;
};