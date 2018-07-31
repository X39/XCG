#pragma once

#include <stdbool.h>
#include <stdlib.h>


#define T__INVALID 0
#define T__FIRST 1
#define T_TOKENIDENT 1
#define T_STATEIDENT 2
#define T_STMTSEP 3
#define T_ANYTEXT 4
#define T_ANNOTATION 5
#define T_SKIP 6
#define T_CASESENSITIVE 7
#define T_LINECOMMENTSTART 8
#define T_OR 9
#define T_CURLYO 10
#define T_CURLYC 11
#define T_ROUNDO 12
#define T_ROUNDC 13
#define T_SQUAREO 14
#define T_SQUAREC 15
#define T_TRUE 16
#define T_FALSE 17
#define T_SC 18
#define T_LT 19
#define T_GT 20
#define T_MODMAX 21
#define T_COLON 22
#define T_NUMBER 23
#define T_ALPHALOW 24
#define T_ALPHAUP 25
#define T_MINUS 26
#define T_PLUS 27
#define T_DIGIT 28
#define T_ANY 29
#define T_DOT 30
#define T_BS 31
#define T_SPACE 32
#define T__LAST 32

#define S_EBNF 33
#define S_ANNOTATION 34
#define S_ASKIP 35
#define S_ACASESENSITIVE 36
#define S_ALINECOMMENTSTART 37
#define S_TOKEN 38
#define S_TC 39
#define S_TCG 40
#define S_TC0 41
#define S_TC1 42
#define S_STATEMENT 43
#define S_EXPRESSION 44
#define S_EXPL0 45
#define S_EXPL1 46
#define S_EXPL2 47
#define S_EXPL3 48
#define S_STMNTMOD 49
#define S_SMMAX 50
#define S_TC2 51
#define S_EXPRESSION2 52

#define T_TOKENIDENT_STR "tokenident"
#define T_STATEIDENT_STR "stateident"
#define T_STMTSEP_STR "="
#define T_ANYTEXT_STR "anytext"
#define T_ANNOTATION_STR "@"
#define T_SKIP_STR "skip"
#define T_CASESENSITIVE_STR "casesensitive"
#define T_LINECOMMENTSTART_STR "linecommentstart"
#define T_OR_STR "|"
#define T_CURLYO_STR "{"
#define T_CURLYC_STR "}"
#define T_ROUNDO_STR "("
#define T_ROUNDC_STR ")"
#define T_SQUAREO_STR "["
#define T_SQUAREC_STR "]"
#define T_TRUE_STR "true"
#define T_FALSE_STR "false"
#define T_SC_STR ";"
#define T_LT_STR "<"
#define T_GT_STR ">"
#define T_MODMAX_STR "modmax"
#define T_COLON_STR ":"
#define T_NUMBER_STR "number"
#define T_ALPHALOW_STR "alphalow"
#define T_ALPHAUP_STR "alphaup"
#define T_MINUS_STR "-"
#define T_PLUS_STR "+"
#define T_DIGIT_STR "digit"
#define T_ANY_STR "any"
#define T_DOT_STR "."
#define T_BS_STR "\\"
#define T_SPACE_STR "space"

#define S_EBNF_STR "EBNF"
#define S_ANNOTATION_STR "ANNOTATION"
#define S_ASKIP_STR "ASKIP"
#define S_ACASESENSITIVE_STR "ACASESENSITIVE"
#define S_ALINECOMMENTSTART_STR "ALINECOMMENTSTART"
#define S_TOKEN_STR "TOKEN"
#define S_TC_STR "TC"
#define S_TCG_STR "TCG"
#define S_TC0_STR "TC0"
#define S_TC1_STR "TC1"
#define S_STATEMENT_STR "STATEMENT"
#define S_EXPRESSION_STR "EXPRESSION"
#define S_EXPL0_STR "EXPL0"
#define S_EXPL1_STR "EXPL1"
#define S_EXPL2_STR "EXPL2"
#define S_EXPL3_STR "EXPL3"
#define S_STMNTMOD_STR "STMNTMOD"
#define S_SMMAX_STR "SMMAX"


#ifndef TOKEN_INITIALSIZE
#define TOKEN_INITIALSIZE 25
#endif // !TOKEN_INITIALSIZE

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
void token_grow(token* ptr);
void token_push(token* ptr, token* t);
void token_skip(scan* s, size_t skip);
size_t token_scan(scan* s, char expected);
char token_next_type(scan* s);
bool EBNF_START(scan *s);
void EBNF(scan *s, token* parent);
bool ANNOTATION_START(scan *s);
void ANNOTATION(scan *s, token* parent);
bool ASKIP_START(scan *s);
void ASKIP(scan *s, token* parent);
bool ACASESENSITIVE_START(scan *s);
void ACASESENSITIVE(scan *s, token* parent);
bool ALINECOMMENTSTART_START(scan *s);
void ALINECOMMENTSTART(scan *s, token* parent);
bool TOKEN_START(scan *s);
void TOKEN(scan *s, token* parent);
bool TC_START(scan *s);
void TC(scan *s, token* parent);
bool TCG_START(scan *s);
void TCG(scan *s, token* parent);
bool TC0_START(scan *s);
void TC0(scan *s, token* parent);
bool TC1_START(scan *s);
void TC1(scan *s, token* parent);
bool TC2_START(scan *s);
void TC2(scan *s, token* parent);
bool STATEMENT_START(scan *s);
void STATEMENT(scan *s, token* parent);
bool EXPRESSION_START(scan *s);
void EXPRESSION(scan *s, token* parent);
bool EXPL0_START(scan *s);
void EXPL0(scan *s, token* parent);
bool EXPL1_START(scan *s);
void EXPL1(scan *s, token* parent);
bool EXPL2_START(scan *s);
void EXPL2(scan *s, token* parent);
bool EXPL3_START(scan *s);
void EXPL3(scan *s, token* parent);
//bool STMNTMOD_START(scan *s);
//void STMNTMOD(scan *s, token* parent); 
//bool SMMAX_START(scan *s);
//bool SMMAX(scan *s, token* parent);