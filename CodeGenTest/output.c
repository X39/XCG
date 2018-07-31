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
	token** tmp;
	ptr->size = ptr->size * 2;
	tmp = realloc(ptr->children, sizeof(token*) * ptr->size);
	if (tmp == 0) {
		exit(1);
	}
	ptr->children = tmp;
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
char token_next_type(scan* s) {
	for (int i = T__FIRST; i < T__LAST; i++) {
		if (token_scan(s, i) > 0) return i;
	}
	return T__INVALID;
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
			case '/': if (s->txt[s->off + 1] == '/') { commentmode = true; break; }
			default: return;
		}
	}
}
size_t token_scan(scan* s, char expected) {
	int i = 0;
	switch(expected) {
		case T_TOKENIDENT:
		{
			if(!((s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z'))) return 0;
			i++;
			if(!((s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; }
			i++;
			for(; (s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++) { if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; } };
			return i;
		}
		case T_STATEIDENT:
		{
			if(!((s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z'))) return 0;
			i++;
			if(!((s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'))) return 0;
			if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; }
			i++;
			for(; (s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++) { if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; } };
			return i;
		}
		case T_STMTSEP: return s->txt[s->off] == '=' ? 1 : 0;
		case T_ANYTEXT:
		{
			if(!((s->txt[i + s->off] != ' ' && s->txt[i + s->off] != '\r' && s->txt[i + s->off] != '\n' && s->txt[i + s->off] != '\t') ? 1 : 0)) return 0;
			if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; }
			i++;
			for(; (s->txt[i + s->off] != ' ' && s->txt[i + s->off] != '\r' && s->txt[i + s->off] != '\n' && s->txt[i + s->off] != '\t') ? 1 : 0; i++) { if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; } };
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
			if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; }
			i++;
			for(; (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++) { if(s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') { i++; } };
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
		case T_ANY:
		{
			i += (s->txt[i + s->off] != ' ' && s->txt[i + s->off] != '\r' && s->txt[i + s->off] != '\n' && s->txt[i + s->off] != '\t') ? 1 : 0;
			return i;
		}
		case T_DOT: return s->txt[s->off] == '.' ? 1 : 0;
		case T_BS: return s->txt[s->off] == '\\' ? 1 : 0;
	}
}
bool EBNF_START(scan* s) { return (token_scan(s, T_ANNOTATION)); }
bool EBNF(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EBNF);
	token* t;
	size_t len;
	if (ANNOTATION_START(s)) {
		while (true) {
			if (ANNOTATION_START(s)) {
				ANNOTATION(s, thistoken);
			}
			else { break; }
		}
		while (true) {
			if (TOKEN_START(s)) {
				TOKEN(s, thistoken);
			}
			else if (STATEMENT_START(s)) {
				STATEMENT(s, thistoken);
			}
			else { break; }
		}
	}
	else {
		s->log("Expected '" S_ANNOTATION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ANNOTATION_START(scan* s) { return token_scan(s, T_ANNOTATION); }
bool ANNOTATION(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_ANNOTATION);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ANNOTATION)) > 0) {
		t = token_gen(s, T_ANNOTATION);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if (ASKIP_START(s)) {
			ASKIP(s, thistoken);
		}
		else if (ACASESENSITIVE_START(s)) {
			ACASESENSITIVE(s, thistoken);
		}
		else if (ALINECOMMENTSTART_START(s)) {
			ALINECOMMENTSTART(s, thistoken);
		}
	}
	else {
		s->log("Expected '" T_ANNOTATION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ASKIP_START(scan* s) { return token_scan(s, T_SKIP); }
bool ASKIP(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_ASKIP);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SKIP)) > 0) {
		t = token_gen(s, T_SKIP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_ANYTEXT)) > 0) {
			t = token_gen(s, T_ANYTEXT);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_SKIP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ACASESENSITIVE_START(scan* s) { return token_scan(s, T_CASESENSITIVE); }
bool ACASESENSITIVE(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_ACASESENSITIVE);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CASESENSITIVE)) > 0) {
		t = token_gen(s, T_CASESENSITIVE);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_TRUE)) > 0) {
			t = token_gen(s, T_TRUE);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else if ((len = token_scan(s, T_FALSE)) > 0) {
			t = token_gen(s, T_FALSE);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
	}
	else {
		s->log("Expected '" T_CASESENSITIVE_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool ALINECOMMENTSTART_START(scan* s) { return token_scan(s, T_LINECOMMENTSTART); }
bool ALINECOMMENTSTART(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_ALINECOMMENTSTART);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_LINECOMMENTSTART)) > 0) {
		t = token_gen(s, T_LINECOMMENTSTART);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_ANYTEXT)) > 0) {
			t = token_gen(s, T_ANYTEXT);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_LINECOMMENTSTART_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TOKEN_START(scan* s) { return token_scan(s, T_TOKENIDENT); }
bool TOKEN(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TOKEN);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_TOKENIDENT)) > 0) {
		t = token_gen(s, T_TOKENIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_STMTSEP)) > 0) {
			t = token_gen(s, T_STMTSEP);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_GT)) > 0) {
			t = token_gen(s, T_GT);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else if ((len = token_scan(s, T_ANYTEXT)) > 0) {
			t = token_gen(s, T_ANYTEXT);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
			if ((len = token_scan(s, T_GT)) > 0) {
				t = token_gen(s, T_GT);
				t->length = len;
				token_skip(s, len);
				token_push(thistoken, t);
			} else {
				s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
		if (TC_START(s)) {
			TC(s, thistoken);
		} else {
			s->log("Expected '" S_TC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_SC)) > 0) {
			t = token_gen(s, T_SC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_TOKENIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC_START(scan* s) { return ((token_scan(s, T_ROUNDO)) || ((token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS)) || token_scan(s, T_DOT))); }
bool TC(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TC);
	token* t;
	size_t len;
	if (TC0_START(s)) {
		while (true) {
			if (TC0_START(s)) {
				TC0(s, thistoken);
			}
			else { break; }
		}
	}
	else {
		s->log("Expected '" S_TC0_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TCG_START(scan* s) { return token_scan(s, T_ROUNDO); }
bool TCG(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TCG);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) > 0) {
		t = token_gen(s, T_ROUNDO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if (TC1_START(s)) {
			TC1(s, thistoken);
		} else {
			s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		while (true) {
			if (TC1_START(s)) {
				TC1(s, thistoken);
			}
			else { break; }
		}
		if ((len = token_scan(s, T_ROUNDC)) > 0) {
			t = token_gen(s, T_ROUNDC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_ROUNDC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_PLUS)) > 0) {
			t = token_gen(s, T_PLUS);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
	}
	else {
		s->log("Expected '" T_ROUNDO_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC0_START(scan* s) { return (token_scan(s, T_ROUNDO)) || ((token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS)) || token_scan(s, T_DOT)); }
bool TC0(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TC0);
	token* t;
	size_t len;
	if (TCG_START(s)) {
		TCG(s, thistoken);
	}
	else if (TC1_START(s)) {
		TC1(s, thistoken);
	}
	else {
		s->log("Expected '" S_TCG_STR "' or '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC1_START(scan* s) { return (token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS)) || token_scan(s, T_DOT); }
bool TC1(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TC1);
	token* t;
	size_t len;
	if (TC2_START(s)) {
		TC2(s, thistoken);
		if ((len = token_scan(s, T_MINUS)) > 0) {
			t = token_gen(s, T_MINUS);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
			if (TC2_START(s)) {
				TC2(s, thistoken);
			} else {
				s->log("Expected '" S_TC2_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
		else if (TC2_START(s)) {
			while (true) {
				if (TC2_START(s)) {
					TC2(s, thistoken);
				}
				else { break; }
			}
		}
	}
	else if ((len = token_scan(s, T_DOT)) > 0) {
		t = token_gen(s, T_DOT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else {
		s->log("Expected '" S_TC2_STR "' or '" T_DOT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool TC2_START(scan* s) { return token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS); }
bool TC2(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_TC2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ALPHALOW)) > 0) {
		t = token_gen(s, T_ALPHALOW);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_ALPHAUP)) > 0) {
		t = token_gen(s, T_ALPHAUP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_DIGIT)) > 0) {
		t = token_gen(s, T_DIGIT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_BS)) > 0) {
		t = token_gen(s, T_BS);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_ANY)) > 0) {
			t = token_gen(s, T_ANY);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_ANY_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_ALPHALOW_STR "' or '" T_ALPHAUP_STR "' or '" T_DIGIT_STR "' or '" T_BS_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool STATEMENT_START(scan* s) { return token_scan(s, T_STATEIDENT); }
bool STATEMENT(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_STATEMENT);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_STATEIDENT)) > 0) {
		t = token_gen(s, T_STATEIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_STMTSEP)) > 0) {
			t = token_gen(s, T_STMTSEP);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if (EXPRESSION_START(s)) {
			EXPRESSION(s, thistoken);
		} else {
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_SC)) > 0) {
			t = token_gen(s, T_SC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else {
		s->log("Expected '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPRESSION_START(scan* s) { return (((token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT)))))); }
bool EXPRESSION(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPRESSION);
	token* t;
	size_t len;
	if (EXPL0_START(s)) {
		EXPL0(s, thistoken);
		while (true) {
			if (EXPL0_START(s)) {
				EXPL0(s, thistoken);
			}
			else { break; }
		}
	}
	else {
		s->log("Expected '" S_EXPL0_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL0_START(scan* s) { return ((token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT))))); }
bool EXPL0(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPL0);
	token* t;
	size_t len;
	if (EXPRESSION2_START(s)) {
		EXPRESSION2(s, thistoken);
		while (true) {
			if ((len = token_scan(s, T_OR)) > 0) {
				t = token_gen(s, T_OR);
				t->length = len;
				token_skip(s, len);
				token_push(thistoken, t);
				if (EXPRESSION2_START(s)) {
					EXPRESSION2(s, thistoken);
				} else {
					s->log("Expected '" S_EXPRESSION2_STR "'", s->line, s->col, s->off, token_next_type(s));
				}
			}
			else { break; }
		}
	}
	else {
		s->log("Expected '" S_EXPRESSION2_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPRESSION2_START(scan* s) { return (token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT)))); }
bool EXPRESSION2(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPRESSION2);
	token* t;
	size_t len;
	if (EXPL1_START(s)) {
		EXPL1(s, thistoken);
		while (true) {
			if (EXPL1_START(s)) {
				EXPL1(s, thistoken);
			}
			else { break; }
		}
	}
	else {
		s->log("Expected '" S_EXPL1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL1_START(scan* s) { return token_scan(s, T_CURLYO) || (token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT))); }
bool EXPL1(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPL1);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CURLYO)) > 0) {
		if ((len = token_scan(s, T_CURLYO)) > 0) {
			t = token_gen(s, T_CURLYO);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
			if (EXPRESSION_START(s)) {
				EXPRESSION(s, thistoken);
			} else {
				s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
			if ((len = token_scan(s, T_CURLYC)) > 0) {
				t = token_gen(s, T_CURLYC);
				t->length = len;
				token_skip(s, len);
				token_push(thistoken, t);
			} else {
				s->log("Expected '" T_CURLYC_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
	}
	else if (EXPL2_START(s)) {
		EXPL2(s, thistoken);
	}
	else {
		s->log("Expected '" T_CURLYO_STR "' or '" S_EXPL2_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL2_START(scan* s) { return token_scan(s, T_SQUAREO) || (token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT)); }
bool EXPL2(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPL2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SQUAREO)) > 0) {
		if ((len = token_scan(s, T_SQUAREO)) > 0) {
			t = token_gen(s, T_SQUAREO);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
			if (EXPRESSION_START(s)) {
				EXPRESSION(s, thistoken);
			} else {
				s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
			if ((len = token_scan(s, T_SQUAREC)) > 0) {
				t = token_gen(s, T_SQUAREC);
				t->length = len;
				token_skip(s, len);
				token_push(thistoken, t);
			} else {
				s->log("Expected '" T_SQUAREC_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
	}
	else if (EXPL3_START(s)) {
		EXPL3(s, thistoken);
	}
	else {
		s->log("Expected '" T_SQUAREO_STR "' or '" S_EXPL3_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
bool EXPL3_START(scan* s) { return token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT); }
bool EXPL3(scan* s, token* parent) {
	token* thistoken = token_gen(s, S_EXPL3);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) > 0) {
		t = token_gen(s, T_ROUNDO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if (EXPRESSION_START(s)) {
			EXPRESSION(s, thistoken);
		} else {
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_ROUNDC)) > 0) {
			t = token_gen(s, T_ROUNDC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		} else {
			s->log("Expected '" T_ROUNDC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else if ((len = token_scan(s, T_TOKENIDENT)) > 0) {
		t = token_gen(s, T_TOKENIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_STATEIDENT)) > 0) {
		t = token_gen(s, T_STATEIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else {
		s->log("Expected '" T_ROUNDO_STR "' or '" T_TOKENIDENT_STR "' or '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
