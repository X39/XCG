#pragma once
#include <stdbool.h>
#include <stdlib.h>

#ifndef TOKEN_INITIALSIZE
#define TOKEN_INITIALSIZE 25
#endif

#define T__INVALID 0
#define T__FIRST 1
#define T_TOKENIDENT 1
#define T_TOKENIDENT_STR "tokenident"
#define T_STATEIDENT 2
#define T_STATEIDENT_STR "stateident"
#define T_STMTSEP 3
#define T_STMTSEP_STR "stmtsep"
#define T_ANNOTATION 4
#define T_ANNOTATION_STR "annotation"
#define T_SKIP 5
#define T_SKIP_STR "skip"
#define T_CASESENSITIVE 6
#define T_CASESENSITIVE_STR "casesensitive"
#define T_LINECOMMENTSTART 7
#define T_LINECOMMENTSTART_STR "linecommentstart"
#define T_BLOCKCOMMENTSTART 8
#define T_BLOCKCOMMENTSTART_STR "blockcommentstart"
#define T_BLOCKCOMMENTEND 9
#define T_BLOCKCOMMENTEND_STR "blockcommentend"
#define T_OR 10
#define T_OR_STR "or"
#define T_CURLYO 11
#define T_CURLYO_STR "curlyo"
#define T_CURLYC 12
#define T_CURLYC_STR "curlyc"
#define T_ROUNDO 13
#define T_ROUNDO_STR "roundo"
#define T_ROUNDC 14
#define T_ROUNDC_STR "roundc"
#define T_SQUAREO 15
#define T_SQUAREO_STR "squareo"
#define T_SQUAREC 16
#define T_SQUAREC_STR "squarec"
#define T_TRUE 17
#define T_TRUE_STR "true"
#define T_FALSE 18
#define T_FALSE_STR "false"
#define T_SC 19
#define T_SC_STR "sc"
#define T_LT 20
#define T_LT_STR "lt"
#define T_GT 21
#define T_GT_STR "gt"
#define T_QUESTIONMARK 22
#define T_QUESTIONMARK_STR "questionmark"
#define T_NUMBER 23
#define T_NUMBER_STR "number"
#define T_ALPHALOW 24
#define T_ALPHALOW_STR "alphalow"
#define T_ALPHAUP 25
#define T_ALPHAUP_STR "alphaup"
#define T_MINUS 26
#define T_MINUS_STR "minus"
#define T_PLUS 27
#define T_PLUS_STR "plus"
#define T_DIGIT 28
#define T_DIGIT_STR "digit"
#define T_DOT 29
#define T_DOT_STR "dot"
#define T_BS 30
#define T_BS_STR "bs"
#define T_NOTOKEN 31
#define T_NOTOKEN_STR "notoken"
#define T_ANYTEXT 32
#define T_ANYTEXT_STR "anytext"
#define T_ANY 33
#define T_ANY_STR "any"
#define T__LAST 33
#define S_EBNF 34
#define S_EBNF_STR "EBNF"
#define S_ANNOTATION 35
#define S_ANNOTATION_STR "ANNOTATION"
#define S_ASKIP 36
#define S_ASKIP_STR "ASKIP"
#define S_ACASESENSITIVE 37
#define S_ACASESENSITIVE_STR "ACASESENSITIVE"
#define S_ALINECOMMENTSTART 38
#define S_ALINECOMMENTSTART_STR "ALINECOMMENTSTART"
#define S_BLOCKCOMMENTSTART 39
#define S_BLOCKCOMMENTSTART_STR "BLOCKCOMMENTSTART"
#define S_BLOCKCOMMENTEND 40
#define S_BLOCKCOMMENTEND_STR "BLOCKCOMMENTEND"
#define S_TOKEN 41
#define S_TOKEN_STR "TOKEN"
#define S_TOKENSTATIC 42
#define S_TOKENSTATIC_STR "TOKENSTATIC"
#define S_TOKENRUNTIME 43
#define S_TOKENRUNTIME_STR "TOKENRUNTIME"
#define S_TC 44
#define S_TC_STR "TC"
#define S_TCG 45
#define S_TCG_STR "TCG"
#define S_TC0 46
#define S_TC0_STR "TC0"
#define S_TC1 47
#define S_TC1_STR "TC1"
#define S_TC2 48
#define S_TC2_STR "TC2"
#define S_TMODE 49
#define S_TMODE_STR "TMODE"
#define S_STATEMENT 50
#define S_STATEMENT_STR "STATEMENT"
#define S_EXPRESSION 51
#define S_EXPRESSION_STR "EXPRESSION"
#define S_EXPL0 52
#define S_EXPL0_STR "EXPL0"
#define S_EXPRESSION2 53
#define S_EXPRESSION2_STR "EXPRESSION2"
#define S_EXPL1 54
#define S_EXPL1_STR "EXPL1"
#define S_EXPL2 55
#define S_EXPL2_STR "EXPL2"
#define S_EXPL3 56
#define S_EXPL3_STR "EXPL3"

typedef void(*logcallback)(const char* m, size_t l, size_t c, size_t o, char gottype);
typedef size_t(*token_scan_resolver)(struct scan*);
typedef struct scan {
	size_t line;
	size_t col;
	size_t off;
	const char* txt;
	logcallback log;
	token_scan_resolver* resolvers;
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
void token_minimize(token*);
char token_next_type(scan* s);

bool EBNF_START(scan*);
void EBNF(scan*, token*);
bool ANNOTATION_START(scan*);
void ANNOTATION(scan*, token*);
bool ASKIP_START(scan*);
void ASKIP(scan*, token*);
bool ACASESENSITIVE_START(scan*);
void ACASESENSITIVE(scan*, token*);
bool ALINECOMMENTSTART_START(scan*);
void ALINECOMMENTSTART(scan*, token*);
bool BLOCKCOMMENTSTART_START(scan*);
void BLOCKCOMMENTSTART(scan*, token*);
bool BLOCKCOMMENTEND_START(scan*);
void BLOCKCOMMENTEND(scan*, token*);
bool TOKEN_START(scan*);
void TOKEN(scan*, token*);
bool TOKENSTATIC_START(scan*);
void TOKENSTATIC(scan*, token*);
bool TOKENRUNTIME_START(scan*);
void TOKENRUNTIME(scan*, token*);
bool TC_START(scan*);
void TC(scan*, token*);
bool TCG_START(scan*);
void TCG(scan*, token*);
bool TC0_START(scan*);
void TC0(scan*, token*);
bool TC1_START(scan*);
void TC1(scan*, token*);
bool TC2_START(scan*);
void TC2(scan*, token*);
bool TMODE_START(scan*);
void TMODE(scan*, token*);
bool STATEMENT_START(scan*);
void STATEMENT(scan*, token*);
bool EXPRESSION_START(scan*);
void EXPRESSION(scan*, token*);
bool EXPL0_START(scan*);
void EXPL0(scan*, token*);
bool EXPRESSION2_START(scan*);
void EXPRESSION2(scan*, token*);
bool EXPL1_START(scan*);
void EXPL1(scan*, token*);
bool EXPL2_START(scan*);
void EXPL2(scan*, token*);
bool EXPL3_START(scan*);
void EXPL3(scan*, token*);
