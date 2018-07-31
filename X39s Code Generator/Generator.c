#include "Generator.h"
#include <string.h>
#include <ctype.h>

#define TABS10 "\t\t\t\t\t\t\t\t\t\t"
#define TABS50 TABS10 TABS10 TABS10 TABS10 TABS10 
#define TABS100 TABS50 TABS50


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
	gen_stmnt_helper * ptr;
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

PGENERATOR generator_create(FILE* code, FILE* header, const char* fname, token* r, const char* origtext)
{
	PGENERATOR gen = malloc(sizeof(generator));
	memset(gen, 0, sizeof(generator));
	gen->code = code;
	gen->header = header;
	gen->origtext = origtext;
	gen->fname = fname;
	gen->root = r;
	gen->linecommentstart = malloc(sizeof(char) * 3);
	strcpy(gen->linecommentstart, "//");
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
	free(gen->linecommentstart);
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
			free(gen->linecommentstart);
			gen->linecommentstart = malloc(anno->children[1]->children[1]->length + 1);
			strncpy(gen->linecommentstart, gen->origtext + anno->children[1]->children[1]->offset, anno->children[1]->children[1]->length);
			gen->linecommentstart[anno->children[1]->children[1]->length] = '\0';
			break;
	}
}
void generator_write_token_skip_method(PGENERATOR gen)
{
	size_t i, j;
	char c;
	bool nlAvailable = false;
	bool isEscaped;
	fprintf(gen->code, "void token_skip(scan* s, size_t skip) {" "\n"
		"\tbool commentmode = false;" "\n"
		"\ts->off += skip;" "\n"
		"\ts->col += skip;" "\n"
		"\twhile (s->txt[s->off] != '\\0') {" "\n"
		"\t\tif (commentmode) {" "\n"
		"\t\t\ts->off++;" "\n"
		"\t\t\ts->col++;" "\n"
		"\t\t\tif (s->txt[s->off] == '\\n') {" "\n"
		"\t\t\t\tcommentmode = false;" "\n"
		"\t\t\t\ts->line++;" "\n"
		"\t\t\t\ts->col = 0;" "\n"
		"\t\t\t}" "\n"
		"\t\t\tcontinue;" "\n"
		"\t\t}" "\n"
		"\t\tswitch (s->txt[s->off]) {" "\n"
	);

	for (i = 0; (c = gen->skip_characters[i]) != '\0'; i++)
	{
		if (isEscaped = c == '\\')
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
	fprintf(gen->code, "\t\t\tcase '%c': ", gen->linecommentstart[gen->linecommentstart[0] == '\\' ? 1 : 0]);
	fprintf(gen->code, "if (");
	nlAvailable = false; //cries "rape"
	for (i = gen->linecommentstart[0] == '\\' ? 2 : 1, j = 1; (c = gen->linecommentstart[i]) != '\0'; i++)
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
	}
	fprintf(gen->code, ") { commentmode = true; break; }\n");
	fprintf(gen->code, "\t\t\tdefault: return;\n\t\t}\n\t}\n}\n");
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
				fprintf(gen->code, "if(!(");
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
				fprintf(gen->code, "if(!(");
				for (i = 1; i < token->top - 2; i++)
				{
					if (i > 1)
					{
						fprintf(gen->code, " || ");
					}
					generator_handle_token_recursive(gen, token->children[i]);
				}
				fprintf(gen->code, ")) return 0;\n");
				fprintf(gen->code, "%.*sif(s->txt[i + s->off] == '\\\\' && s->txt[i + s->off + 1] != '\\0') { i++; }\n", gen->depth, TABS100);
				fprintf(gen->code, "%.*si++;\n", gen->depth, TABS100);
				fprintf(gen->code, "%.*s", gen->depth, TABS100);
				fprintf(gen->code, "for(; ");
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
					fprintf(gen->code, "%c", generator_get_escaped_char((gen->origtext + token->children[1]->offset)[0]));
					break;
				case S_TCG:
					generator_handle_token_recursive(gen, token->children[0]);
					break;
			}
			break;
	}
}
void generator_handle_token(PGENERATOR gen, token* token)
{
	size_t index;
	char c, c2;
	//print case label
	fprintf(gen->code, "%.*scase T_", gen->depth, TABS100);
	for (index = 0; index < token->children[0]->length; index++)
	{
		fprintf(gen->code, "%c", toupper(*(gen->origtext + token->children[0]->offset + index)));
	}
	fprintf(gen->code, ":");
	index = token->children[2]->type == T_GT ? 3 : 4;
	
	if (token->children[index]->length == 1 && (gen->origtext + token->children[index]->offset)[0] != '.' || token->children[index]->length == 2 && (gen->origtext + token->children[index]->offset)[0] == '\\')
	{ //Special case for singe-char tokens (either with or without leading backspace)
		if ((gen->origtext + token->children[index]->offset)[0] == '\\')
		{
			c = (gen->origtext + token->children[index]->offset)[1];
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
			c = (gen->origtext + token->children[index]->offset)[0];
			fprintf(gen->code, " return s->txt[s->off] == '%c' ? 1 : 0;\n", c);
		}
	}
	else
	{ //Normal handle for token-parsing
		fprintf(gen->code, "\n%.*s{\n", gen->depth, TABS100);
		gen->depth++;
		generator_handle_token_recursive(gen, token->children[index]);
		gen->depth--;
		fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
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
			else if(token->children[0]->type == T_TOKENIDENT)
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
					sprintf(stderr, "Missing matching STATEMENT for %.*s", token->children[0]->length, gen->origtext + token->children[0]->offset);
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
	size_t i;
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
	size_t i;
	if (t->type == T_TOKENIDENT)
	{
		fprintf(gen->code, "(len = token_scan(s, ");
		generator_write_macro(gen->code, gen->origtext, t);
		fprintf(gen->code, ")) > 0");
	}
	else if(t->type == T_STATEIDENT)
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
void generator_handle_statement_EXEC_get_starts(PGENERATOR gen, token* t, pgen_stmnt_helper h, bool allowsubhelpers)
{
	size_t i;
	struct token* othertoken;
	pgen_stmnt_helper h2;
	switch (t->type)
	{
		case S_EXPRESSION:
		case S_EXPRESSION2:
			generator_handle_statement_EXEC_get_starts(gen, t->children[0], h, allowsubhelpers);
			break;
		case S_EXPL0:
			if (t->top > 1)
			{
				if (allowsubhelpers)
				{
					h2 = gen_stmnt_helper_create();
					h2->thistoken = t;
					gen_stmnt_helper_push_helper(h, h2);
					for (i = 0; i < t->top; i++)
					{
						generator_handle_statement_EXEC_get_starts(gen, t->children[i], h2, allowsubhelpers);
					}
				}
				else
				{
					for (i = 0; i < t->top; i++)
					{
						generator_handle_statement_EXEC_get_starts(gen, t->children[i], h, allowsubhelpers);
					}
				}
			}
			else
			{
				generator_handle_statement_EXEC_get_starts(gen, t->children[0], h, allowsubhelpers);
			}
			break;
		case S_EXPL1:
			generator_handle_statement_EXEC_get_starts(gen, t->children[t->top > 1 ? 1 : 0], h, allowsubhelpers);
			break;
		case S_EXPL2:
			generator_handle_statement_EXEC_get_starts(gen, t->children[t->top > 1 ? 1 : 0], h, allowsubhelpers);
			break;
		case S_EXPL3:
			switch (t->children[0]->type)
			{
				case T_ROUNDO:
					generator_handle_statement_EXEC_get_starts(gen, t->children[1], h, allowsubhelpers);
					break;
				case T_TOKENIDENT:
				case T_STATEIDENT:
					gen_stmnt_helper_push_token(h, t->children[0]);
					break;
			}
			break;
	}
}
void generator_handle_statement_EXEC_EXPL0_print(PGENERATOR gen, token* t, bool expl0_or_format, bool expl0_prevent_else_log_printout)
{
	size_t i, j, k;
	struct token* othertoken;
	pgen_stmnt_helper helper;
	for (i = 0; i < t->top; i++)
	{
		if (t->children[i]->type == T_OR)
		{
			continue;
		}
		helper = gen_stmnt_helper_create();
		generator_handle_statement_EXEC_get_starts(gen, t->children[i], helper, true);
		if (!expl0_or_format)
		{
			fprintf(gen->code, "%.*s", gen->depth, TABS100);
			expl0_or_format = true;
		}
		if (i > 0)
		{
			fprintf(gen->code, "else ");
		}
		if (helper->tokens_top > 0)
		{
			for (j = 0; j < helper->tokens_top; j++)
			{
				if (!expl0_or_format)
				{
					fprintf(gen->code, "%.*s", gen->depth, TABS100);
				}
				if (i == 0 && j > 0)
				{
					fprintf(gen->code, "else ");
				}
				fprintf(gen->code, "if (");
				generator_handle_statement_EXEC_write_start(gen, helper->tokens[j]);
				fprintf(gen->code, ") {\n");
				gen->depth++;
				gen->helper_is_first_after_EXP_start = true;
				generator_handle_statement_EXEC(gen, t->children[i], expl0_or_format, expl0_prevent_else_log_printout);
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
			}
		}
		else //if (helper->helpers_top > 0) implicit
		{
			for (j = 0; j < helper->helpers_top; j++)
			{
				//fprintf(gen->code, "%.*s", gen->depth, TABS100);
				//if (i > 0)
				//{
				//	fprintf(gen->code, "else ");
				//}
				//fprintf(gen->code, "if (");
				//generator_handle_statement_EXEC_write_start(gen, helper->helpers[j]->thistoken);
				//gen->depth++;
				generator_handle_statement_EXEC(gen, helper->helpers[j]->thistoken, expl0_or_format, expl0_prevent_else_log_printout);
				//gen->depth--;
				//fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
			}
		}
		gen_stmnt_helper_destroy(helper);
		expl0_or_format = false;
	}
}
void generator_handle_statement_EXEC(PGENERATOR gen, token* t, bool expl0_or_format, bool expl0_prevent_else_log_printout)
{
	size_t i, j;
	struct token* othertoken;
	pgen_stmnt_helper helper;
	bool flag;
	switch (t->type)
	{
		case S_EXPRESSION:
		case S_EXPRESSION2:
			for (i = 0; i < t->top; i++)
			{
				generator_handle_statement_EXEC(gen, t->children[i], expl0_or_format, expl0_prevent_else_log_printout);
				fflush(gen->code);
			}
			break;
		case S_EXPL0:
			if (expl0_prevent_else_log_printout)
			{
				generator_handle_statement_EXEC_EXPL0_print(gen, t, expl0_or_format, expl0_prevent_else_log_printout);
			}
			else
			{
				expl0_prevent_else_log_printout = true;
				generator_handle_statement_EXEC_EXPL0_print(gen, t, expl0_or_format, expl0_prevent_else_log_printout);
				fprintf(gen->code, "%.*selse {\n", gen->depth, TABS100);
				gen->depth++;
				fprintf(gen->code, "%.*ss->log(\"Expected '\" ", gen->depth, TABS100);
				for (i = 0; i < t->top; i++)
				{
					if (t->children[i]->type == T_OR)
					{
						continue;
					}
					helper = gen_stmnt_helper_create();
					generator_handle_statement_EXEC_get_starts(gen, t->children[i], helper, false);
					for (j = 0; j < helper->tokens_top; j++)
					{
						if (i > 0 || j > 0)
						{
							fprintf(gen->code, " \"' or '\" ");
						}
						generator_write_macro(gen->code, gen->origtext, helper->tokens[j]);
						fprintf(gen->code, "_STR");
					}
					gen_stmnt_helper_destroy(helper);
				}
				fprintf(gen->code, " \"'\", s->line, s->col, s->off, token_next_type(s));\n");
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				expl0_prevent_else_log_printout = false;
			}
			break;
		case S_EXPL1:
			if (t->top > 1)
			{
				fprintf(gen->code, "%.*swhile (true) {\n", gen->depth, TABS100);
				gen->depth++;
				generator_handle_statement_EXEC(gen, t->children[1], false, true);
				fprintf(gen->code, "%.*selse { break; }\n", gen->depth, TABS100);
				gen->depth--;
				fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
			}
			else
			{
				generator_handle_statement_EXEC(gen, t->children[0], false, expl0_prevent_else_log_printout);
			}
			break;
		case S_EXPL2:
			generator_handle_statement_EXEC(gen, t->children[t->top > 1 ? 1 : 0], false, expl0_prevent_else_log_printout);
			break;
		case S_EXPL3:
			if (t->top > 1)
			{
				generator_handle_statement_EXEC(gen, t->children[1], false, expl0_prevent_else_log_printout);
			}
			else
			{
				if ((flag = gen->helper_is_first_after_EXP_start))
				{
					gen->helper_is_first_after_EXP_start = false;
				}
				else
				{
					fprintf(gen->code, "%.*sif (", gen->depth, TABS100);
					generator_handle_statement_EXEC_write_start(gen, t->children[0]);
					fprintf(gen->code, ") {\n");
					gen->depth++;
				}

				if (t->children[0]->type == T_TOKENIDENT)
				{
					fprintf(gen->code, "%.*s" "t = token_gen(s, ", gen->depth, TABS100);
					generator_write_macro(gen->code, gen->origtext, t->children[0]);
					fprintf(gen->code, ");" "\n"
						"%.*s" "t->length = len;" "\n"
						"%.*s" "token_skip(s, len);" "\n"
						"%.*s" "token_push(thistoken, t);" "\n",
						gen->depth, TABS100,
						gen->depth, TABS100,
						gen->depth, TABS100
					);
				}
				else //if (t->children[0]->type == T_STATEIDENT) implicit
				{
					fprintf(gen->code, "%.*s%.*s(s, thistoken);\n", gen->depth, TABS100, t->children[0]->length, gen->origtext + t->children[0]->offset);
				}

				if (!flag)
				{
					gen->depth--;
					fprintf(gen->code, "%.*s} else {\n", gen->depth, TABS100);
					gen->depth++;
					fprintf(gen->code, "%.*ss->log(\"Expected '\" ", gen->depth, TABS100);
					generator_write_macro(gen->code, gen->origtext, t->children[0]);
					fprintf(gen->code, "_STR \"'\", s->line, s->col, s->off, token_next_type(s));\n");
					gen->depth--;
					fprintf(gen->code, "%.*s}\n", gen->depth, TABS100);
				}
			}
			break;
	}
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
	generator_handle_statement_EXEC(gen, token->children[2], false, false);
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
		fprintf(gen->header, "\n"
			"typedef void(*logcallback)(const char* m, size_t l, size_t c, size_t o, char gottype);" "\n"
			"typedef struct {" "\n"
			"	size_t line;" "\n"
			"	size_t col;" "\n"
			"	size_t off;" "\n"
			"	const char* txt;" "\n"
			"	logcallback log;" "\n"
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
			"	ptr->line = s->line;" "\n"
			"	ptr->column = s->col;" "\n"
			"	ptr->offset = s->off;" "\n"
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
		fprintf(gen->code, "\t}\n}\n");

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