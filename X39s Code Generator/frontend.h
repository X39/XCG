#pragma once
typedef struct frontend
{
	const char* header_head;
	const char* header_enumeration_tokens_start;
	//Will receive the %u param of the last token too.
	const char* header_enumeration_tokens_end;
	const char* header_enumeration_element_tokens_start;
	const char* header_enumeration_element_tokens_end;

	//Will receive the %u param of the first statement too.
	const char* header_enumeration_statements_start;
	//Will receive the %u param of the last statement too.
	const char* header_enumeration_statements_end;

	const char* header_logcallback;
	const char* header_scan_struct;
	const char* header_token_struct;
	const char* header_methods;
	//Will receive the %.*s param containing the actual name.
	const char* header_mhead_statement_start;
	//Will receive the %.*s param containing the actual name.
	const char* header_mhead_statement;
} frontend;

frontend frontend_get_default()
{
	frontend f;
	f.header_head = "#pragma once\n#include <stdbool.h>\n#include<stdlib.h>\n"
		"#ifndef TOKEN_INITIALSIZE\n#define TOKEN_INITIALSIZE 25\n#endif\n";
	f.header_enumeration_tokens_start = "#define T__INVALID 0\n#define T__FIRST 1\n";
	f.header_enumeration_tokens_end = "#define T__LAST %u\n";
	f.header_enumeration_element_tokens_start = "#define T_";
	f.header_enumeration_element_tokens_end = "";
	f.header_enumeration_statements_start = "";
	f.header_enumeration_statements_end = "";
	f.header_logcallback = "typedef void(*logcallback)(const char* m, size_t l, size_t c, size_t o, char gottype);\n";
	f.header_scan_struct = "typedef struct {" "\n"
		"	size_t line;" "\n"
		"	size_t col;" "\n"
		"	size_t off;" "\n"
		"	const char* txt;" "\n"
		"	logcallback log;" "\n"
		"} scan;" "\n";
	f.header_token_struct = "typedef struct token {" "\n"
		"	size_t line;" "\n"
		"	size_t column;" "\n"
		"	size_t offset;" "\n"
		"	size_t length;" "\n"
		"	char type;" "\n"
		"	size_t size;" "\n"
		"	size_t top;" "\n"
		"	struct token** children;" "\n"
		"} token;" "\n";
	f.header_methods = "bool str_equals(const char* strin, const char* otherstr);" "\n"
		"token* token_gen(scan *s, char type);" "\n"
		"void token_del(token* ptr);" "\n"
		"void token_grow(token* ptr);" "\n"
		"void token_push(token* ptr, token* t);" "\n"
		"void token_skip(scan* s, size_t skip);" "\n"
		"size_t token_scan(scan* s, char expected);" "\n"
		"void token_minimize(token*);" "\n"
		"char token_next_type(scan* s);" "\n";
	f.header_mhead_statement_start = "bool %.*s_START(scan*);\n";
	f.header_mhead_statement = "void %.*s(scan*, token*);\n";
	return f;
}