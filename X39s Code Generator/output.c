#include "output.h"
#include <malloc.h>

bool str_equals(const char* strin, const char* otherstr) {
	int i;
	for (i = 0; strin[i] != '\0' && otherstr[i] != '\0' && strin[i] == otherstr[i]; i++);
	return otherstr[i] == '\0';
}
token* token_gen(scan *s, char type) {
	token* ptr = malloc(sizeof(token));
	ptr->size = TOKEN_INITIALSIZE;
	ptr->children = malloc(sizeof(token*) * ptr->size);
	ptr->top = 0;
	ptr->type = type;
	ptr->line = s->line;
	ptr->column = s->col;
	ptr->offset = s->off;
	return ptr;
}
void token_del(token* ptr) {
	int i;
	for (i = 0; i < ptr->top; i++) { token_del(ptr->children[i]); }
	free(ptr->children);
	free(ptr);
}
void token_grow(token* ptr) {
	ptr->size = ptr->size * 2;
	ptr->children = realloc(ptr->children, sizeof(token*) * ptr->size);
}
void token_push(token* ptr, token* t) {
	if (ptr->top == ptr->size) { token_grow(ptr); }
	ptr->children[ptr->top] = t;
	ptr->top++;
}
void token_minimize(token* root) {
	token* tmp;
	int i;
	for (i = 0; i < root->top; i++) {
		while (root->children[i]->top == 1) {
			tmp = root->children[i];
			root->children[i] = tmp->children[0];
			tmp->top = 0;
			token_del(tmp);
		}
	}
	for (i = 0; i < root->top; i++) {
		token_minimize(root->children[i]);
	}
}
void token_skip(scan* s, size_t skip) {
	bool commentmode = false;
	s->off += skip;
	s->col += skip;
	while (s->txt[s->off] != '\0') {
		if (commentmode) {
			s->off++;
			s->col++;
			if (s->txt[s->off] == '\n') {
				commentmode = false;
				s->line++;
				s->col = 0;
			}
			continue;
		}
		switch (s->txt[s->off]) {
			case ' ': s->col++; s->off++; break;
			case '\r': s->col++; s->off++; break;
			case '\n': s->line++; s->col = 0; s->off++; break;
			case '\t': s->col++; s->off++; break;
			default: return;
		}
	}
}
size_t token_scan(scan* s, char expected) {
	int i = 0;
	switch(expected) {
		case T_ANY:
		{
			i += (s->txt[s->off] != ' ' && s->txt[s->off] != '\r' && s->txt[s->off] != '\n' && s->txt[s->off] != '\t') ? 1 : 0;
			return i;
		}
		case T_DOT: return s->txt[s->off] == '.' ? 1 : 0;
		case T_TOKENIDENT:
		{
			if(!((s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z'))) return 0;
			i++;
			if(!((s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			i++;
			for(; (s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++);
			return i;
		}
		case T_STMTSEP: return s->txt[s->off] == '=' ? 1 : 0;
		case T_ANYTEXT:
		{
			if(!((s->txt[s->off] != ' ' && s->txt[s->off] != '\r' && s->txt[s->off] != '\n' && s->txt[s->off] != '\t') ? 1 : 0)) return 0;
			i++;
			for(; (s->txt[s->off] != ' ' && s->txt[s->off] != '\r' && s->txt[s->off] != '\n' && s->txt[s->off] != '\t') ? 1 : 0; i++);
			return i;
		}
		case T_SPACE: return s->txt[s->off] == ' ' ? 1 : 0;
		case T_STATEIDENT:
		{
			if(!((s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z'))) return 0;
			i++;
			if(!((s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			i++;
			for(; (s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++);
			return i;
		}
		case T_ANNOTATION: return s->txt[s->off] == '@' ? 1 : 0;
		case T_SKIP:
		{
			i += str_equals(s->txt + s->off, "SKIP") ? 4 : 0;
			return i;
		}
		case T_CASESENSITIVE:
		{
			i += str_equals(s->txt + s->off, "CASESENSITIVE") ? 13 : 0;
			return i;
		}
		case T_LINECOMMENTSTART:
		{
			i += str_equals(s->txt + s->off, "LINECOMMENTSTART") ? 16 : 0;
			return i;
		}
		case T_OR: return s->txt[s->off] == '|' ? 1 : 0;
		case T_CURLYO: return s->txt[s->off] == '{' ? 1 : 0;
		case T_CURLYC: return s->txt[s->off] == '}' ? 1 : 0;
		case T_ROUNDO: return s->txt[s->off] == '(' ? 1 : 0;
		case T_ROUNDC: return s->txt[s->off] == ')' ? 1 : 0;
		case T_SQUAREO: return s->txt[s->off] == '[' ? 1 : 0;
		case T_SQUAREC: return s->txt[s->off] == ']' ? 1 : 0;
		case T_TRUE:
		{
			i += str_equals(s->txt + s->off, "true") ? 4 : 0;
			return i;
		}
		case T_FALSE:
		{
			i += str_equals(s->txt + s->off, "false") ? 5 : 0;
			return i;
		}
		case T_SC: return s->txt[s->off] == ';' ? 1 : 0;
		case T_LT: return s->txt[s->off] == '<' ? 1 : 0;
		case T_GT: return s->txt[s->off] == '>' ? 1 : 0;
		case T_MODMAX:
		{
			i += str_equals(s->txt + s->off, "max") ? 3 : 0;
			return i;
		}
		case T_COLON: return s->txt[s->off] == ':' ? 1 : 0;
		case T_NUMBER:
		{
			if(!((s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			i++;
			for(; (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++);
			return i;
		}
		case T_ALPHALOW:
		{
			if(!((s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z'))) return 0;
			i++;
			return i;
		}
		case T_ALPHAUP:
		{
			if(!((s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z'))) return 0;
			i++;
			return i;
		}
		case T_MINUS: return s->txt[s->off] == '-' ? 1 : 0;
		case T_PLUS: return s->txt[s->off] == '+' ? 1 : 0;
		case T_DIGIT:
		{
			if(!((s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			i++;
			return i;
		}
		case T_BS: return s->txt[s->off] == '\\' ? 1 : 0;
	}
}
bool EBNF_START(scan*) { return (token_scan(s, T_ANNOTATION)); }
bool EBNF(scan*, token*) {
	token* thistoken = token_gen(s, S_EBNF);
	token* t;
	size_t len;
	if (ANNOTATION_START(scan*)) {
	}
	else {
		s->log("Expected '" S_ANNOTATION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (TOKEN_START(scan*)) {
	}
	else {
		s->log("Expected '" S_TOKEN_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC_START(scan*) { return ((token_scan(s, T_ROUNDO)) || ((token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS)))); }
bool TC(scan*, token*) {
	token* thistoken = token_gen(s, S_TC);
	token* t;
	size_t len;
	if (TC0_START(scan*)) {
	}
	else {
		s->log("Expected '" S_TC0_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ANNOTATION_START(scan*) { return token_scan(s, T_ANNOTATION); }
bool ANNOTATION(scan*, token*) {
	token* thistoken = token_gen(s, S_ANNOTATION);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ANNOTATION)) {
	}
	else {
		s->log("Expected '" T_ANNOTATION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (ASKIP_START(scan*)) {
	}
	else {
		s->log("Expected '" S_ASKIP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ASKIP_START(scan*) { return token_scan(s, T_SKIP); }
bool ASKIP(scan*, token*) {
	token* thistoken = token_gen(s, S_ASKIP);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SKIP)) {
	}
	else {
		s->log("Expected '" T_SKIP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ANYTEXT)) {
	}
	else {
		s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ACASESENSITIVE_START(scan*) { return token_scan(s, T_CASESENSITIVE); }
bool ACASESENSITIVE(scan*, token*) {
	token* thistoken = token_gen(s, S_ACASESENSITIVE);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CASESENSITIVE)) {
	}
	else {
		s->log("Expected '" T_CASESENSITIVE_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_TRUE)) {
	}
	else {
		s->log("Expected '" T_TRUE_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ALINECOMMENTSTART_START(scan*) { return token_scan(s, T_LINECOMMENTSTART); }
bool ALINECOMMENTSTART(scan*, token*) {
	token* thistoken = token_gen(s, S_ALINECOMMENTSTART);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_LINECOMMENTSTART)) {
	}
	else {
		s->log("Expected '" T_LINECOMMENTSTART_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ANYTEXT)) {
	}
	else {
		s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TOKEN_START(scan*) { return token_scan(s, T_TOKENIDENT); }
bool TOKEN(scan*, token*) {
	token* thistoken = token_gen(s, S_TOKEN);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_TOKENIDENT)) {
	}
	else {
		s->log("Expected '" T_TOKENIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_STMTSEP)) {
	}
	else {
		s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ANYTEXT)) {
	}
	else {
		s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_GT)) {
	}
	else {
		s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (TC_START(scan*)) {
	}
	else {
		s->log("Expected '" S_TC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_SC)) {
	}
	else {
		s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TCG_START(scan*) { return token_scan(s, T_ROUNDO); }
bool TCG(scan*, token*) {
	token* thistoken = token_gen(s, S_TCG);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) {
	}
	else {
		s->log("Expected '" T_ROUNDO_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (TC_START(scan*)) {
	}
	else {
		s->log("Expected '" S_TC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ROUNDC)) {
	}
	else {
		s->log("Expected '" T_ROUNDC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_PLUS)) {
	}
	else {
		s->log("Expected '" T_PLUS_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC0_START(scan*) { return (token_scan(s, T_ROUNDO)) || ((token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS))); }
bool TC0(scan*, token*) {
	token* thistoken = token_gen(s, S_TC0);
	token* t;
	size_t len;
	if (TCG_START(scan*)) {
	}
	else if (TC1_START(scan*)) {
		if (TC1_START(scan*)) {
		}
		else {
			s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" S_TCG_STR "' or '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC1_START(scan*) { return (token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS)); }
bool TC1(scan*, token*) {
	token* thistoken = token_gen(s, S_TC1);
	token* t;
	size_t len;
	if (TC2_START(scan*)) {
	}
	else {
		s->log("Expected '" S_TC2_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_MINUS)) {
	}
	else if ((len = token_scan(s, T_DOT)) {
		if ((len = token_scan(s, T_DOT)) {
		}
		else {
			s->log("Expected '" T_DOT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_MINUS_STR "' or '" T_DOT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC2_START(scan*) { return token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS); }
bool TC2(scan*, token*) {
	token* thistoken = token_gen(s, S_TC2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ALPHALOW)) {
	}
	else if ((len = token_scan(s, T_ALPHAUP)) {
		if ((len = token_scan(s, T_ALPHAUP)) {
		}
		else if ((len = token_scan(s, T_DIGIT)) {
			if ((len = token_scan(s, T_DIGIT)) {
			}
			else if ((len = token_scan(s, T_BS)) {
				if ((len = token_scan(s, T_BS)) {
				}
				else {
					s->log("Expected '" T_BS_STR "'", s->line, s->col, s->off, token_next_type(s));
				}
				if ((len = token_scan(s, T_ANY)) {
				}
				else {
					s->log("Expected '" T_ANY_STR "'", s->line, s->col, s->off, token_next_type(s));
				}
			}
			else {
				s->log("Expected '" T_DIGIT_STR "' or '" T_BS_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
		else {
			s->log("Expected '" T_ALPHAUP_STR "' or '" T_DIGIT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_ALPHALOW_STR "' or '" T_ALPHAUP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool STATEMENT_START(scan*) { return token_scan(s, T_STATEIDENT); }
bool STATEMENT(scan*, token*) {
	token* thistoken = token_gen(s, S_STATEMENT);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_STATEIDENT)) {
	}
	else {
		s->log("Expected '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_STMTSEP)) {
	}
	else {
		s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (EXPRESSION_START(scan*)) {
	}
	else {
		s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_SC)) {
	}
	else {
		s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPRESSION_START(scan*) { return ((token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO))))); }
bool EXPRESSION(scan*, token*) {
	token* thistoken = token_gen(s, S_EXPRESSION);
	token* t;
	size_t len;
	if (EXPL0_START(scan*)) {
	}
	else {
		s->log("Expected '" S_EXPL0_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL0_START(scan*) { return (token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO)))); }
bool EXPL0(scan*, token*) {
	token* thistoken = token_gen(s, S_EXPL0);
	token* t;
	size_t len;
	if (EXPL1_START(scan*)) {
	}
	else {
		s->log("Expected '" S_EXPL1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_OR)) {
	}
	else {
		s->log("Expected '" T_OR_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL1_START(scan*) { return token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO))); }
bool EXPL1(scan*, token*) {
	token* thistoken = token_gen(s, S_EXPL1);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CURLYO)) {
	}
	else if (EXPL2_START(scan*)) {
		if (EXPL2_START(scan*)) {
		}
		else {
			s->log("Expected '" S_EXPL2_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_CURLYO_STR "' or '" S_EXPL2_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL2_START(scan*) { return token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO)); }
bool EXPL2(scan*, token*) {
	token* thistoken = token_gen(s, S_EXPL2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SQUAREO)) {
	}
	else if (EXPL3_START(scan*)) {
		if (EXPL3_START(scan*)) {
		}
		else {
			s->log("Expected '" S_EXPL3_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_SQUAREO_STR "' or '" S_EXPL3_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL3_START(scan*) { return token_scan(s, T_ROUNDO); }
bool EXPL3(scan*, token*) {
	token* thistoken = token_gen(s, S_EXPL3);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) {
	}
	else {
		s->log("Expected '" T_ROUNDO_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (EXPRESSION_START(scan*)) {
	}
	else {
		s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ROUNDC)) {
	}
	else if ((len = token_scan(s, T_TOKENIDENT)) {
		if ((len = token_scan(s, T_TOKENIDENT)) {
		}
		else if ((len = token_scan(s, T_STATEIDENT)) {
			if ((len = token_scan(s, T_STATEIDENT)) {
			}
			else {
				s->log("Expected '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
			if (STMNTMOD_START(scan*)) {
			}
			else {
				s->log("Expected '" S_STMNTMOD_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
		else {
			s->log("Expected '" T_TOKENIDENT_STR "' or '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_ROUNDC_STR "' or '" T_TOKENIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool STMNTMOD_START(scan*) { return token_scan(s, T_LT); }
bool STMNTMOD(scan*, token*) {
	token* thistoken = token_gen(s, S_STMNTMOD);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_LT)) {
	}
	else {
		s->log("Expected '" T_LT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (SMMAX_START(scan*)) {
	}
	else {
		s->log("Expected '" S_SMMAX_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_GT)) {
	}
	else {
		s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool SMMAX_START(scan*) { return token_scan(s, T_MODMAX); }
bool SMMAX(scan*, token*) {
	token* thistoken = token_gen(s, S_SMMAX);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_MODMAX)) {
	}
	else {
		s->log("Expected '" T_MODMAX_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_COLON)) {
	}
	else {
		s->log("Expected '" T_COLON_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_NUMBER)) {
	}
	else {
		s->log("Expected '" T_NUMBER_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
