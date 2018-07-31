#include "Parser.h"

#include <malloc.h>

bool str_equals(const char* strin, const char* otherstr)
{
	int i;
	for (i = 0; strin[i] != '\0' && otherstr[i] != '\0' && strin[i] == otherstr[i]; i++);
	return otherstr[i] == '\0';
}

token* token_gen(scan *s, char type)
{
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
void token_del(token* ptr)
{
	int i;
	for (i = 0; i < ptr->top; i++)
	{
		token_del(ptr->children[i]);
	}
	free(ptr->children);
	free(ptr);
}
void token_grow(token* ptr)
{
	ptr->size = ptr->size * 2;
	ptr->children = realloc(ptr->children, sizeof(token*) * ptr->size);
}
void token_push(token* ptr, token* t)
{
	if (ptr->top == ptr->size)
	{
		token_grow(ptr);
	}
	ptr->children[ptr->top] = t;
	ptr->top++;
}

void token_skip(scan* s, size_t skip)
{
	bool commentmode = false;
	s->off += skip;
	s->col += skip;
	while (s->txt[s->off] != '\0')
	{
		if (commentmode)
		{
			s->off++;
			s->col++;
			if (s->txt[s->off] == '\n')
			{
				commentmode = false;
				s->line++;
				s->col = 0;
			}
			continue;
		}
		switch (s->txt[s->off])
		{
			case '\n':
				s->line++;
				s->col = 0;
			case ' ':
			case '\t':
			case '\r':
				s->off++;
				s->col++;
				break;
			case '/':
				if (s->txt[s->off + 1] == '/')
				{
					commentmode = true;
					break;
				}
			default:
				return;
		}
	}
}
size_t token_scan(scan* s, char expected)
{
	int i;

	switch (expected)
	{
		case T_TOKENIDENT: if (!(s->txt[s->off] >= 'a' && s->txt[s->off] <= 'z')) return 0; for (i = 1; (s->txt[i + s->off] >= 'a' && s->txt[i + s->off] <= 'z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++); return i;
		case T_STATEIDENT: if (!(s->txt[s->off] >= 'A' && s->txt[s->off] <= 'Z')) return 0; for (i = 1; (s->txt[i + s->off] >= 'A' && s->txt[i + s->off] <= 'Z') || (s->txt[i + s->off] >= '0' && s->txt[i + s->off] <= '9'); i++); return i;
		case T_STMTSEP: return s->txt[s->off] == '=' ? 1 : 0;
		case T_ANYTEXT: for (i = 0; s->txt[i + s->off] != ' ' && s->txt[i + s->off] != '\t' && s->txt[i + s->off] != '\r' && s->txt[i + s->off] != '\n'; i++) { if (s->txt[i + s->off] == '\\' && s->txt[i + s->off + 1] != '\0') i++; } return i;
		case T_ANNOTATION: return s->txt[s->off] == '@' ? 1 : 0;
		case T_SKIP: return str_equals(s->txt + s->off, "SKIP") ? 4 : 0;
		case T_CASESENSITIVE:  return str_equals(s->txt + s->off, "CASESENSITIVE") ? 13 : 0;
		case T_LINECOMMENTSTART: return str_equals(s->txt + s->off, "LINECOMMENTSTART") ? 16 : 0;
		case T_OR: return s->txt[s->off] == '|' ? 1 : 0;
		case T_CURLYO: return s->txt[s->off] == '{' ? 1 : 0;
		case T_CURLYC: return s->txt[s->off] == '}' ? 1 : 0;
		case T_ROUNDO: return s->txt[s->off] == '(' ? 1 : 0;
		case T_ROUNDC: return s->txt[s->off] == ')' ? 1 : 0;
		case T_SQUAREO: return s->txt[s->off] == '[' ? 1 : 0;
		case T_SQUAREC: return s->txt[s->off] == ']' ? 1 : 0;
		case T_TRUE: return str_equals(s->txt + s->off, "true") ? 4 : 0;
		case T_FALSE: return str_equals(s->txt + s->off, "false") ? 5 : 0;
		case T_SC: return s->txt[s->off] == ';' ? 1 : 0;
		case T_LT: return s->txt[s->off] == '<' ? 1 : 0;
		case T_GT: return s->txt[s->off] == '>' ? 1 : 0;
		case T_MODMAX: return str_equals(s->txt + s->off, "max") ? 3 : 0;
		case T_COLON: return s->txt[s->off] == ':' ? 1 : 0;
		case T_NUMBER: return (s->txt[s->off] >= '0' && s->txt[s->off] <= '9') ? 1 : 0;
		case T_ALPHALOW: return (s->txt[s->off] >= 'a' && s->txt[s->off] <= 'z') ? 1 : 0;
		case T_ALPHAUP: return (s->txt[s->off] >= 'A' && s->txt[s->off] <= 'Z') ? 1 : 0;
		case T_MINUS: return s->txt[s->off] == '-' ? 1 : 0;
		case T_PLUS: return s->txt[s->off] == '+' ? 1 : 0;
		case T_DIGIT: return (s->txt[s->off] >= '0' && s->txt[s->off] <= '9') ? 1 : 0;
		case T_ANY: return s->txt[s->off] != ' ' && s->txt[s->off] != '\t' && s->txt[s->off] != '\r' && s->txt[s->off] != '\n' ? 1 : 0;
		case T_DOT: return s->txt[s->off] == '.' ? 1 : 0;
		case T_BS: return s->txt[s->off] == '\\' ? 1 : 0;
		case T_SPACE: return s->txt[s->off] == ' ' ? 1 : 0;
	}
	return 0;
}
char token_next_type(scan* s)
{
	for (int i = T__FIRST; i < T__LAST; i++)
	{
		if (token_scan(s, i) > 0) return i;
	}
	return T__INVALID;
}

//EBNF = { ANNOTATION } { TOKEN | STATEMENT };
bool EBNF_START(scan *s) { return ANNOTATION_START(s) || TOKEN_START(s) || STATEMENT_START(s); }
void EBNF(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EBNF);
	while (true)
	{
		if (ANNOTATION_START(s))
		{
			ANNOTATION(s, thistoken);
		}
		else
		{
			break;
		}
	}
	while (true)
	{
		if (TOKEN_START(s))
		{
			TOKEN(s, thistoken);
		}
		else if (STATEMENT_START(s))
		{
			STATEMENT(s, thistoken);
		}
		else
		{
			break;
		}
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}

//ANNOTATION = annotation ( ASKIP | ACASEINSENSITIVE | ALINECOMMENTSTART );
bool ANNOTATION_START(scan *s) { return token_scan(s, T_ANNOTATION); }
void ANNOTATION(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_ANNOTATION);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ANNOTATION)) > 0)
	{
		t = token_gen(s, T_ANNOTATION);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_ANNOTATION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (ASKIP_START(s))
	{
		ASKIP(s, thistoken);
	}
	else if (ACASESENSITIVE_START(s))
	{
		ACASESENSITIVE(s, thistoken);
	}
	else if (ALINECOMMENTSTART_START(s))
	{
		ALINECOMMENTSTART(s, thistoken);
	}
	else
	{
		s->log("Expected '" S_ASKIP_STR "' or '" S_ACASESENSITIVE_STR "' or '" S_ALINECOMMENTSTART_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//ASKIP = skip anytext;
bool ASKIP_START(scan *s) { return token_scan(s, T_SKIP); }
void ASKIP(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_ASKIP);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SKIP)) > 0)
	{
		t = token_gen(s, T_SKIP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_SKIP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ANYTEXT)) > 0)
	{
		t = token_gen(s, T_ANYTEXT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//ACASESENSITIVE = casesensitive ( true | false );
bool ACASESENSITIVE_START(scan *s) { return token_scan(s, T_CASESENSITIVE); }
void ACASESENSITIVE(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_ACASESENSITIVE);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CASESENSITIVE)) > 0)
	{
		t = token_gen(s, T_CASESENSITIVE);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_CASESENSITIVE_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_TRUE)) > 0)
	{
		t = token_gen(s, T_TRUE);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_FALSE)) > 0)
	{
		t = token_gen(s, T_FALSE);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_TRUE_STR "' or '" T_FALSE_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//ALINECOMMENTSTART = linecommentstart anytext;
bool ALINECOMMENTSTART_START(scan *s) { return token_scan(s, T_LINECOMMENTSTART); }
void ALINECOMMENTSTART(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_ALINECOMMENTSTART);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_LINECOMMENTSTART)) > 0)
	{
		t = token_gen(s, T_LINECOMMENTSTART);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_LINECOMMENTSTART_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ANYTEXT)) > 0)
	{
		t = token_gen(s, T_ANYTEXT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_ANYTEXT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}

//TOKEN = tokenident stmtsep [ anytext ] gt TC sc;
bool TOKEN_START(scan *s) { return token_scan(s, T_TOKENIDENT); }
void TOKEN(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TOKEN);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_TOKENIDENT)) > 0)
	{
		t = token_gen(s, T_TOKENIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_TOKENIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_STMTSEP)) > 0)
	{
		t = token_gen(s, T_STMTSEP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_GT)) > 0)
	{
		t = token_gen(s, T_GT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_ANYTEXT)) > 0)
	{
		t = token_gen(s, T_ANYTEXT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		if ((len = token_scan(s, T_GT)) > 0)
		{
			t = token_gen(s, T_GT);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else
		{
			s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else
	{
		s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (TC_START(s))
	{
		TC(s, thistoken);
	}
	else
	{
		s->log("Expected '" S_TC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_SC)) > 0)
	{
		t = token_gen(s, T_SC);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//TC = { TC0 };
bool TC_START(scan *s) { return TC0_START(s); }
void TC(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TC);
	token* t;
	size_t len;
	while (TC0_START(s))
	{
		TC0(s, thistoken);
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//TCG = roundo TC1 { TC1 } roundc [ plus ]
bool TCG_START(scan *s) { return token_scan(s, T_ROUNDO); }
void TCG(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TCG);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) > 0)
	{
		t = token_gen(s, T_ROUNDO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_ROUNDO_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (TC1_START(s))
	{
		do
		{
			TC1(s, thistoken);
		} while (TC1_START(s));
	}
	else
	{
		s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_ROUNDC)) > 0)
	{
		t = token_gen(s, T_ROUNDC);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_ROUNDC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_PLUS)) > 0)
	{
		t = token_gen(s, T_PLUS);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//TC0 = TCG | TC1;
bool TC0_START(scan *s) { return TCG_START(s) || TC1_START(s); }
void TC0(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TC0);
	token* t;
	size_t len;
	if (TCG_START(s))
	{
		TCG(s, thistoken);
	}
	else if (TC1_START(s))
	{
		TC1(s, thistoken);
	}
	else
	{
		s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//TC1 = TC2 [ minus TC2 | { TC2 } ] | dot;
bool TC1_START(scan *s) { return TC2_START(s) || token_scan(s, T_DOT);; }
void TC1(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TC1);
	token* t;
	size_t len;
	if (TC2_START(s))
	{
		TC2(s, thistoken);
		if ((len = token_scan(s, T_MINUS)) > 0)
		{
			t = token_gen(s, T_MINUS);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);

			if (TC2_START(s))
			{
				TC2(s, thistoken);
			}
			else
			{
				s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
			}
		}
		else if (TC2_START(s))
		{
			do
			{
				TC2(s, thistoken);
			} while (TC2_START(s));
		}
	}
	else if ((len = token_scan(s, T_DOT)) > 0)
	{
		t = token_gen(s, T_DOT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" S_TC1_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//TC2 = alphalow | alphaup | digit | bs any;
bool TC2_START(scan *s) { return token_scan(s, T_ALPHALOW) || token_scan(s, T_ALPHAUP) || token_scan(s, T_DIGIT) || token_scan(s, T_BS); }
void TC2(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_TC2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ALPHALOW)) > 0)
	{
		t = token_gen(s, T_ALPHALOW);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_ALPHAUP)) > 0)
	{
		t = token_gen(s, T_ALPHAUP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_DIGIT)) > 0)
	{
		t = token_gen(s, T_DIGIT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_BS)) > 0)
	{
		t = token_gen(s, T_BS);
		t->length = len;
		token_push(thistoken, t);
		if ((len = token_scan(s, T_ANY)) > 0)
		{
			t = token_gen(s, T_ANY);
			t->length = len;
			token_skip(s, len + 1);
			token_push(thistoken, t);
		}
		else
		{
			s->log("Expected '" T_ANY_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else
	{
		s->log("Expected '" S_TCG_STR "' or '"  T_ALPHALOW_STR "' or '"  T_ALPHAUP_STR "' or '"  T_DIGIT_STR "' or '"  T_BS_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//STATEMENT = stateident stmtsep EXPRESSION sc;
bool STATEMENT_START(scan *s) { return token_scan(s, T_STATEIDENT); }
void STATEMENT(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_STATEMENT);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_STATEIDENT)) > 0)
	{
		t = token_gen(s, T_STATEIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_STMTSEP)) > 0)
	{
		t = token_gen(s, T_STMTSEP);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_STMTSEP_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if (EXPRESSION_START(s))
	{
		EXPRESSION(s, thistoken);
	}
	else
	{
		s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_SC)) > 0)
	{
		t = token_gen(s, T_SC);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_SC_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPRESSION = EXPL0 { EXPL0 };
bool EXPRESSION_START(scan *s) { return EXPL0_START(s); }
void EXPRESSION(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPRESSION);
	token* t;
	size_t len;
	while (EXPL0_START(s))
	{
		EXPL0(s, thistoken);
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPRESSION2 = EXPL1 { EXPL1 };
bool EXPRESSION2_START(scan *s) { return EXPL1_START(s); }
void EXPRESSION2(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPRESSION2);
	token* t;
	size_t len;
	while (EXPL1_START(s))
	{
		EXPL1(s, thistoken);
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPL0 = EXPRESSION2 { or EXPRESSION2 };
bool EXPL0_START(scan *s) { return EXPL1_START(s); }
void EXPL0(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPL0);
	token* t;
	size_t len;
	if (EXPRESSION2_START(s))
	{
		EXPRESSION2(s, thistoken);
	}
	else
	{
		s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	while ((len = token_scan(s, T_OR)) > 0)
	{
		t = token_gen(s, T_OR);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);

		if (EXPRESSION2_START(s))
		{
			EXPRESSION2(s, thistoken);
		}
		else
		{
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPL1 = ( curlyo EXPRESSION curlyc ) | EXPL2;
bool EXPL1_START(scan *s) { return token_scan(s, T_CURLYO) || EXPL2_START(s); }
void EXPL1(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPL1);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_CURLYO)) > 0)
	{
		t = token_gen(s, T_CURLYO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);

		if (EXPRESSION_START(s))
		{
			EXPRESSION(s, thistoken);
		}
		else
		{
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_CURLYC)) > 0)
		{
			t = token_gen(s, T_CURLYC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else
		{
			s->log("Expected '" T_CURLYC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else if (EXPL2_START(s))
	{
		EXPL2(s, thistoken);
	}
	else
	{
		s->log("Expected '" T_CURLYO_STR "' or '" S_EXPL2_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPL2 = ( squareo EXPRESSION squarec ) | EXPL3;
bool EXPL2_START(scan *s) { return token_scan(s, T_SQUAREO) || EXPL3_START(s); }
void EXPL2(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPL2);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_SQUAREO)) > 0)
	{
		t = token_gen(s, T_SQUAREO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);

		if (EXPRESSION_START(s))
		{
			EXPRESSION(s, thistoken);
		}
		else
		{
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_SQUAREC)) > 0)
		{
			t = token_gen(s, T_SQUAREC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else
		{
			s->log("Expected '" T_SQUAREC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else if (EXPL3_START(s))
	{
		EXPL3(s, thistoken);
	}
	else
	{
		s->log("Expected '" T_SQUAREO_STR "' or '" S_EXPL3_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//EXPL3 = roundo EXPRESSION roundc | tokenident | stateident;
bool EXPL3_START(scan *s) { return token_scan(s, T_ROUNDO) || token_scan(s, T_TOKENIDENT) || token_scan(s, T_STATEIDENT); }
void EXPL3(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_EXPL3);
	token* t;
	size_t len;
	if ((len = token_scan(s, T_ROUNDO)) > 0)
	{
		t = token_gen(s, T_ROUNDO);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);

		if (EXPRESSION_START(s))
		{
			EXPRESSION(s, thistoken);
		}
		else
		{
			s->log("Expected '" S_EXPRESSION_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
		if ((len = token_scan(s, T_ROUNDC)) > 0)
		{
			t = token_gen(s, T_ROUNDC);
			t->length = len;
			token_skip(s, len);
			token_push(thistoken, t);
		}
		else
		{
			s->log("Expected '" T_ROUNDC_STR "'", s->line, s->col, s->off, token_next_type(s));
		}
	}
	else if ((len = token_scan(s, T_TOKENIDENT)) > 0)
	{
		t = token_gen(s, T_TOKENIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else if ((len = token_scan(s, T_STATEIDENT)) > 0)
	{
		t = token_gen(s, T_STATEIDENT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
		//if (STMNTMOD_START(s))
		//{
		//	STMNTMOD(s, thistoken);
		//}
	}
	else
	{
		s->log("Expected '" T_ROUNDO_STR "' or '" T_TOKENIDENT_STR "' or '" T_STATEIDENT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}


/*
//STMNTMOD = lt { SMMAX<max:1> } gt;
bool STMNTMOD_START(scan *s) { return token_scan(s, T_LT); }
void STMNTMOD(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_STMNTMOD);
	token* t;
	size_t len;
	short smax_count = 0;
	if ((len = token_scan(s, T_LT)) > 0)
	{
		t = token_gen(s, T_LT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_LT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	while (SMMAX_START(s))
	{
		if (smax_count >= 1)
		{
			s->log("SMMAX is not allowed to occur more often then 1.", s->line, s->col, s->off, token_next_type(s));
		}
		else
		{
			SMMAX(s, thistoken);
		}
	}
	if ((len = token_scan(s, T_GT)) > 0)
	{
		t = token_gen(s, T_GT);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_GT_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
//SMMAX = modmax colon number;
bool SMMAX_START(scan *s) { return token_scan(s, T_MODMAX); }
void SMMAX(scan *s, token* parent)
{
	token* thistoken = token_gen(s, S_SMMAX);
	token* t;
	size_t len;
	short smax_count = 0;
	if ((len = token_scan(s, T_MODMAX)) > 0)
	{
		t = token_gen(s, T_MODMAX);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_MODMAX_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_COLON)) > 0)
	{
		t = token_gen(s, T_COLON);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_COLON_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	if ((len = token_scan(s, T_NUMBER)) > 0)
	{
		t = token_gen(s, T_NUMBER);
		t->length = len;
		token_skip(s, len);
		token_push(thistoken, t);
	}
	else
	{
		s->log("Expected '" T_NUMBER_STR "'", s->line, s->col, s->off, token_next_type(s));
	}
	thistoken->length = s->off - thistoken->offset;
	token_push(parent, thistoken);
}
*/