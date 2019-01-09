#pragma once
#include <stdbool.h>

#ifndef ASTNODE_INITIALSIZE
#define ASTNODE_INITIALSIZE 25
#endif // !ASTNODE_INITIALSIZE


typedef struct astnode {
	//Contains the line this astnode refers to.
	unsigned int line;
	//Contains the column this astnode refers to.
	unsigned int col;
	//Contains the length of the matched location.
	unsigned int length;
	//Contains a reference (not a copy!) into the string parsed.
	const char* stroffref;
	//Contains a number refering to the specific node-type. Parser Specific!
	unsigned short type;
	//Contains child nodes, may be NULL
	struct astnode* children;
	unsigned int children_length;
	unsigned int children_size;
} ASTNODE;
typedef ASTNODE* PASTNODE;

//Creates new astnode (technically just calls malloc and memsets to 0)
PASTNODE astnode_create(void);
//Clears the astnodes children and marks it as empty.
//If no children are inside the provided node, nothing will be done.
void astnode_clear(PASTNODE);
//Appends the provided second-arg astnode to the first-arg astnode ptr.
//may fail if out of ram, will then return false.
bool astnode_push(PASTNODE, ASTNODE);
//Creates a new astnode and outputs it into second arg.
//may fail if out of ram, will then return false.
bool astnode_push_new(PASTNODE, PASTNODE*);
//Ensures that the provided astnode has at least X slots for its children.
//if it does not, will grow according to newsize = cursize * 2
//may fail if out of ram, will then return false.
bool astnode_ensure(PASTNODE, unsigned int);