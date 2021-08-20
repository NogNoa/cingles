// Ritchie, D. and Kernighan, W. (1988) p110


#include <ctype.h>
#include "dcl.h"

void dcl(void);
void dirdcl(void);
void typedcl(void);

char name[MAXTOKEN]; /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
int tokentype; /* type of last token */

int main(void) 
{ /* convert declaration to words */
	//stdin= fopen("b.txt", "r");
	token[0] = '\0'; /* making sure not to get garbage */
	while ((tokentype = gettoken()) != EOF)  /* 1st token on line */
	{	out[0] = '\0';
		datatype[0] = '\0'; /* forget datatype */
		typedcl(); /* fetch the datatype */
		dcl(); /* parse rest of line */
		for (;tokentype == ')' || tokentype == ']'; tokentype=gettoken())
			fprintf(stderr, "error: Found a dangling %c. Have you lost it?\n", tokentype);
		if (tokentype != '\n' && tokentype != EOF)
		{	fprintf(stderr,"syntax error %d %c\n", tokentype, tokentype);
			dcl();
		}
		printf("%s: %s %s\n\n", name, out, datatype);
	}
	return 0;
}

void dcl(void)
{ /* dcl: parse a declarator */
	int ns=0;
	while ((tokentype = gettoken()) == '*') /* count *'s */
		ns++;
	dirdcl();
	while (ns-- > 0)
		strcat(out, " pointer to");
}
	
void dirdcl(void)
{ /* dirdcl: parse a direct declarator */
	if (tokentype == '(')  /* ( dcl ) */
	{	dcl();
		if (tokentype != ')')
			fprintf(stderr,"error: missing )\n");
	} else if (tokentype == NAME) /* variable name */
		strcpy(name, token);
	else if (tokentype == '\n')
		return;
	else
		fprintf(stderr,"error: expected name or (dcl)\n");
	for (_Bool cont=1;cont;)
	{	tokentype=gettoken();
		if (tokentype == PARENS)
			strcat(out, " function returning");
		else if (tokentype == BRACKETS) 
		{	strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");
		}
		else
			cont = 0;
	}
}

void typedcl(void)
{ 
	if (tokentype == '(')  /* ( dcl ) */
	{	tokentype = gettoken();
		typedcl();
		if ( (tokentype = gettoken()) != ')')
		{	fprintf(stderr,"error: missing ) at typedcl\n");
			ungettoken(tokentype);
		}
	} 
	else if (tokentype == NAME) /* variable name */
		strcpy(datatype, token);
	else 
	{	fprintf(stderr,"error: expected type name\n");
		ungettoken(tokentype);
	}
}



/* type |  *      (    | name   |    )    | () []
   main | dcl<->dirdcl | dirdcl | dirdcl  | dirdcl 
*/
