#include "Parser.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include "Generator.h"
#if _WIN32 & _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#endif

#define VERSION "1.1"

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
		case T_NUMBER: printf("TOKEN: NUMBER"); break;
		case T_ALPHALOW: printf("TOKEN: ALPHALOW"); break;
		case T_ALPHAUP: printf("TOKEN: ALPHAUP"); break;
		case T_MINUS: printf("TOKEN: MINUS"); break;
		case T_PLUS: printf("TOKEN: PLUS"); break;
		case T_DIGIT: printf("TOKEN: DIGIT"); break;
		case T_ANY: printf("TOKEN: ANY"); break;
		case T_DOT: printf("TOKEN: DOT"); break;
		case T_BS: printf("TOKEN: BS"); break;
		case T_NOTOKEN: printf("TOKEN: NOTOKEN"); break;
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
		case S_TC2: printf("TYPE: TC2"); break;
		case S_STATEMENT: printf("TYPE: STATEMENT"); break;
		case S_EXPRESSION: printf("TYPE: EXPRESSION"); break;
		case S_EXPRESSION2: printf("TYPE: EXPRESSION2"); break;
		case S_EXPL0: printf("TYPE: EXPL0"); break;
		case S_EXPL1: printf("TYPE: EXPL1"); break;
		case S_EXPL2: printf("TYPE: EXPL2"); break;
		case S_EXPL3: printf("TYPE: EXPL3"); break;
		case S_TMODE: printf("TYPE: TMODE"); break;
		default:
			printf("TYPE: INVALID");
			break;
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
void scan_log_method(const char* m, size_t l, size_t c, size_t o, char gottype)
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
		case T_NOTOKEN: printf("L%uC%u, NOTOKEN:\t%s", l, c, m); break;
		case T_NUMBER: printf("L%uC%u, NUMBER:\t%s", l, c, m); break;
		case T_ALPHALOW: printf("L%uC%u, ALPHALOW:\t%s", l, c, m); break;
		case T_ALPHAUP: printf("L%uC%u, ALPHAUP:\t%s", l, c, m); break;
		case T_MINUS: printf("L%uC%u, MINUS:\t%s", l, c, m); break;
		case T_PLUS: printf("L%uC%u, PLUS:\t%s", l, c, m); break;
		case T_DIGIT: printf("L%uC%u, DIGIT:\t%s", l, c, m); break;
		case T_ANY: printf("L%uC%u, ANY:\t%s", l, c, m); break;
		case T_DOT: printf("L%uC%u, DOT:\t%s", l, c, m); break;
		case T_BS: printf("L%uC%u, BS:\t%s", l, c, m); break;
		default:
			printf("L%uC%u, NA:\t%s", l, c, m);
			break;
	}
}
void print_help(void)
{
	printf(
		"Warning! Arguments are never properly checked!\n"
		"    Usage: xcg -i <path> -o <name>\n"
		"        -i    Sets the input BNF file. Should be a valid path.\n"
		"              Will be passed straigth into fopen(...)!\n"
		"\n"
		"        -o    Sets the file names for the generation output.\n"
		"              Please note that theese are not allowed to\n"
		"              be a path and have to be a valid filename.\n"
		"              Moving output to a different directory then\n"
		"              where the tool is located is not supported.\n"
		"\n"
		"        -t    Prints the whole BNF parsing tree after generating.\n"
		"\n"
		"        -T    Same as `-t` but minimizes the tree first.\n"
		"\n"
		"        -v    Prints current version informations and terminates\n"
		"              with exit code 0.\n"
		"\n"
		"    BNF Documentation:\n"
		"        - Annotation:\n"
		"            Annotations have to be at the very start of each file.\n"
		"            They allow you to change some flags in the generator\n"
		"            which modify the output.\n"
		"            Available annotations are:\n"
		"                - @SKIP\n"
		"                    Expects the characters that should be skipped.\n"
		"                    defaults to \" \\r\\n\\t\".\n"
		"                - @LINECOMMENTSTART\n"
		"                    Tells what a linecomment-start looks like.\n"
		"                    defaults to \"\\\\\".\n"
		"                - @CASESENSITIVE\n"
		"                    Allows parsing of test-tokens to be either\n"
		"                    case-sensitive or not.\n"
		"                    Please note that this has no effect on\n"
		"                    tokens that are non-text tokens.\n"
		"                    --> `(a-z)` is no text-token\n"
		"                    --> `abc` is a text-token\n"
		"                    defaults to \"false\".\n"
		"                    value has to be either\n"
		"                    `true` or `false`.\n"
		"        - Tokens:\n"
		"            Tokens are character-combinations that can be\n"
		"            used in statements.\n"
		"            The tokens always have to be lowercase!\n"
		"            A token consists of:\n"
		"                - A name\n"
		"                - An optional representation for errors\n"
		"                - the actual token\n"
		"                - Optional token mods\n"
		"            The syntax of a token somewhat resembles regex,\n"
		"            but do not be fooled! It is no actual regex\n"
		"            involved!\n"
		"            Usage:\n"
		"                name = \"representation\" > token ? tokenmod\n"
		"                name => token\n"
		"                name => token ? tokenmod ? tokenmod\n"
		"            Allowed stuff for tokens:\n"
		"                - alphanumerical characters\n"
		"                - backspace escaped anything\n"
		"            Special syntax constructs:\n"
		"                `?-?` will check for a given range.\n"
		"                `(?)` allows to group a token together.\n"
		"                `(?)+` allows repeat a group.\n"
		"                `.` placeholder for ANY character but '\\0'.\n"
		"            Available tokenmods:\n"
		"                notoken - Prevents token generation so that\n"
		"                          it does not appears inside the\n"
		"                          generated tree.\n"
		"        - Statements:\n"
		"            Statements are rules about how to parse something.\n"
		"            They always have to be named fully uppercase.\n"
		"            Usage (Expressions is the actual content):\n"
		"                NAME = <EXPRESSIONS>;"
		"            Syntax constructs:\n"
		"                `(?)` Allows grouping\n"
		"                `[?]` Allows to conditional execute\n"
		"                `{?}` Will repeatedly parse whatever is inside\n"
		"            Example:\n"
		"                STATEMENT = token1 OTHERSTATEMENT { token2 };\n"
		"            For more info, checkout the wikipedia page to BNF :)\n"
	);
}

int get_bom_skip(const char* buff)
{
	if (buff[0] == (char)0xEF && buff[1] == (char)0xBB && buff[2] == (char)0xBF)
	{
		//UTF-8
		return 3;
	}
	else if (buff[0] == (char)0xFE && buff[1] == (char)0xFF)
	{
		//UTF-16 (BE)
		return 2;
	}
	else if (buff[0] == (char)0xFE && buff[1] == (char)0xFE)
	{
		//UTF-16 (LE)
		return 2;
	}
	else if (buff[0] == (char)0x00 && buff[1] == (char)0x00 && buff[2] == (char)0xFF && buff[3] == (char)0xFF)
	{
		//UTF-32 (BE)
		return 2;
	}
	else if (buff[0] == (char)0xFF && buff[1] == (char)0xFF && buff[2] == (char)0x00 && buff[3] == (char)0x00)
	{
		//UTF-32 (LE)
		return 2;
	}
	else if (buff[0] == (char)0x2B && buff[1] == (char)0x2F && buff[2] == (char)0x76 &&
		(buff[3] == (char)0x38 || buff[3] == (char)0x39 || buff[3] == (char)0x2B || buff[3] == (char)0x2F))
	{
		//UTF-7
		return 4;
	}
	else if (buff[0] == (char)0xF7 && buff[1] == (char)0x64 && buff[2] == (char)0x4C)
	{
		//UTF-1
		return 3;
	}
	else if (buff[0] == (char)0xDD && buff[1] == (char)0x73 && buff[2] == (char)0x66 && buff[3] == (char)0x73)
	{
		//UTF-EBCDIC
		return 3;
	}
	else if (buff[0] == (char)0x0E && buff[1] == (char)0xFE && buff[2] == (char)0xFF)
	{
		//SCSU
		return 3;
	}
	else if (buff[0] == (char)0xFB && buff[1] == (char)0xEE && buff[2] == (char)0x28)
	{
		//BOCU-1
		if (buff[3] == (char)0xFF)
			return 4;
		return 3;
	}
	else if (buff[0] == (char)0x84 && buff[1] == (char)0x31 && buff[2] == (char)0x95 && buff[3] == (char)0x33)
	{
		//GB 18030
		return 3;
	}
	return 0;
}

char* load_file(const char* fpath)
{
	FILE* fptr = fopen(fpath, "rb");
	size_t size;
	char* filebuff, *filebuff2;
	unsigned int bomskip = 0;
	if (fptr == 0)
	{
		printf("[ERR] Could not open file '%s'", fpath);
		return 0;
	}
	fseek(fptr, 0, SEEK_END);
	size = ftell(fptr);
	fseek(fptr, 0, SEEK_SET);
	filebuff = malloc(sizeof(char) * (size + 1));
	memset(filebuff, 0, sizeof(char) * (size + 1));
	fread(filebuff, sizeof(char), size, fptr);
	fclose(fptr);
	bomskip = get_bom_skip(filebuff);
	filebuff2 = malloc(sizeof(char) * (size + 1 - bomskip));
	strcpy(filebuff2, filebuff + bomskip);
	free(filebuff);
	return filebuff2;
}

int main(int argc, char** argv)
{
	scan s;
	token* t = token_gen(&s, T__INVALID);
	PGENERATOR gen;
	FILE* header, *code;
	int i;
	char* cptr;
	char* inputfile = 0;
	char* outputname = 0;
	bool printtree = false, minimize = false;
#if _WIN32 & _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF);
	//_CrtSetBreakAlloc(1718);
	_ASSERTE(_CrtCheckMemory());
#endif

	if (argc <= 1)
	{
		print_help();
		return 1;
	}
	for (i = 0; i < argc; i++)
	{
		cptr = argv[i];
		if (cptr[0] == '-' && i + 1 < argc)
		{
			switch (cptr[1])
			{
				case 'i':
					inputfile = argv[i + 1];
					i++;
					printf("Seting input file to '%s'\n", inputfile);
					break;
				case 'o':
					outputname = argv[i + 1];
					printf("Seting output files to '%s.c' and '%s.h'\n", outputname, outputname);
					i++;
					break;
				case 'T':
					minimize = true;
					printtree = true;
					break;
				case 't':
					printtree = true;
					break;
				case '?':
					print_help();
					break;
				case 'v':
					printf("X39s Code Generator (XCG) v" VERSION "\n");
					return 0;
				default:
					printf("Invalid Usage! Use the `-?` option for more info.\n");
					return 1;
			}
		}
		else if(i != 0)
		{
			printf("Invalid Usage! Use the `-?` option for more info.\n");
			return 1;
		}
	}
	if (inputfile == 0 || outputname == 0)
	{
		printf("Invalid Usage! Use the `-?` option for more info.\n");
		print_help();
		return 1;
	}


	memset(&s, 0, sizeof(scan));
	s.log = scan_log_method;
	s.txt = load_file(inputfile);
	EBNF(&s, t);

	if (minimize)
	{
		token_minimize(t);
	}
	if (printtree)
	{
		treeprint(&s, t, 0);
	}

	cptr = alloca(sizeof(char) * ((i = strlen(outputname)) + 3));
	strcpy(cptr, outputname);
	cptr[i] = '.';
	cptr[i + 1] = 'h';
	cptr[i + 2] = '\0';
	header = fopen(cptr, "w");
	if (header == 0)
	{
		printf("Failed to open '%s' in write mode.\n", cptr);
		return 1;
	}
	cptr[i + 1] = 'c';
	code = fopen(cptr, "w");
	if (code == 0)
	{
		printf("Failed to open '%s' in write mode.\n", cptr);
		fclose(header);
		return 1;
	}
	gen = generator_create(code, header, outputname, t, s.txt);

	generate(gen);

	generator_destroy(gen);
	fflush(header);
	fflush(code);
	fclose(header);
	fclose(code);
	free((char*)s.txt); //on purpose, load_file currently loads directly into s.txt


	token_del(t);
#if _WIN32 & _DEBUG
	_CrtDumpMemoryLeaks();
	_ASSERTE(_CrtCheckMemory());
#endif
	return 0;
}