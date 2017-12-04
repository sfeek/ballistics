#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

/*Safe function to get strings from the user*/
void sgets (char *line , int size)
{
	int i;
	
	fflush (stdin);
		
	for (i = 0 ; i < size ; ++i)
	{
		int ch = fgetc(stdin);
		if (ch == '\n' || ch == EOF)
		{
			break;
		}
		line[i] = ch;
	}

	line[i] = '\0';
}

/* Make sure string is really a double */
int stringtodouble (const char *str, double *v) 
{
	char *ptr;
	
	*v = strtod (str, &ptr);
	
	if (str != ptr && *ptr == '\0') return 1;

	return 0;
}

/* Make sure string is really an integer */
int stringtoint (const char *str, int *v) 
{
	char *ptr;
	
	*v = (int) strtol (str, &ptr, 10);
	
	if (str != ptr && *ptr == '\0') return 1;

	return 0;
}

/* Gracefully get a double or decimal value */
double getdouble (const char *display)
{
	char buffer[30];
	double value;

	do 
	{
		printf ("%s", display);

		sgets (buffer, 30);
	} 
	while (!stringtodouble(buffer, &value));

	return value;
}

/* Gracefully get a string - *** Remember to free() the returned string when finished with it! *** */
char *getstring (const char *display, int length)
{
	char *buffer;

	if (!(buffer = calloc (length + 2, sizeof (char))))
	{
			return NULL;
	}

	printf ("%s", display);

	sgets (buffer, length + 1);
	
	return buffer;
}

/* Gracefully get an integer value */
int getint (const char *display)
{
	char buffer[30];
	int value;

	do 
	{
		printf ("%s", display);

		sgets (buffer, 30);
	} 
	while (!stringtoint(buffer, &value));

	return value;
}

/* Wait for the user to Press ENTER */
void PauseForEnterKey (void)
{
	char ch;

	printf("\n*** Press [ENTER] For Main Menu ***\n");

	while (1)
	{
		ch=fgetc(stdin);
		if (ch == '\n') break;
	}

	return;
}
