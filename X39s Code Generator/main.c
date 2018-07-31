#include "Parser.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Generator.h"


void treeprint(scan* s, token* t, int depth)
{
	unsigned int i;
	printf("%.*s", depth * 2,
		"                                                  " //50
		"                                                  " //100
		"                                                  " //150
		"                                                  " //200
		"                                                  " //250
		"                                                  " //300
		"                                                  " //350
		"                                                  " //400
	);
	switch (t->type)
	{
		case T_TOKENIDENT: printf("TOKEN: TOKENIDENT"); break;
		case T_STATEIDENT: printf("TOKEN: STATEIDENT"); break;
		case T_STMTSEP: printf("TOKEN: STMTSEP"); break;
		case T_ANYTEXT: printf("TOKEN: ANYTEXT"); break;
		case T_ANNOTATION: printf("TOKEN: ANNOTATION"); break;
		case T_SKIP: printf("TOKEN: SKIP"); break;
		case T_CASESENSITIVE: printf("TOKEN: CASESENSITIVE"); break;
		case T_LINECOMMENTSTART: printf("TOKEN: LINECOMMENTSTART"); break;
		case T_OR: printf("TOKEN: OR"); break;
		case T_CURLYO: printf("TOKEN: CURLYO"); break;
		case T_CURLYC: printf("TOKEN: CURLYC"); break;
		case T_ROUNDO: printf("TOKEN: ROUNDO"); break;
		case T_ROUNDC: printf("TOKEN: ROUNDC"); break;
		case T_SQUAREO: printf("TOKEN: SQUAREO"); break;
		case T_SQUAREC: printf("TOKEN: SQUAREC"); break;
		case T_TRUE: printf("TOKEN: TRUE"); break;
		case T_FALSE: printf("TOKEN: FALSE"); break;
		case T_SC: printf("TOKEN: SC"); break;
		case T_LT: printf("TOKEN: LT"); break;
		case T_GT: printf("TOKEN: GT"); break;
		case T_MODMAX: printf("TOKEN: MODMAX"); break;
		case T_COLON: printf("TOKEN: COLON"); break;
		case T_NUMBER: printf("TOKEN: NUMBER"); break;
		case T_ALPHALOW: printf("TOKEN: ALPHALOW"); break;
		case T_ALPHAUP: printf("TOKEN: ALPHAUP"); break;
		case T_MINUS: printf("TOKEN: MINUS"); break;
		case T_PLUS: printf("TOKEN: PLUS"); break;
		case T_DIGIT: printf("TOKEN: DIGIT"); break;
		case T_ANY: printf("TOKEN: ANY"); break;
		case T_DOT: printf("TOKEN: DOT"); break;
		case T_BS: printf("TOKEN: BS"); break;
		case T_SPACE: printf("TOKEN: SPACE"); break;
		case S_EBNF: printf("TYPE: EBNF"); break;
		case S_ANNOTATION: printf("TYPE: ANNOTATION"); break;
		case S_ASKIP: printf("TYPE: ASKIP"); break;
		case S_ACASESENSITIVE: printf("TYPE: ACASESENSITIVE"); break;
		case S_ALINECOMMENTSTART: printf("TYPE: ALINECOMMENTSTART"); break;
		case S_TOKEN: printf("TYPE: TOKEN"); break;
		case S_TC: printf("TYPE: TC"); break;
		case S_TCG: printf("TYPE: TCG"); break;
		case S_TC0: printf("TYPE: TC0"); break;
		case S_TC1: printf("TYPE: TC1"); break;
		case S_STATEMENT: printf("TYPE: STATEMENT"); break;
		case S_EXPRESSION: printf("TYPE: EXPRESSION"); break;
		case S_EXPL0: printf("TYPE: EXPL0"); break;
		case S_EXPL1: printf("TYPE: EXPL1"); break;
		case S_EXPL2: printf("TYPE: EXPL2"); break;
		case S_EXPL3: printf("TYPE: EXPL3"); break;
		case S_STMNTMOD: printf("TYPE: STMNTMOD"); break;
		case S_SMMAX: printf("TYPE: SMMAX"); break;
		default: printf("TYPE: INVALID"); break;
	}
	if (t->type >= T__FIRST && t->type <= T__LAST)
	{
		printf(": %.*s", t->length, s->txt + t->offset);
	}
	printf("\n");
	for (i = 0; i < t->top; i++)
	{
		treeprint(s, t->children[i], depth + 1);
	}
}

void log(const char* m, size_t l, size_t c, size_t o, char gottype)
{
	switch (gottype)
	{
		case T_TOKENIDENT: printf("L%uC%u, TOKENIDENT:\t%s", l, c, m); break;
		case T_STATEIDENT: printf("L%uC%u, STATEIDENT:\t%s", l, c, m); break;
		case T_STMTSEP: printf("L%uC%u, STMTSEP:\t%s", l, c, m); break;
		case T_ANYTEXT: printf("L%uC%u, ANYTEXT:\t%s", l, c, m); break;
		case T_ANNOTATION: printf("L%uC%u, ANNOTATION:\t%s", l, c, m); break;
		case T_SKIP: printf("L%uC%u, SKIP:\t%s", l, c, m); break;
		case T_CASESENSITIVE: printf("L%uC%u, CASESENSITIVE:\t%s", l, c, m); break;
		case T_LINECOMMENTSTART: printf("L%uC%u, LINECOMMENTSTART:\t%s", l, c, m); break;
		case T_OR: printf("L%uC%u, OR:\t%s", l, c, m); break;
		case T_CURLYO: printf("L%uC%u, CURLYO:\t%s", l, c, m); break;
		case T_CURLYC: printf("L%uC%u, CURLYC:\t%s", l, c, m); break;
		case T_ROUNDO: printf("L%uC%u, ROUNDO:\t%s", l, c, m); break;
		case T_ROUNDC: printf("L%uC%u, ROUNDC:\t%s", l, c, m); break;
		case T_SQUAREO: printf("L%uC%u, SQUAREO:\t%s", l, c, m); break;
		case T_SQUAREC: printf("L%uC%u, SQUAREC:\t%s", l, c, m); break;
		case T_TRUE: printf("L%uC%u, TRUE:\t%s", l, c, m); break;
		case T_FALSE: printf("L%uC%u, FALSE:\t%s", l, c, m); break;
		case T_SC: printf("L%uC%u, SC:\t%s", l, c, m); break;
		case T_LT: printf("L%uC%u, LT:\t%s", l, c, m); break;
		case T_GT: printf("L%uC%u, GT:\t%s", l, c, m); break;
		case T_MODMAX: printf("L%uC%u, MODMAX:\t%s", l, c, m); break;
		case T_COLON: printf("L%uC%u, COLON:\t%s", l, c, m); break;
		case T_NUMBER: printf("L%uC%u, NUMBER:\t%s", l, c, m); break;
		case T_ALPHALOW: printf("L%uC%u, ALPHALOW:\t%s", l, c, m); break;
		case T_ALPHAUP: printf("L%uC%u, ALPHAUP:\t%s", l, c, m); break;
		case T_MINUS: printf("L%uC%u, MINUS:\t%s", l, c, m); break;
		case T_PLUS: printf("L%uC%u, PLUS:\t%s", l, c, m); break;
		case T_DIGIT: printf("L%uC%u, DIGIT:\t%s", l, c, m); break;
		case T_ANY: printf("L%uC%u, ANY:\t%s", l, c, m); break;
		case T_DOT: printf("L%uC%u, DOT:\t%s", l, c, m); break;
		case T_BS: printf("L%uC%u, BS:\t%s", l, c, m); break;
		case T_SPACE: printf("L%uC%u, SPACE:\t%s", l, c, m); break;
		default:
			printf("L%uC%u, NA:\t%s", l, c, m);
			break;
	}
}

void token_minimize(token* root)
{
	token* tmp;
	int i;
	for (i = 0; i < root->top; i++)
	{
		while (root->children[i]->top == 1)
		{
			tmp = root->children[i];
			root->children[i] = tmp->children[0];
			tmp->top = 0;
			token_del(tmp);
		}
	}
	for (i = 0; i < root->top; i++)
	{
		token_minimize(root->children[i]);
	}
}

int main(int cargs, char** vargs)
{
	scan s;
	token* t = token_gen(&s, T__INVALID);
	PGENERATOR gen;
	FILE* header, *code;
	memset(&s, 0, sizeof(scan));
	s.log = log;
	s.txt = "@SKIP \\ \\r\\n\\t\n"
		"@CASESENSITIVE true\n"
		"@LINECOMMENTSTART \\/\\/\n"
	
		"any => .;\n"
		"dot = \".\" > \\.;\n"
		"tokenident => (a-z)(a-z0-9)+;\n"
		"stmtsep = \"=\" > \\=;\n"
		"anytext => (.)+;\n"
		"space => \\ ;\n"
		"stateident => (A-Z)(A-Z0-9)+;\n"
		"annotation = \"@\" > \\@;\n"
		"skip => SKIP;\n"
		"casesensitive => CASESENSITIVE;\n"
		"linecommentstart => LINECOMMENTSTART;\n"
		"or = \"|\" > \\|;\n"
		"curlyo = \"{\" > \\{;\n"
		"curlyc = \"}\" > \\};\n"
		"roundo = \"(\" > \\(;\n"
		"roundc = \")\" > \\);\n"
		"squareo = \"[\" > \\[;\n"
		"squarec = \"]\" > \\];\n"
		"true => true;\n"
		"false => false;\n"
		"sc = \";\" > \\;;\n"
		"lt = \"<\" > \\<;\n"
		"gt = \">\" > \\>;\n"
		"modmax => max;\n"
		"colon = \":\" > \\:;\n"
		"number => (0-9)+;\n"
		"alphalow => (a-z);\n"
		"alphaup => (A-Z);\n"
		"minus = \"-\" > \\-;\n"
		"plus = \"+\" > \\+;\n"
		"digit => (0-9);\n"
		"bs = \"\\\\\" > \\\\;\n"
	
	
		"EBNF = { ANNOTATION } { TOKEN | STATEMENT };\n"
		"TC = { TC0 };\n"
	
		"//Switches in the generator\n"
		"ANNOTATION = annotation ( ASKIP | ACASEINSENSITIVE | ALINECOMMENTSTART );\n"
		"ASKIP = skip anytext;\n"
		"ACASESENSITIVE = casesensitive ( true | false );\n"
		"ALINECOMMENTSTART = linecommentstart anytext;\n"
	
		"//Token that will be looked up.\n"
		"//Stuff inbetween the stmtsep and the gt is used for the tostring representation.\n"
		"//All tokens need to be LF(1).\n"
		"TOKEN = tokenident stmtsep [ anytext ] gt TC sc;\n"
		"TCG = roundo TC roundc [ plus ];\n"
		"//range\n"
		"TC0 = TCG | TC1;\n"
		"TC1 = TC2 [ minus TC | { TC2 } ] | dot;\n"
		"TC2 = alphalow | alphaup | digit | bs any;\n"
	
		"STATEMENT = stateident stmtsep EXPRESSION sc;\n"
		"EXPRESSION = { EXPL0 };\n"
		"EXPL0 = EXPL1 { or EXPL1 };\n"
		"EXPL1 = ( curlyo EXPRESSION curlyc ) | EXPL2;\n"
		"EXPL2 = ( squareo EXPRESSION squarec ) | EXPL3;\n"
		"EXPL3 = roundo EXPRESSION roundc | tokenident | stateident [ STMNTMOD ];\n"
	
	
		"STMNTMOD = lt { SMMAX<max:1> } gt;\n"
		"//Sets the max occurances for an statement inside given context.\n"
		"SMMAX = modmax colon number;\n";
	//s.txt = "token => foobar; ROOT = NEST1 | NEST2 | NEST3 | NEST4; NEST1 = token; NEST2 = token; NEST3 = token; NEST4 = token;";
	EBNF(&s, t);
	//treeprint(&s, t, 0);
	//token_minimize(t);
	//treeprint(&s, t, 0);

	header = fopen("output.h", "w");
	code = fopen("output.c", "w");
	gen = generator_create(code, header, "output", t, s.txt);

	generate(gen);

	fflush(header);
	fflush(code);
	fclose(header);
	fclose(code);

	token_del(t);
	//getchar();
}