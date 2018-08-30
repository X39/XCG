#pragma once
#include "Parser.h"
#include <stdio.h>
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
	char* blockcommentstart;
	char* blockcommentend;
	const char* origtext;
	bool casesensitive;
	const char* fname;
	bool helper_is_first_after_EXP_start;
} generator;
typedef generator* PGENERATOR;

typedef struct gen_stmnt_helper {
	struct gen_stmnt_helper** helpers;
	size_t helpers_top;
	size_t helpers_size;
	token** tokens;
	size_t tokens_top;
	size_t tokens_size;
	token* thistoken;
} gen_stmnt_helper;
typedef gen_stmnt_helper* pgen_stmnt_helper;
pgen_stmnt_helper gen_stmnt_helper_create(void);
void gen_stmnt_helper_push_token(pgen_stmnt_helper, token*);
void gen_stmnt_helper_push_helper(pgen_stmnt_helper, pgen_stmnt_helper);
void gen_stmnt_helper_destroy(pgen_stmnt_helper);

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
token* generator_handle_statement_find_statement(PGENERATOR, const char*, size_t);
token* generator_handle_statement_find_token(PGENERATOR, const char*, size_t);
void generator_handle_statement(PGENERATOR, token*);
void generator_validate_token_tree(PGENERATOR, token*, bool *);
void generator_validate_token_tree_inner(PGENERATOR, token*, bool *);
void generate(PGENERATOR);