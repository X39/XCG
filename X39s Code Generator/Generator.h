#pragma once
#include <stdio.h>
#include "Parser.h"
#include <stdbool.h>

typedef struct generator_token {
	char* name;
	size_t length;
} generator_token;

typedef struct generator
{
	FILE* code;
	FILE* header;
	token* root;
	unsigned short depth;
	char* skip_characters;
	char* linecommentstart;
	const char* origtext;
	bool casesensitive;
	const char* fname;
} generator;
typedef generator* PGENERATOR;

bool str_partial_equals(const char*, const char*, size_t);
PGENERATOR generator_create(FILE*, FILE*, const char*, token*, const char*);
void generator_destroy(PGENERATOR);
void generator_write_skip_condition(PGENERATOR);
char generator_get_escaped_char(char);
void generator_handle_annotation(PGENERATOR, token*);
void generator_create_macro(PGENERATOR, token*);
void generator_write_token_skip_method(PGENERATOR);
void generator_handle_token_recursive(PGENERATOR, token*);
void generator_handle_token(PGENERATOR, token*);
void generator_handle_statement_START(PGENERATOR, token*);
token* generator_handle_statement_EXEC_find_start(token*);
void generator_handle_statement_EXEC(PGENERATOR, token*);
token* generator_handle_statement_find_statement(PGENERATOR, const char*, size_t);
void generator_handle_statement(PGENERATOR, token*);
void generate(PGENERATOR);