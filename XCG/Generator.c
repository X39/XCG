#include "Generator.h"
#include <string.h>
#include <ctype.h>

#define TABS10 "\t\t\t\t\t\t\t\t\t\t"
#define TABS50 TABS10 TABS10 TABS10 TABS10 TABS10 
#define TABS100 TABS50 TABS50

#define ELSEMODE_INACTIVE 0
#define ELSEMODE_PREPARED 1
#define ELSEMODE_ACTIVE 2


bool str_partial_equals(const char* strin, const char* otherstr, size_t len) {
	size_t i;
	for (i = 0; strin[i] != '\0' && otherstr[i] != '\0' && strin[i] == otherstr[i] && i != len; i++);
	return i == len;
}
pgen_stmnt_helper gen_stmnt_helper_create(void)
{
	pgen_stmnt_helper h = malloc(sizeof(gen_stmnt_helper));
	h->helpers = malloc(sizeof(gen_stmnt_helper*) * 25);
	h->helpers_top = 0;
	h->helpers_size = 25;
	h->tokens = malloc(sizeof(token*) * 25);
	h->tokens_top = 0;
	h->tokens_size = 25;
	return h;
}
void gen_stmnt_helper_destroy(pgen_stmnt_helper h)
{
	size_t i;
	for (i = 0; i < h->helpers_top; i++)
	{
		gen_stmnt_helper_destroy(h->helpers[i]);
	}
	free(h->helpers);
	free(h->tokens);
	free(h);
}
void gen_stmnt_helper_push_token(pgen_stmnt_helper h, token* t)
{
	token** ptr;
	size_t s;
	if (h->tokens_top == h->tokens_size)
	{
		s = h->tokens_size * 2;
		ptr = realloc(h->tokens, sizeof(token*) * s);
		if (ptr == 0)
		{
			//ToDo: Propper error logging
			printf("Realloc failed.\n");
			return;
		}
		h->tokens = ptr;
		h->tokens_size = s;
	}
	h->tokens[h->tokens_top++] = t;
}
void gen_stmnt_helper_push_helper(pgen_stmnt_helper h, pgen_stmnt_helper h2)
{
	gen_stmnt_helper ** ptr;
	size_t s;
	if (h->helpers_top == h->helpers_size)
	{
		s = h->helpers_size * 2;
		ptr = realloc(h->helpers, sizeof(gen_stmnt_helper*) * s);
		if (ptr == 0)
		{
			//ToDo: Propper error logging
			printf("Realloc failed.\n");
			return;
		}
		h->helpers = ptr;
		h->helpers_size = s;
	}
	h->helpers[h->helpers_top++] = h2;
}

token* generator_next_token2(token* root, size_t * tokenindex)
{
	size_t i;
	token* othertoken;
	if (root->type >= T__FIRST && root->type <= T__LAST)
	{
		if (*tokenindex == 0)
		{
			return root;
		}
		--*tokenindex;
		return 0;
	}
	else
	{
		for (i = 0; i < root->top; i++)
		{
			othertoken = generator_next_token2(root->children[i], tokenindex);
			if (othertoken != 0)
			{
				return othertoken;
			}
		}
	}
	return 0;
}
token* generator_next_token(token* root, size_t tokenindex)
{
	return generator_next_token2(root, &tokenindex);
}

void token_flatten(token* target, token* source)
{
	size_t i;
	token* t;
	for (i = 0; i < source->top; i++)
	{
		t = source->children[i];
		if (t->type >= T__FIRST && t->type <= T__LAST)
		{
			token_push(target, t);
		}
		else
		{
			token_flatten(target, source->children[i]);
		}
	}
}

PGENERATOR generator_create(FILE* code, FILE* header, const char* fname, token* r, const char* origtext)
{
	PGENERATOR gen = malloc(sizeof(generator));
	memset(gen, 0, sizeof(generator));
	gen->code = code;
	gen->header = header;
	gen->origtext = origtext;
	gen->fname = fname;
	gen->root = r;
	gen->linecommentstart = NULL;
	gen->blockcommentstart = NULL;
	gen->blockcommentend = NULL;
	gen->skip_characters = malloc(sizeof(char) * 10);
	strcpy(gen->skip_characters, "\\ \\t\\r\\n");
	if (r->top == 1 && r->children[0]->type == S_EBNF)
	{
		gen->root = r->children[0];
	}
	return gen;
}
void generator_destroy(PGENERATOR gen)
{
	if (gen->linecommentstart != NULL) { free(gen->linecommentstart); }
	if (gen->blockcommentstart != NULL) { free(gen->blockcommentstart); }
	if (gen->blockcommentend != NULL) { free(gen->blockcommentend); }
	free(gen->skip_characters);
	free(gen);
}

char generator_get_escaped_char(char input)
{
	switch (input)
	{
		case 'n': return '\n';
		case 't': return '\t';
		case 'r': return '\r';
		default: return input;
	}
}

void generator_handle_annotation(PGENERATOR gen, token* anno)
{
	switch (anno->children[1]->type)
	{
		case S_ASKIP:
			free(gen->skip_characters);
			gen->skip_characters = malloc(anno->children[1]->children[1]->length + 1);
			strncpy(gen->skip_characters, gen->origtext + anno->children[1]->children[1]->offset, anno->children[1]->children[1]->length);
			gen->skip_characters[anno->children[1]->children[1]->length] = '\0';
			break;
		case S_ACASESENSITIVE:
			gen->casesensitive = anno->children[1]->children[1]->type == T_TRUE;
			break;
		case S_ALINECOMMENTSTART:
			if (gen->linecommentstart != NULL)
			{
				free(gen->linecommentstart);
			}
			gen->linecommentstart = malloc(anno->children[1]->children[1]->length + 1);
			strncpy(gen->linecommentstart, gen->origtext + anno->children[1]->children[1]->offset, anno->children[1]->children[1]->length);
			gen->linecommentstart[anno->children[1]->children[1]->length] = '\0';
			break;
		case S_BLOCKCOMMENTSTART:
			if (gen->blockcommentstart != NULL)
			{
				free(gen->blockcommentstart);
			}
			gen->blockcommentstart = malloc(anno->children[1]->children[1]->length + 1);
			strncpy(gen->blockcommentstart, gen->origtext + anno->children[1]->children[1]->offset, anno->children[1]->children[1]->length);
			gen->blockcommentstart[anno->children[1]->children[1]->length] = '\0';

			break;
		case S_BLOCKCOMMENTEND:
			if (gen->blockcommentend != NULL)
			{
				free(gen->blockcommentend);
			}
			gen->blockcommentend = malloc(anno->children[1]->children[1]->length + 1);
			strncpy(gen->blockcommentend, gen->origtext + anno->children[1]->children[1]->offset, anno->children[1]->children[1]->length);
			gen->blockcommentend[anno->children[1]->children[1]->length] = '\0';

			break;
	}
}
void generator_write_token_skip_method(PGENERATOR gen)
{
	size_t i, j;
	char c;
	bool nlAvailable = false;
	bool isEscaped;
	fprintf(gen->code, "void token_skip(scan* s, size_t skip) {" "\n");
	if (gen->linecommentstart != NULL)
	{
		fprintf(gen->code, "\tbool lcommentmode = false;" "\n");
	}
	if (gen->blockcommentstart != NULL)
	{
		fprintf(gen->code, "\tbool bcommentmode = false;" "\n");
	}
	fprintf(gen->code, "\ts->off += skip;" "\n"
		"\ts->col += skip;" "\n"
		"\twhile (s->txt[s->off] != '\\0') {" "\n");
	if (gen->linecommentstart != NULL)
	{
		fprintf(gen->code,
			"\t\tif (lcommentmode) {" "\n"
			"\t\t\ts->off++;" "\n"
			"\t\t\ts->col++;" "\n"
			"\t\t\tif (s->txt[s->off] == '\\n') {" "\n"
			"\t\t\t\tlcommentmode = false;" "\n"
			"\t\t\t\ts->line++;" "\n"
			"\t\t\t\ts->col = 0;" "\n"
			"\t\t\t}" "\n"
			"\t\t\tcontinue;" "\n"
			"\t\t}" "\n"
		);
	}
	if (gen->blockcommentend != NULL)
	{
		fprintf(gen->code,
			"\t\tif (bcommentmode) {" "\n"
			"\t\t\ts->off++;" "\n"
			"\t\t\ts->col++;" "\n"
			"\t\t\tif (");
		isEscaped = false; //Why you no use proper variable for dis!?
		for (i = 0, j = 0; (c = gen->blockcommentend[i]) != '\0'; i++)
		{
			if (c == '\\' && gen->blockcommentend[i + 1] != '\0')
			{
				i++;
				c = gen->blockcommentend[i];
			}
			if (isEscaped) //Ohh bro ... really ...
			{
				fprintf(gen->code, " && ");
			}
			else
			{
				isEscaped = true; //You need help dude
			}
			fprintf(gen->code, "s->txt[s->off + %u] == '%c'", j, c);
			j++;
		}
		fprintf(gen->code, ") {" "\n"
			"\t\t\t\tbcommentmode = false;" "\n"
			"\t\t\t\ts->line++;" "\n"
			"\t\t\t\ts->col = 0;" "\n"
			"\t\t\t}" "\n"
			"\t\t\tcontinue;" "\n"
			"\t\t}" "\n"
		);
	}
	fprintf(gen->code, "\t\tswitch (s->txt[s->off]) {" "\n");

	for (i = 0; (c = gen->skip_characters[i]) != '\0'; i++)
	{
		isEscaped = c == '\\';
		if (isEscaped)
		{
			i++;
			c = gen->skip_characters[i];
			if (c == generator_get_escaped_char(c) && c != '\\')
			{
				isEscaped = false;
			}
		}
		if (isEscaped)
		{
			if (c == 'n')
			{
				nlAvailable = true;
				fprintf(gen->code, "\t\t\tcase '\\n': s->line++; s->col = 0; s->off++; break;\n");
			}
			else
			{
				fprintf(gen->code, "\t\t\tcase '\\%c': s->col++; s->off++; break;\n", c);
			}
		}
		else
		{
			fprintf(gen->code, "\t\t\tcase '%c': s->col++; s->off++; break;\n", c);
		}
	}
	if (!nlAvailable)
	{
		fprintf(gen->code, "\t\t\tcase '\\n': s->line++; s->col = 0; return;\n");
	}
	fprintf(gen->code, "\t\t\tdefault:\n");
	if (gen->linecommentstart != NULL)
	{
		fprintf(gen->code, "\t\t\t\tif (");
		nlAvailable = false; //cries "rape"
		for (i = 0, j = 0; (c = gen->linecommentstart[i]) != '\0'; i++)
		{
			if (c == '\\' && gen->linecommentstart[i + 1] != '\0')
			{
				i++;
				c = gen->linecommentstart[i];
			}
			if (nlAvailable) //cries "Why you do this to me.." T_T
			{
				fprintf(gen->code, " && ");
			}
			else
			{
				nlAvailable = true; //cries "No more please!"
			}
			fprintf(gen->code, "s->txt[s->off + %u] == '%c'", j, c);
			j++;
		}
		fprintf(gen->code, ") { lcommentmode = true; break; }\n");
	}
	if (gen->blockcommentstart != NULL)
	{
		fprintf(gen->code, "\t\t\t\tif (");
		nlAvailable = false; //cries "How are you not yet satisfied" T_T
		for (i = 0, j = 0; (c = gen->blockcommentstart[i]) != '\0'; i++)
		{
			if (c == '\\' && gen->blockcommentstart[i + 1] != '\0')
			{
				i++;
				c = gen->blockcommentstart[i];
			}
			if (nlAvailable) //cries "LET ME GO" T_T
			{
				fprintf(gen->code, " && ");
			}
			else
			{
				nlAvailable = true; //cries "No more please!"
			}
			fprintf(gen->code, "s->txt[s->off + %u] == '%c'", j, c);
			j++;
		}
		fprintf(gen->code, ") { bcommentmode = true; break; }\n");
	}
	fprintf(gen->code, "\t\t\t\treturn;\n\t\t}\n\t}\n}\n");
}
void generator_create_macro(PGENERATOR gen, token* token)
{
	int i;
	if (token->type == S_TOKEN)
	{
		fprintf(gen->header, "#define T_");
		for (i = 0; i < token->children[0]->length; i++)
		{
			fprintf(gen->header, "%c", toupper(*(gen->origtext + token->children[0]->offset + i)));
		}
		fprintf(gen->header, " %u\n", gen->depth++);

		fprintf(gen->header, "#define T_");
		for (i = 0; i < token->children[0]->length; i++)
		{
			fprintf(gen->header, "%c", toupper(*(gen->origtext + token->children[0]->offset + i)));
		}
		if (token->top >= 3 && token->children[2]->type == T_ANYTEXT)
		{
			fprintf(gen->header, "_STR %.*s\n", token->children[2]->length, gen->origtext + token->children[2]->offset);
		}
		else
		{
			fprintf(gen->header, "_STR \"%.*s\"\n", token->children[0]->length, gen->origtext + token->children[0]->offset);
		}
	}
	else
	{
		fprintf(gen->header, "#define S_%.*s %u\n", token->children[0]->length, gen->origtext + token->children[0]->offset, gen->depth++);
		fprintf(gen->header, "#define S_%.*s_STR \"%.*s\"\n", token->children[0]->length, gen->origtext + token->children[0]->offset, token->children[0]->length, gen->origtext + token->children[0]->offset);
	}
}

void generator_handle_token_recursive(PGENERATOR gen, token* token)
{
	size_t i;
	char c, c2;
	switch (token->type)
	{
		case S_TC:
			for (i = 0; i < token->top; i++)
			{
				generator_handle_token_recursive(gen, token->children[i]);
			}
			fprintf(gen->code, "%.*sreturn i;\n", gen->depth, TABS100);
			break;
		case S_TCG:
			if (token->children[token->top - 1]->type != T_PLUS)
			{
				fprintf(gen->code, "%.*s", gen->depth, TABS100);
				fprintf(gen->code, "if (!(");
				for (i = 1; i < token->top - 1; i++)
				{
					if (i > 1)
					{
						fprintf(gen->code, " || ");
					}
					generator_handle_token_recursive(gen, token->children[i]);
				}
				fprintf(gen->code, ")) return 0;\n");
				fprintf(gen->code, "%.*si++;\n", gen->depth, TABS100);
			}
			else
			{
				fprintf(gen->code, "%.*s", gen->depth, TABS100);
				fprintf(gen->code, "if (!(");
				for (i = 1; i < token->top - 2; i++)
				{
					if (i > 1)
					{
						fprintf(gen->code, " || ");
					}
					generator_handle_token_recursive(gen, token->children[i]);
				}
				fprintf(gen->code, ")) return 0;\n");
				fprintf(gen->code, "%.*sif (s->txt[i + s->off] == '\\\\' && s->txt[i + s->off + 1] != '\\0') { i++; }\n", gen->depth, TABS100);
				fprintf(gen->code, "%.*si++;\n", gen->depth, TABS100);
				fprintf(gen->code, "%.*s", gen->depth, TABS100);
				fprintf(gen->code, "for (; ");
				for (i = 1; i < token->top - 2; i++)
				{
					if (i > 1)
					{
						fprintf(gen->code, " || ");
					}
					generator_handle_token_recursive(gen, token->children[i]);
				}
				fprintf(gen->code, "; i++) { if(s->txt[i + s->off] == '\\\\' && s->txt[i + s->off + 1] != '\\0') { i++; } };\n");
			}
			break;
		case S_TC0:
			if (token->children[0]->type == S_TCG)
			{
				generator_handle_token_recursive(gen, token->children[0]);
			}
			else
			{
				fprintf(gen->code, "%.*s", gen->depth, TABS100);
				fprintf(gen->code, "i += ");
				generator_handle_token_recursive(gen, token->children[0]);
				fprintf(gen->code, ";\n");
			}
			break;
		case S_TC1:
			if (token->top == 3 && token->children[1]->type == T_MINUS)
			{
				fprintf(gen->code, "(s->txt[i + s->off] >= '");
				generator_handle_token_recursive(gen, token->children[0]);
				fprintf(gen->code, "' && s->txt[i + s->off] <= '");
				generator_handle_token_recursive(gen, token->children[2]);
				fprintf(gen->code, "')");
			}
			else if (token->children[0]->type == T_DOT)
			{
				fprintf(gen->code, "(");
				for (i = 0; (c = gen->skip_characters[i]) != '\0'; i++)
				{
					if (i > 0)
					{
						fprintf(gen->code, " && ");
					}
					if (c == '\'')
					{
						fprintf(gen->code, "s->txt[i + s->off] != '\\''");
					}
					else if (c == '\\')
					{
						c = gen->skip_characters[++i];
						c2 = generator_get_escaped_char(c);
						if (c2 != c)
						{
							fprintf(gen->code, "s->txt[i + s->off] != '\\%c'", c);
						}
						else
						{
							fprintf(gen->code, "s->txt[i + s->off] != '%c'", c);
						}
					}
					else
					{
						fprintf(gen->code, "s->txt[i + s->off] != '%c'", c);
					}
				}
				fprintf(gen->code, ")");
				fprintf(gen->code, " ? 1 : 0");
			}
			else
			{
				fprintf(gen->code, "str_equals(s->txt + s->off, \"");
				for (i = 0; i < token->top; i++)
				{
					generator_handle_token_recursive(gen, token->children[i]);
				}
				fprintf(gen->code, "\") ? %u : 0", token->length);
			}
			break;
		case S_TC2:
			switch (token->children[0]->type)
			{
				case T_ALPHALOW:
				case T_ALPHAUP:
				case T_DIGIT:
				case T_DOT:
					fprintf(gen->code, "%c", (gen->origtext + token->children[0]->offset)[0]);
					break;
				case T_BS:
					if ((gen->origtext + token->children[1]->offset)[0] == '"')
					{
						fprintf(gen->code, "\\\"");
					}
					else
					{
						fprintf(gen->code, "%c", generator_get_escaped_char((gen->origtext + token->children[1]->offset)[0]));
					}
					break;
				case S_TCG:
					generator_handle_token_recursive(gen, token->children[0]);
					break;
			}
			break;
	}
}
void generator_handle_token(PGENERATOR gen, token* t)
{
	size_t index;
	char c, c2;
	token* tmp;
	//print case label
	fprintf(gen->code, "%.*scase T_", gen->depth, TABS100);
	for (index = 0; index < t->children[0]->length; index++)
	{
		fprintf(gen->code, "%c", toupper(*(gen->origtext + t->children[0]->offset + index)));
	}
	fprintf(gen->code, ":");
	if (t->children[2]->type == S_TOKENSTATIC)
	{
		tmp = t->children[2];
		index = tmp->children[0]->type == T_GT ? 1 : 2;

		if (((tmp->children[index]->length == 1) && (gen->origtext + tmp->children[index]->offset)[0] != '.') || (tmp->children[index]->length == 2 && (gen->origtext + tmp->children[index]->offset)[0] == '\\'))
		{ //Special case for singe-char tokens (either with or without leading backspace)
			if ((gen->origtext + tmp->children[index]->offset)[0] == '\\')
			{
				c = (gen->origtext + tmp->children[index]->offset)[1];
				c2 = generator_get_escaped_char(c);
				if (c != c2 || c == '\\')
				{
					fprintf(gen->code, " return s->txt[s->off] == '\\%c' ? 1 : 0;\n", c);
				}
				else
				{
					fprintf(gen->code, " return s->txt[s->off] == '%c' ? 1 : 0;\n", c);
				}
			}
			else
			{
				c = (gen->origtext + tmp->children[index]->offset)[0];
				fprintf(gen->code, " return s->txt[s->off] == '%c' ? 1 : 0;\n", c);
			}
		}
		else
		{ //Normal handle for token-parsing
			fprintf(gen->code, "\n%.*s{\n", gen->depth, TABS100);
			gen->depth++;
			generator_handle_token_recursive(gen, tmp->children[index]);
			gen->depth--;
			fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
		}
	}
	else if (t->children[2]->type == S_TOKENRUNTIME)
	{
		tmp = t->children[2]->children[1];
		fprintf(gen->code, " return s->resolvers[%.*s](s);\n", tmp->length, gen->origtext + tmp->offset);
	}
}


token* generator_handle_statement_find_statement(PGENERATOR gen, const char* name, size_t len)
{
	size_t index, off;
	token* t;
	for (index = 0; index < gen->root->top; index++)
	{
		t = gen->root->children[index];
		switch (t->type)
		{
			case S_STATEMENT:
				off = t->children[0]->offset;
				if (str_partial_equals(gen->origtext + off, name, len))
				{
					return t;
				}
				break;
		}
	}
	return 0;
}
token* generator_handle_statement_find_token(PGENERATOR gen, const char* name, size_t len)
{
	size_t index, off;
	token* t;
	for (index = 0; index < gen->root->top; index++)
	{
		t = gen->root->children[index];
		switch (t->type)
		{
			case S_TOKEN:
				off = t->children[0]->offset;
				if (str_partial_equals(gen->origtext + off, name, len))
				{
					return t;
				}
				break;
		}
	}
	return 0;
}

void generator_handle_statement_START(PGENERATOR gen, token* token)
{
	size_t i;
	struct token* otherstmnt;
	switch (token->type)
	{
		case T_OR:
			fprintf(gen->code, " || ");
			break;
		case S_EXPRESSION:
		case S_EXPRESSION2:
			generator_handle_statement_START(gen, token->children[0]);
			break;
		case S_EXPL0:
			for (i = 0; i < token->top; i++)
			{
				generator_handle_statement_START(gen, token->children[i]);
			}
			break;
		case S_EXPL1:
			if (token->children[0]->type == T_CURLYO)
			{
				generator_handle_statement_START(gen, token->children[1]);
			}
			else
			{
				generator_handle_statement_START(gen, token->children[0]);
			}
			break;
		case S_EXPL2:
			if (token->children[0]->type == T_SQUAREO)
			{
				generator_handle_statement_START(gen, token->children[1]);
			}
			else
			{
				generator_handle_statement_START(gen, token->children[0]);
			}
			break;
		case S_EXPL3:
			if (token->children[0]->type == T_ROUNDO)
			{
				generator_handle_statement_START(gen, token->children[1]);
			}
			else if (token->children[0]->type == T_TOKENIDENT)
			{
				fprintf(gen->code, "token_scan(s, T_");
				for (i = 0; i < token->children[0]->length; i++)
				{
					fprintf(gen->code, "%c", toupper(*(gen->origtext + token->children[0]->offset + i)));
				}
				fprintf(gen->code, ")");
			}
			else
			{
				fprintf(gen->code, "(");
				otherstmnt = generator_handle_statement_find_statement(gen, gen->origtext + token->children[0]->offset, token->children[0]->length);
				if (otherstmnt == 0)
				{
					//ToDo: Add proper error reporting
					fprintf(stderr, "Missing matching STATEMENT for %.*s\n", token->children[0]->length, gen->origtext + token->children[0]->offset);
					break;
				}
				generator_handle_statement_START(gen, otherstmnt->children[2]);
				fprintf(gen->code, ")");
			}
			break;
	}
}
token* generator_handle_statement_EXEC_find_start(token* token)
{
	switch (token->type)
	{
		case S_EXPL3:
			if (token->children[0]->type == T_ROUNDO)
			{
				return generator_handle_statement_EXEC_find_start(token->children[1]);
			}
			else
			{
				return token->children[0];
			}
		case S_EXPL1:
		case S_EXPL2:
			if (token->top > 1)
			{
				return generator_handle_statement_EXEC_find_start(token->children[1]);
			}
		default:
			return generator_handle_statement_EXEC_find_start(token->children[0]);
	}
}

void generator_write_macro(FILE* f, const char* origtext, token* t)
{
	size_t i;
	if (t->type == T_TOKENIDENT)
	{
		fprintf(f, "T_");
		for (i = 0; i < t->length; i++)
		{
			fprintf(f, "%c", toupper(*(origtext + t->offset + i)));
		}
	}
	else if (t->type == T_STATEIDENT)
	{
		fprintf(f, "S_%.*s", t->length, origtext + t->offset);
	}
#if _DEBUG
	else
	{
		free((void*)~0); //On purpose so that it appears during missuse in debug sessions
	}
#endif
}
void generator_handle_statement_EXEC_write_start(PGENERATOR gen, token* t)
{
	if (t->type == T_TOKENIDENT)
	{
		fprintf(gen->code, "(len = token_scan(s, ");
		generator_write_macro(gen->code, gen->origtext, t);
		fprintf(gen->code, ")) > 0");
	}
	else if (t->type == T_STATEIDENT)
	{
		fprintf(gen->code, "%.*s_START(s)", t->length, gen->origtext + t->offset);
	}
#if _DEBUG
	else
	{
		free((void*)~0); //On purpose so that it appears during missuse in debug sessions
	}
#endif
}

void generator_handle_statement_EXEC_flattened_casing_errorlogging_recursive(PGENERATOR gen, token *flattened, size_t index, size_t *i, bool *start_printed, bool *or_required)
{
	size_t enclosure_counter = 0;
	for (; *i <= index; ++*i)
	{
		switch (flattened->children[*i]->type)
		{
			case T_CURLYO:
			case T_SQUAREO:
			case T_ROUNDO:
				if (*start_printed)
				{
					enclosure_counter++;
				}
				else
				{
					++*i;
					generator_handle_statement_EXEC_flattened_casing_errorlogging_recursive(gen, flattened, index, i, start_printed, or_required);
				}
				break;
			case T_OR:
				if (enclosure_counter == 0)
				{
					*start_printed = false;
				}
				break;
			case T_CURLYC:
			case T_SQUAREC:
			case T_ROUNDC:
				if (enclosure_counter == 0)
				{
					return;
				}
				else
				{
					enclosure_counter--;
				}
				break;
			case T_STATEIDENT:
			case T_TOKENIDENT:
				if (enclosure_counter == 0 && !*start_printed)
				{
					*start_printed = true;
					if (*or_required)
					{
						fprintf(gen->code, " \"' or '\" ");
					}
					else
					{
						*or_required = true;
					}
					generator_write_macro(gen->code, gen->origtext, flattened->children[*i]);
					fprintf(gen->code, "_STR");
				}
				break;
		}
	}
}
void generator_handle_statement_EXEC_flattened_casing_errorlogging(PGENERATOR gen, token *flattened, size_t index)
{
	size_t i = index == flattened->top ? index - 1 : index, enclosure_counter = 0;
	bool start_printed = false;
	bool flag;

	fprintf(gen->code, "%.*selse {\n", gen->depth, TABS100);
	gen->depth++;
	fprintf(gen->code, "%.*ss->log(s->data, \"Expected '\" ", gen->depth, TABS100);

	// Backtrack to T_OR start
	// `flag` is used in here to break out of the loop.
	flag = false;
	for (; i != ~0; i--)
	{
		switch (flattened->children[i]->type)
		{
			case T_CURLYO:
			case T_SQUAREO:
			case T_ROUNDO:
				if (enclosure_counter > 0)
				{
					enclosure_counter--;
				}
				else
				{
					flag = true;
					break;
				}
			case T_CURLYC:
			case T_SQUAREC:
			case T_ROUNDC:
				enclosure_counter++;
				break;
		}
		if (flag)
			break;
	}
	if (i == ~0)
	{ // We hit 0 but due to backtracking, we are now at ~0 :)
		i = 0; // Now we are at the correct index again
	}

	// Print out moving towards our original index the different
	// possibilities.
	// `flag` is used in here to check if the or should be printed.
	flag = false;
	generator_handle_statement_EXEC_flattened_casing_errorlogging_recursive(gen, flattened, index, &i, &start_printed, &flag);
	fprintf(gen->code, " \"'\", s->line, s->col, s->off, token_next_type(s));\n");
	gen->depth--;
	fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
}
void generator_handle_statement_EXEC_flattened_casing_forward_condition_scan(PGENERATOR gen, token *flattened, size_t index)
{
	size_t enclosure_counter = 0;
	bool start_printed = false;
	bool initial_printed = false;

	for (; index != flattened->top; index++)
	{
		switch (flattened->children[index]->type)
		{
			case T_CURLYO:
			case T_SQUAREO:
			case T_ROUNDO:
				// Add one to enclosure counter so we actually leave when we have to
				enclosure_counter++;
				break;
			case T_CURLYC:
			case T_SQUAREC:
			case T_ROUNDC:
				enclosure_counter--;
				if (enclosure_counter == 0)
				{ // We hit our outter scope, so we are done T_T
					return;
				}
				break;
			case T_OR:
				start_printed = false;
				break;
			case T_STATEIDENT:
			case T_TOKENIDENT:
				if (start_printed)
				{ // No need to do anything, our start already appeared
					continue;
				}
				if (initial_printed)
				{
					fprintf(gen->code, " || ");
				}
				else
				{
					initial_printed = true;
				}
				generator_handle_statement_EXEC_write_start(gen, flattened->children[index]);
				start_printed = true;
				break;
		}
	}
}
bool generator_tmode__notoken(PGENERATOR gen, token* t)
{
	size_t i;
	token *def = NULL, *tmp;
	for (i = 0; i < gen->root->top; i++)
	{
		tmp = gen->root->children[i];
		if (tmp->type == S_TOKEN && tmp->length == t->length && str_partial_equals(gen->origtext + tmp->offset, gen->origtext + t->offset, t->length))
		{
			def = tmp;
			break;
		}
	}
	if (def == NULL)
	{
		return false;
	}
	for (i = 0; i < def->top; i++)
	{
		tmp = def->children[i];
		if (tmp->type == S_TMODE)
		{
			if (tmp->children[0]->type == T_NOTOKEN)
			{
				return true;
			}
		}
	}
	return false;
}
void generator_handle_statement_EXEC_flattened_casing(PGENERATOR gen, token *flattened, size_t *index, char parenttype)
{
	token *t, *tla;
	short elsemode = ELSEMODE_INACTIVE;
	for (; *index < flattened->top; ++*index)
	{
		t = flattened->children[*index];
		tla = 1 + *index < flattened->top ? flattened->children[1 + *index] : NULL;
		switch (t->type)
		{
			case T_CURLYO:
				fprintf(gen->code, parenttype == T_OR || elsemode == ELSEMODE_PREPARED ? "%.*selse if (" : "%.*sif (", gen->depth, TABS100);
				generator_handle_statement_EXEC_flattened_casing_forward_condition_scan(gen, flattened, *index);
				fprintf(gen->code, ") {\n");
				gen->depth++;
				fprintf(gen->code, "%.*swhile (true) {\n", gen->depth, TABS100);
				gen->depth++;
				++*index;
				generator_handle_statement_EXEC_flattened_casing(gen, flattened, index, T_CURLYO);
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				break;
			case T_CURLYC:
				if (elsemode == ELSEMODE_ACTIVE)
				{
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
				if (parenttype != T_STATEIDENT && parenttype != T_TOKENIDENT)
				{
					fprintf(gen->code, "%.*selse { break; }\n", gen->depth, TABS100);
				}
				return;

			case T_SQUAREO:
				fprintf(gen->code, parenttype == T_OR || elsemode == ELSEMODE_PREPARED ? "%.*selse if (" : "%.*sif (", gen->depth, TABS100);
				gen->depth++;
				generator_handle_statement_EXEC_flattened_casing_forward_condition_scan(gen, flattened, *index);
				fprintf(gen->code, ") {\n");
				++*index;
				generator_handle_statement_EXEC_flattened_casing(gen, flattened, index, T_SQUAREO);
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				break;
			case T_SQUAREC:
				if (elsemode == ELSEMODE_ACTIVE)
				{
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
				return;

			case T_ROUNDO:
				++*index;
				generator_handle_statement_EXEC_flattened_casing(gen, flattened, index, T_ROUNDO);
				break;
			case T_ROUNDC:
				if (elsemode == ELSEMODE_ACTIVE)
				{
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
				if (parenttype != T_STATEIDENT && parenttype != T_TOKENIDENT)
				{
					generator_handle_statement_EXEC_flattened_casing_errorlogging(gen, flattened, (*index) - 1);
				}
				return;

			case T_OR:
				if (parenttype == T_STATEIDENT || parenttype == T_TOKENIDENT)
				{
					return;
				}
				if (elsemode == ELSEMODE_ACTIVE)
				{
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
				elsemode = ELSEMODE_PREPARED;
				break;
			case T_STATEIDENT:
			case T_TOKENIDENT:
				fprintf(gen->code, elsemode == ELSEMODE_PREPARED ? "%.*selse if (" : "%.*sif (", gen->depth, TABS100);
				generator_handle_statement_EXEC_write_start(gen, t);
				fprintf(gen->code, ") {\n");
				gen->depth++;

				if (t->type == T_TOKENIDENT)
				{
					if (!generator_tmode__notoken(gen, t))
					{
						fprintf(gen->code, "%.*s" "t = token_gen(s, ", gen->depth, TABS100);
						generator_write_macro(gen->code, gen->origtext, t);
						fprintf(gen->code, ");" "\n"
							"%.*s" "t->length = len;" "\n"
							"%.*s" "token_skip(s, len);" "\n"
							"%.*s" "token_push(thistoken, t);" "\n",
							gen->depth, TABS100,
							gen->depth, TABS100,
							gen->depth, TABS100
						);
					}
				}
				else //if (t->type == T_STATEIDENT) implicit
				{
					fprintf(gen->code, "%.*s%.*s(s, thistoken);\n", gen->depth, TABS100, t->length, gen->origtext + t->offset);
				}
				if (elsemode == ELSEMODE_PREPARED)
				{
					elsemode = ELSEMODE_ACTIVE;
				}
				else if (parenttype != T_STATEIDENT && parenttype != T_TOKENIDENT)
				{
					++*index;
					generator_handle_statement_EXEC_flattened_casing(gen, flattened, index, t->type);
					gen->depth--;
					fflush(gen->code);
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
					if (*index < flattened->top)
					{
						tla = flattened->children[*index];
						if (tla->type == T_CURLYC)
						{
							fprintf(gen->code, "%.*selse { break; }\n", gen->depth, TABS100);
						}
						else if (tla->type == T_ROUNDC && ((*index) + 1 >= flattened->top || flattened->children[(*index) + 1]->type != T_OR))
						{
							gen->depth--;
							fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
							generator_handle_statement_EXEC_flattened_casing_errorlogging(gen, flattened, (*index) - 1);
						}
						else if (tla->type == T_OR)
						{
							--*index;
						}
						else if ((*index) + 1 >= flattened->top || flattened->children[(*index) + 1]->type != T_OR)
						{
							fprintf(gen->code, "%.*selse {\n", gen->depth, TABS100);
							gen->depth++;
							fprintf(gen->code, "%.*ss->log(s->data, \"Expected '\" ", gen->depth, TABS100);
							generator_write_macro(gen->code, gen->origtext, t);
							fprintf(gen->code, "_STR");
							fprintf(gen->code, " \"'\", s->line, s->col, s->off, token_next_type(s));\n");
							gen->depth--;
							fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
						}
						if (parenttype != T__INVALID && (tla->type == T_CURLYC || tla->type == T_ROUNDC || tla->type == T_SQUAREC))
						{
							return;
						}
					}
				}
				else
				{
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
				break;
			default:
				break;
		}
		fflush(gen->code);
	}
	if (elsemode == ELSEMODE_ACTIVE)
	{
		gen->depth--;
		fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
	}
	if (parenttype == T__INVALID)
	{
		generator_handle_statement_EXEC_flattened_casing_errorlogging(gen, flattened, flattened->top - 1);
	}
}
void generator_handle_statement_EXEC_flattened(PGENERATOR gen, token* input)
{
	token *flattened;
	size_t i = 0;

	//Generate temporary token for usage in token_flatten
	flattened = token_gen(NULL, T__INVALID);
	token_flatten(flattened, input);

	generator_handle_statement_EXEC_flattened_casing(gen, flattened, &i, T__INVALID);

	//Do not use token_del for deletion of the temporary token!
	//token_flatten is not creating copies and token_del would
	//thus delete those.
	free(flattened->children);
	free(flattened);
}

void generator_handle_statement(PGENERATOR gen, token* token)
{
	fprintf(gen->code, "bool %.*s_START(scan* s) { return ", token->children[0]->length, gen->origtext + token->children[0]->offset);
	generator_handle_statement_START(gen, token->children[2]);
	fprintf(gen->code, "; }\nvoid %.*s(scan* s, token* parent) {" "\n"
		"\t" "token* thistoken = token_gen(s, S_%.*s);" "\n"
		"\t" "token* t;" "\n"
		"\t" "size_t len;" "\n",
		token->children[0]->length, gen->origtext + token->children[0]->offset,
		token->children[0]->length, gen->origtext + token->children[0]->offset
	);
	gen->depth = 1;
	generator_handle_statement_EXEC_flattened(gen, token->children[2]);
	//generator_handle_statement_EXEC(gen, token->children[2], false, false);
	fprintf(gen->code, "\t" "thistoken->length = s->off - thistoken->offset;" "\n"
		"\t" "token_push(parent, thistoken);" "\n"
		"}\n"
	);
}

void generate(PGENERATOR gen)
{
	size_t index;
	token* token;
	//Apply Annotations
	for (index = 0; index < gen->root->top; index++)
	{
		token = gen->root->children[index];
		if (token->type == S_ANNOTATION)
		{
			generator_handle_annotation(gen, token);
		}
		else
		{
			break;
		}
	}

	//Handle Header-Section
	{
		//Create the different macros
		fprintf(gen->header, "#pragma once\n"
			"#include <stdbool.h>" "\n"
			"#include <stdlib.h>" "\n"
			"\n"
			"#ifndef TOKEN_INITIALSIZE" "\n"
			"#define TOKEN_INITIALSIZE 25" "\n"
			"#endif" "\n"
			"\n"
			"#define T__INVALID 0" "\n"
			"#define T__FIRST 1" "\n"
		);
		gen->depth = 1;
		for (index = 0; index < gen->root->top; index++)
		{
			token = gen->root->children[index];
			switch (token->type)
			{
				case S_TOKEN:
					generator_create_macro(gen, token);
					break;
			}
		}
		fprintf(gen->header, "#define T__LAST %u" "\n", gen->depth - 1);
		for (index = 0; index < gen->root->top; index++)
		{
			token = gen->root->children[index];
			switch (token->type)
			{
				case S_STATEMENT:
					generator_create_macro(gen, token);
					break;
			}
		}

		//Create the method-headers
		fprintf(gen->header, "#ifdef __cplusplus" "\n"
			"extern \"C\" {" "\n"
			"#endif" "\n\n"
			"typedef void(*logcallback)(void * data, const char * m, size_t l, size_t c, size_t o, char gottype);" "\n"
			"typedef size_t(*token_scan_resolver)(struct scan * s);" "\n"
			"typedef struct scan {" "\n"
			"	size_t line;" "\n"
			"	size_t col;" "\n"
			"	size_t off;" "\n"
			"	const char* txt;" "\n"
			"	logcallback log;" "\n"
			"	token_scan_resolver* resolvers;" "\n"
			"	void* data;" "\n"
			"} scan;" "\n"
			"typedef struct token {" "\n"
			"	size_t line;" "\n"
			"	size_t column;" "\n"
			"	size_t offset;" "\n"
			"	size_t length;" "\n"
			"	char type;" "\n"
			"	size_t size;" "\n"
			"	size_t top;" "\n"
			"	struct token** children;" "\n"
			"} token;" "\n"
			"bool str_equals(const char* strin, const char* otherstr);" "\n"
			"token* token_gen(scan *s, char type);" "\n"
			"void token_del(token* ptr);" "\n"
			"void token_grow(token* ptr);" "\n"
			"void token_push(token* ptr, token* t);" "\n"
			"void token_skip(scan* s, size_t skip);" "\n"
			"size_t token_scan(scan* s, char expected);" "\n"
			"void token_minimize(token*);" "\n"
			"char token_next_type(scan* s);" "\n"
			"\n"
		);
		for (index = 0; index < gen->root->top; index++)
		{
			token = gen->root->children[index];
			switch (token->type)
			{
				case S_STATEMENT:
					fprintf(gen->header, "bool %.*s_START(scan*);\n", token->children[0]->length, gen->origtext + token->children[0]->offset);
					fprintf(gen->header, "void %.*s(scan*, token*);\n", token->children[0]->length, gen->origtext + token->children[0]->offset);
					break;
			}
		}
	}
	fprintf(gen->header, "#ifdef __cplusplus\n}\n#endif");

	//Handle Code-Section
	{
		if (gen->casesensitive)
		{
			fprintf(gen->code, "#include \"%s.h\"\n#include <malloc.h>\n\n"
				"bool str_equals(const char* strin, const char* otherstr) {" "\n"
				"	int i;" "\n"
				"	for (i = 0; strin[i] != '\\0' && otherstr[i] != '\\0' && strin[i] == otherstr[i]; i++);" "\n"
				"	return otherstr[i] == '\\0';" "\n"
				"}" "\n", gen->fname);
		}
		else
		{
			fprintf(gen->code, "#include \"%s.h\"\n#include <malloc.h>\n#include <ctypes.h>\n\n"
				"bool str_equals(const char* strin, const char* otherstr) {" "\n"
				"	int i;" "\n"
				"	for (i = 0; strin[i] != '\\0' && otherstr[i] != '\\0' && toupper(strin[i]) == toupper(otherstr[i]); i++);" "\n"
				"	return otherstr[i] == '\\0';" "\n"
				"}" "\n", gen->fname);
		}
		fprintf(gen->code, "token* token_gen(scan *s, char type) {" "\n"
			"	token* ptr = malloc(sizeof(token));" "\n"
			"	ptr->size = TOKEN_INITIALSIZE;" "\n"
			"	ptr->children = malloc(sizeof(token*) * ptr->size);" "\n"
			"	ptr->top = 0;" "\n"
			"	ptr->type = type;" "\n"
			"	if (s != 0) {" "\n"
			"		ptr->line = s->line;" "\n"
			"		ptr->column = s->col;" "\n"
			"		ptr->offset = s->off;" "\n"
			"	}" "\n"
			"	return ptr;" "\n"
			"}" "\n"
			"void token_del(token* ptr) {" "\n"
			"	int i;" "\n"
			"	for (i = 0; i < ptr->top; i++) { token_del(ptr->children[i]); }" "\n"
			"	free(ptr->children);" "\n"
			"	free(ptr);" "\n"
			"}" "\n"
			"void token_grow(token* ptr) {" "\n"
			"	token** tmp;" "\n"
			"	ptr->size = ptr->size * 2;" "\n"
			"	tmp = realloc(ptr->children, sizeof(token*) * ptr->size);" "\n"
			"	if (tmp == 0) {" "\n"
			"		exit(1);" "\n"
			"	}" "\n"
			"	ptr->children = tmp;" "\n"
			"}" "\n"
			"void token_push(token* ptr, token* t) {" "\n"
			"	if (ptr->top == ptr->size) { token_grow(ptr); }" "\n"
			"	ptr->children[ptr->top] = t;" "\n"
			"	ptr->top++;" "\n"
			"}" "\n"
			"void token_minimize(token* root) {" "\n"
			"	token* tmp;" "\n"
			"	int i;" "\n"
			"	for (i = 0; i < root->top; i++) {" "\n"
			"		while (root->children[i]->top == 1) {" "\n"
			"			tmp = root->children[i];" "\n"
			"			root->children[i] = tmp->children[0];" "\n"
			"			tmp->top = 0;" "\n"
			"			token_del(tmp);" "\n"
			"		}" "\n"
			"	}" "\n"
			"	for (i = 0; i < root->top; i++) {" "\n"
			"		token_minimize(root->children[i]);" "\n"
			"	}" "\n"
			"}" "\n"
			"char token_next_type(scan* s) {" "\n"
			"	for (int i = T__FIRST; i < T__LAST; i++) {" "\n"
			"		if (token_scan(s, i) > 0) return i;" "\n"
			"	}" "\n"
			"	return T__INVALID;" "\n"
			"}" "\n"

		);

		generator_write_token_skip_method(gen);
		fprintf(gen->code, "size_t token_scan(scan* s, char expected) {" "\n"
			"	int i = 0;" "\n"
			"	switch(expected) {" "\n"
		);
		gen->depth = 2;
		for (index = 0; index < gen->root->top; index++)
		{
			token = gen->root->children[index];
			switch (token->type)
			{
				case S_TOKEN:
					generator_handle_token(gen, token);
					break;
			}
		}
		fprintf(gen->code, "\t}\n\treturn 0;\n}\n");

		for (index = 0; index < gen->root->top; index++)
		{
			token = gen->root->children[index];
			switch (token->type)
			{
				case S_STATEMENT:
					generator_handle_statement(gen, token);
					break;
			}
		}
	}
}
void generator_validate_token_tree(PGENERATOR gen, token* t, bool * success)
{
	size_t i;
	token* tmp;
	bool hasblockcommentstart = false;
	bool hasblockcommentend = false;
	if (t->type == T__INVALID && t->top == 0)
	{
		fprintf(stderr, "Token provided is invalid and empty.\n");
		*success = false;
		return;
	}
	if (t->type == T__INVALID && t->children[0]->type == S_EBNF)
	{
		t = t->children[0];
	}
	for (i = 0; i < t->top; i++)
	{
		tmp = t->children[i];
		if (tmp->type == S_ANNOTATION)
		{
			switch (tmp->children[1]->type)
			{
				case S_BLOCKCOMMENTSTART:
					hasblockcommentstart = true;
					break;
				case S_BLOCKCOMMENTEND:
					hasblockcommentend = true;
					break;
			}
		}
		else if (tmp->type == S_STATEMENT && tmp->children[0]->length == 4 && str_partial_equals(gen->origtext + tmp->children[0]->offset, "FILE", 4))
		{
			fprintf(stderr, "Statement '%.*s' requires a different name due to conflicts with FILE struct. Line %u, Column %u\n", tmp->children[0]->length, gen->origtext + tmp->children[0]->offset, tmp->children[0]->line, tmp->children[0]->column);
			*success = false;
		}
	}
	if (hasblockcommentstart != hasblockcommentend)
	{
		if (hasblockcommentstart)
		{
			fprintf(stderr, "Missing annotation for blockcommentend.\n");
			*success = false;
		}
		else
		{
			fprintf(stderr, "Missing annotation for blockcommentstart.\n");
			*success = false;
		}
	}
	generator_validate_token_tree_inner(gen, t, success);
}

void generator_validate_token_tree_inner(PGENERATOR gen, token* t, bool * success)
{
	size_t i;
	token* tmp;
	switch (t->type)
	{
		case T_STATEIDENT:
			tmp = generator_handle_statement_find_statement(gen, gen->origtext + t->offset, t->length);
			if (tmp == 0)
			{
				fprintf(stderr, "Statement '%.*s' cannot be found. Line %u, Column %u\n", t->length, gen->origtext + t->offset, t->line, t->column);
				*success = false;
			}
			break;
		case T_TOKENIDENT:
			tmp = generator_handle_statement_find_token(gen, gen->origtext + t->offset, t->length);
			if (tmp == 0)
			{
				fprintf(stderr, "Token '%.*s' cannot be found. Line %u, Column %u\n", t->length, gen->origtext + t->offset, t->line, t->column);
				*success = false;
			}
			break;
		default:
			for (i = 0; i < t->top; i++)
			{
				generator_validate_token_tree_inner(gen, t->children[i], success);
			}
			break;
	}
}