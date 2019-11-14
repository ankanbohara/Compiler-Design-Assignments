#include <stdbool.h> 
#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>

// Returns true if character is digit
bool isDigit(char ch)
{
	switch(ch)
	{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return (true);
	}
	return (false);
} 

// Returns true if character is an operator
bool isOperator(char ch) 
{ 
	switch(ch)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '>':
		case '<':
		case '=':
			return (true);
	} 
	return (false); 
}

// Returns true if character is a Delimiter
bool isDelimiter(char ch) 
{ 
	bool isOp = isOperator(ch);
	bool isDem = false;
	switch(ch)
	{
		case ' ':
		case ',':
		case ';':
		case '(':
		case ')':
		case '[':
		case ']':
		case '{':
		case '}':
		case '\n':
			isDem = true;
	}
	return (isOp|isDem);
} 

// Returns true if string is a valid identifier
bool validIdentifier(char* str) 
{ 
	bool isDem = isDelimiter(str[0]);
	bool isDig = isDigit(str[0]);
	return !(isDig|isDem); 
} 

// Returns true if string is a keyword
bool isKeyword(char *str){
	char keywords[32][10] = {"auto","break","case","char","const","continue","default",
							"do","double","else","enum","extern","float","for","goto",
							"if","int","long","register","return","short","signed",
							"sizeof","static","struct","switch","typedef","union",
							"unsigned","void","volatile","while"};
	int i;
	bool flag = false;
	for(i = 0; i < 32; ++i)
	{
		if(strcmp(keywords[i],str) == 0)
		{
			flag = true;
			break;
		}
	}
	return flag;
} 

// Returns true if string is an integer 
bool isInteger(char* str) 
{ 
	int i, len = strlen(str); 

	if (len == 0) 
		return (false); 
	for (i = 0; i < len; i++)
	{ 
		if (!isDigit(str[i]) || (str[i] == '-' && i > 0)) 
			return (false); 
	} 
	return (true); 
} 

// Returns true if string is a real number
bool isRealNumber(char* str) 
{ 
	int i, len = strlen(str); 
	bool hasDecimal = false; 

	if (len == 0) 
		return (false); 
	for (i = 0; i < len; i++) { 
		if (!isDigit(str[i]) && str[i] != '.' || (str[i] == '-' && i > 0)) 
			return (false); 
		if (str[i] == '.') 
			hasDecimal = true; 
	} 
	return (hasDecimal); 
} 

// Function to find sub string
char* subString(char* str, int left, int right) 
{ 
	int i; 
	char* subStr = (char*)malloc( 
				sizeof(char) * (right - left + 2)); 

	for (i = left; i <= right; i++) 
		subStr[i - left] = str[i]; 
	subStr[right - left + 1] = '\0'; 
	return (subStr); 
} 

// Parsing the input STRING. 
void parse(char* str) 
{ 
	int left = 0, right = 0; 
	int len = strlen(str); 

	while (right <= len && left <= right) { 
		if (isDelimiter(str[right]) == false) 
			right++; 

		if (isDelimiter(str[right]) == true && left == right) { 
			if (isOperator(str[right]) == true) 
				printf("'%c' IS AN OPERATOR\n", str[right]); 

			right++; 
			left = right; 
		} else if (isDelimiter(str[right]) == true && left != right 
				|| (right == len && left != right)) { 
			char* subStr = subString(str, left, right - 1); 

			if (isKeyword(subStr) == true) 
				printf("'%s' IS A KEYWORD\n", subStr); 

			else if (isInteger(subStr) == true) 
				printf("'%s' IS AN INTEGER\n", subStr); 

			else if (isRealNumber(subStr) == true) 
				printf("'%s' IS A REAL NUMBER\n", subStr); 

			else if (validIdentifier(subStr) == true
					&& isDelimiter(str[right - 1]) == false) 
				printf("'%s' IS A VALID IDENTIFIER\n", subStr); 

			else if (validIdentifier(subStr) == false
					&& isDelimiter(str[right - 1]) == false) 
				printf("'%s' IS NOT A VALID IDENTIFIER\n", subStr); 
			left = right; 
		} 
	} 
	return; 
}

// Loading the input file
char* load_file(char const* path)
{
    char* buffer = 0;
    long length;
    FILE * f = fopen (path, "rb"); //was "rb"

    if (f)
    {
      fseek (f, 0, SEEK_END);
      length = ftell (f);
      fseek (f, 0, SEEK_SET);
      buffer = (char*)malloc ((length+1)*sizeof(char));
      if (buffer)
      {
        fread (buffer, sizeof(char), length, f);
      }
      fclose (f);
    }
    buffer[length] = '\0';
    return buffer;
} 

// Main Function 
int main() 
{ 
	char *str = load_file("ass2.txt"); 
	parse(str);
	return 0; 
} 

