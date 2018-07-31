#include "astnode.h"


#include <malloc.h>
#include <string.h>
//Creates new astnode (technically just calls malloc and memsets to 0)
PASTNODE astnode_create(void)
{
	PASTNODE node = malloc(sizeof(ASTNODE));
	memset(node, 0, sizeof(ASTNODE));
	return node;
}

//Clears the astnodes children and marks it as empty.
//If no children are inside the provided node, nothing will be done.
void astnode_clear(PASTNODE node)
{
	if (node->children != 0)
	{
		for (unsigned int i = 0; i < node->children_length; i++)
		{
			astnode_clear(node->children + i);
		}
		free(node->children);
		node->children = 0;
		node->children_length = 0;
		node->children_size = 0;
	}
}

//Creates a new astnode and outputs it into second arg.
//may fail if out of ram, will then return false.
bool astnode_push_new(PASTNODE node, PASTNODE * out)
{
	ASTNODE newnode;
	memset(&newnode, 0, sizeof(ASTNODE));
	if (!astnode_push(node, newnode))
	{
		return false;
	}
	*out = node->children + node->children_length - 1;
	return true;
}
//Appends the provided second-arg astnode to the first-arg astnode ptr.
bool astnode_push(PASTNODE node, ASTNODE data)
{
	if (!astnode_ensure(node, node->children_length + 1))
	{
		return false;
	}
	node->children[node->children_length++] = data;
	return true;
}
//Ensures that the provided astnode has at least X slots for its children.
//if it does not, will grow according to newsize = cursize * 2
bool astnode_ensure(PASTNODE node, unsigned int size)
{
	PASTNODE ptr;
	if (node->children == 0)
	{
		node->children = malloc(sizeof(ASTNODE) * ASTNODE_INITIALSIZE);
		node->children_size = ASTNODE_INITIALSIZE;
		return node->children != 0;
	}
	else if (node->children_size <= size)
	{
		node->children_size *= 2;
		ptr = realloc(node->children, sizeof(ASTNODE) * node->children_size);
		if (ptr == 0)
			return false;
		node->children = ptr;
		return true;
	}
	return true;
}