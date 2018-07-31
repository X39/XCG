#pragma once
#include <stdbool.h>
#include <stdlib.h>

#ifndef TOKEN_INITIALSIZE
#define TOKEN_INITIALSIZE 25
#endif

#define T__INVALID 0
#define T__FIRST 1
#define T_ANY 1
#define T_ANY_STR "any"
#define T_DOT 2
#define T_DOT_STR "."
#define T_TOKENIDENT 3
#define T_TOKENIDENT_STR "tokenident"
#define T_STMTSEP 4
#define T_STMTSEP_STR "="
#define T_ANYTEXT 5
#define T_ANYTEXT_STR "anytext"
#define T_SPACE 6
#define T_SPACE_STR "space"
#define T_STATEIDENT 7
#define T_STATEIDENT_STR "stateident"
#define T_ANNOTATION 8
#define T_ANNOTATION_STR "@"
#define T_SKIP 9
#define T_SKIP_STR "skip"
#define T_CASESENSITIVE 10
#define T_CASESENSITIVE_STR "casesensitive"
#define T_LINECOMMENTSTART 11
#define T_LINECOMMENTSTART_STR "linecommentstart"
#define T_OR 12
#define T_OR_STR "|"
#define T_CURLYO 13
#define T_CURLYO_STR "{"
#define T_CURLYC 14
#define T_CURLYC_STR "}"
#define T_ROUNDO 15
#define T_ROUNDO_STR "("
#define T_ROUNDC 16
#define T_ROUNDC_STR ")"
#define T_SQUAREO 17
#define T_SQUAREO_STR "["
#define T_SQUAREC 18
#define T_SQUAREC_STR "]"
#define T_TRUE 19
#define T_TRUE_STR "true"
#define T_FALSE 20
#define T_FALSE_STR "false"
#define T_SC 21
#define T_SC_STR ";"
#define T_LT 22
#define T_LT_STR "<"
#define T_GT 23
#define T_GT_STR ">"
#define T_MODMAX 24
#define T_MODMAX_STR "modmax"
#define T_COLON 25
#define T_COLON_STR ":"
#define T_NUMBER 26
#define T_NUMBER_STR "number"
#define T_ALPHALOW 27
#define T_ALPHALOW_STR "alphalow"
#define T_ALPHAUP 28
#define T_ALPHAUP_STR "alphaup"
#define T_MINUS 29
#define T_MINUS_STR "-"
#define T_PLUS 30
#define T_PLUS_STR "+"
#define T_DIGIT 31
#define T_DIGIT_STR "digit"
#define T_BS 32
#define T_BS_STR "\\"
#define T__LAST 32
#define S_EBNF 33
#define S_EBNF_STR "EBNF"
#define S_TC 34
#define S_TC_STR "TC"
#define S_ANNOTATION 35
#define S_ANNOTATION_STR "ANNOTATION"
#define S_ASKIP 36
#define S_ASKIP_STR "ASKIP"
#define S_ACASESENSITIVE 37
#define S_ACASESENSITIVE_STR "ACASESENSITIVE"
#define S_ALINECOMMENTSTART 38
#define S_ALINECOMMENTSTART_STR "ALINECOMMENTSTART"
#define S_TOKEN 39
#define S_TOKEN_STR "TOKEN"
#define S_TCG 40
#define S_TCG_STR "TCG"
#define S_TC0 41
#define S_TC0_STR "TC0"
#define S_TC1 42
#define S_TC1_STR "TC1"
#define S_TC2 43
#define S_TC2_STR "TC2"
#define S_STATEMENT 44
#define S_STATEMENT_STR "STATEMENT"
#define S_EXPRESSION 45
#define S_EXPRESSION_STR "EXPRESSION"
#define S_EXPL0 46
#define S_EXPL0_STR "EXPL0"
#define S_EXPL1 47
#define S_EXPL1_STR "EXPL1"
#define S_EXPL2 48
#define S_EXPL2_STR "EXPL2"
#define S_EXPL3 49
#define S_EXPL3_STR "EXPL3"
#define S_STMNTMOD 50
#define S_STMNTMOD_STR "STMNTMOD"
#define S_SMMAX 51
#define S_SMMAX_STR "SMMAX"

typedef void(*logcallback)(const char* m, size_t l, size_t c, size_t o, char gottype);
typedef struct {
	size_t line;
	size_t col;
	size_t off;
	const char* txt;
	logcallback log;
} scan;
typedef struct token {
	size_t line;
	size_t column;
	size_t offset;
	size_t length;
	char type;
	size_t size;
	size_t top;
	struct token** children;
} token;
bool str_equals(const char* strin, const char* otherstr);
token* token_gen(scan *s, char type);
void token_del(token* ptr);
bool token_grow(token* ptr);
bool token_push(token* ptr, token* t);
void token_skip(scan* s, size_t skip);
size_t token_scan(scan* s, char expected);
void token_minimize(token*);
char token_next_type(scan* s);

bool EBNF_START(scan*);
bool EBNF(scan*, token*);
bool TC_START(scan*);
bool TC(scan*, token*);
bool ANNOTATION_START(scan*);
bool ANNOTATION(scan*, token*);
bool ASKIP_START(scan*);
bool ASKIP(scan*, token*);
bool ACASESENSITIVE_START(scan*);
bool ACASESENSITIVE(scan*, token*);
bool ALINECOMMENTSTART_START(scan*);
bool ALINECOMMENTSTART(scan*, token*);
bool TOKEN_START(scan*);
bool TOKEN(scan*, token*);
bool TCG_START(scan*);
bool TCG(scan*, token*);
bool TC0_START(scan*);
bool TC0(scan*, token*);
bool TC1_START(scan*);
bool TC1(scan*, token*);
bool TC2_START(scan*);
bool TC2(scan*, token*);
bool STATEMENT_START(scan*);
bool STATEMENT(scan*, token*);
bool EXPRESSION_START(scan*);
bool EXPRESSION(scan*, token*);
bool EXPL0_START(scan*);
bool EXPL0(scan*, token*);
bool EXPL1_START(scan*);
bool EXPL1(scan*, token*);
bool EXPL2_START(scan*);
bool EXPL2(scan*, token*);
bool EXPL3_START(scan*);
bool EXPL3(scan*, token*);
bool STMNTMOD_START(scan*);
bool STMNTMOD(scan*, token*);
bool SMMAX_START(scan*);
bool SMMAX(scan*, token*);
