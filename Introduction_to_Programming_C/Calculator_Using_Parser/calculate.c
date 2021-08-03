#include <stdio.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1

#define RESCHAR '\n'

// ENDCHAR defined to be End Of Transmission ASCII (ETX) - for Windows CNTR-D
#define ENDCHAR 4


char isspaceortab(char c)
{
	if (c == ' ' || c == '\t')
		return TRUE;
	return FALSE;
}
char getchar_nospaceortab()
{
	int	c = getchar();
	while (isspaceortab(c))
		c = getchar();

	return c;
}

// ----------------------------------------------------------------------------
// <digit> ::= ’0’ | ’1’ | ’2’ | ’3’ | ’4’ | ’5’ | ’6’ | ’7’ | ’8’ | ’9’
// <unumber> ::= <digit> | <digit> <unumber>
// ----------------------------------------------------------------------------
int get_unumber(char *c) 
{
	int num = 0;
	while (1)
	{
		//  Check for SPACE or TAB
		if (isspaceortab(*c)) 
			*c = getchar_nospaceortab();

		// get number
		while (isdigit(*c))
		{
			num = num * 10 + *c - '0';
			*c = getchar_nospaceortab();
		}
		break;
	}
	return num;
}

// ----------------------------------------------------------------------------
// <snumber> ::= <unumber> | ’+’ <unumber> | ’-’ <unumber>
// ----------------------------------------------------------------------------
int get_snumber(char *c) 
{
	int num = 0;
	char operator = ' ';	
	while (1)
	{
		// Check for SPACE or TAB
		if (isspaceortab(*c)) 
			*c = getchar_nospaceortab();

		// Check for expression operator
		// if expression operator
		if (*c == '+' || *c == '-')
		{
			operator = *c;
			// getchar
			*c = getchar_nospaceortab();
			continue;
		}

		// get number
		if (isdigit(*c))
		{
			num = get_unumber(c);
		}
		if (operator == '-')
			num *= -1;
		break;
	}
	return num;
}

// ----------------------------------------------------------------------------
// <factor> ::= <snumber> | ’(’ <expression> ’)’
// ----------------------------------------------------------------------------
int calculate_factor(char *error, char* c) 
{
	int res = 0;
	if (*error == TRUE || *error>100)
		return res;
	int flag=0;

	while (1)
	{
		// Check for SPACE or TAB
		if (isspaceortab(*c)) 
			*c = getchar_nospaceortab();
		
		// Check for expression operator
		// if expression operator
		if (*c == '(')
		{
			*c = ' ';
			res = calculate_expression(error, c);
			flag=1;
			if (*error > 0)
				return res;
			continue;
		}
		else if (*c == ')')
		{
			*c = ' ';
			break;
		}
		else if(flag==1) 
		{
		
	
		*error=104;
		return res;
		}
		else 
		{
			res = get_snumber(c);
			break;
		}
	}
	return res;
}

// ----------------------------------------------------------------------------
// <term> ::= <factor> | <factor> ’*’ <term>
// ----------------------------------------------------------------------------
int calculate_term(char *error, char* c) {
	int res = 0;
	if (*error == TRUE || *error>100)
		return res;
	/*
	if (*c == '*')
	{
		*error = 101;
		return -99999;
	}
	*/
	while (1)
	{
		// Check for SPACE or TAB
		if (isspaceortab(*c)) 
			*c = getchar_nospaceortab();
		// Check for expression operator
		// if NOT expression operator
		if (*c != '*')
		{
			res = calculate_factor(error, c);
			// Check for SPACE or TAB
			if (isspaceortab(*c)) 
				*c = getchar_nospaceortab();
			if (*c != '*')
				break;
		}

		// Check for expression operator
		// if expression operator
		if (*c == '*')
		{
			*c = ' ';
			int res_term = calculate_term(error, c);
			res *= res_term;
			// Check for SPACE or TAB
			if (isspaceortab(*c)) 
				*c = getchar_nospaceortab();
			if (*c != '*')
				break;
		}

	}
	return res;
}

// ----------------------------------------------------------------------------
// <expression> ::= <term> | <expression> ’+’ <term> | <expression> ’-’ <term>
// ----------------------------------------------------------------------------
int calculate_expression(char *error, char* c)
{
	int res = 0;
	if (*error == TRUE||*error>100)
		return res;
	
	while (1)
	{
		// Check for SPACE or TAB
		if (isspaceortab(*c)) 
			*c = getchar_nospaceortab();

		// Check for expression operator
		// if NOT expression operator
		if ((*c != '+') && (*c != '-'))
		{
			res = calculate_term(error, c);
			//  Check for SPACE or TAB
			//if (isspaceortab(*c)) 
			//	*c = getchar_nospaceortab();
			if ((*c != '+') && (*c != '-'))
				break;
		}

		// Check for expression operator
		// if expression operator
		if ((*c == '+') || (*c == '-'))
		{
			char oper = *c;
			*c = ' ';
			int res_expr = calculate_term(error, c);
			if (oper == '+')
			{
				res += res_expr;
			}
			else //if (oper == '-')
			{
				res -= res_expr;
			}
			// Check for SPACE or TAB
			if (isspaceortab(*c)) 
				*c = getchar_nospaceortab();
			if ((*c != '+') && (*c != '-'))
				break;
		}

	}
	return res;
}

// ----------------------------------------------------------------------------
// CALCULATE MAIN - One Line
// ----------------------------------------------------------------------------
int calculate(char *error)
{
	int res = 0;
	int ci = getchar();
	if ((ci > 0) && (ci != ENDCHAR)) 
	{
		char c = (char) ci;
		res = calculate_expression(error, &c);
	}
	else
	{
		*error = ENDCHAR;
	}
	return res;
}

int main()
{
	int loop = 0;
	int res = 0;
	char error = FALSE;

	while (1)
	{
		printf("Enter a calculation to be made : ");
		loop++;
		res = calculate(&error);
		if (error == FALSE) {
			printf("Result %d : %d\r\n", loop, res);
		}
		else if ((error == TRUE) || (error > 100) ) {
			if(error==104)
			{
				printf("ERROR : Missing closing parenthesis\n", error);
				error= FALSE;
			}
		}
		else if (error == ENDCHAR) {
			printf("\n");
			break;
		}
	}
}
