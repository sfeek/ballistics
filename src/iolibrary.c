#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

/* Gracefully get a string - *** Remember to free() the returned string when finished with it! *** */
char *getstring (const char *display)
{
	char c;
	size_t len = 2; 
	size_t i=0;	

	printf("%s", display);
	
	char *strData = malloc (2);
	if (strData == NULL) 
	{
		printf("\nOut of Memory Error!\n");
		return NULL;
	}

	while ((c=fgetc(stdin)) != '\n') 
	{
		strData[i++] = c;
		
		if (i > INT_MAX) 
		{
			printf("\nString Overflow Error!\n");
			return NULL;
		}

		if (i >= len) 
		{
			len *= 2;

			strData = realloc (strData, len);
			
			if (strData == NULL) 
			{
				printf("\nOut of Memory Error!\n");
				return NULL;
			}
		}
	}

	strData[i] = 0;

	return strData;
}

/* Make sure string is really a double */
int stringtodouble (const char *str, double *v) 
{
	char *ptr;
	
	errno = 0;
	
	*v = strtod (str, &ptr);

	if (errno == ERANGE) 
	{	
		printf ("\nNumber Overflow/Underflow Error!\n");
		return EXIT_FAILURE;
	}
	
	if (str == ptr) 
	{
		printf ("\nInvalid Number Conversion Error!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* Make sure string is really an integer */
int stringtoint (const char *str, int *v) 
{
	char *ptr;

	errno = 0;
	
	*v = (int) strtol (str, &ptr, 10);

	if (errno == ERANGE) 
	{	
		printf ("\nNumber Overflow/Underflow Error!\n");
		return EXIT_FAILURE;
	}
	
	if (str == ptr) 
	{
		printf ("\nInvalid Number Conversion Error!\n");
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

/* Gracefully get a double or decimal value */
double getdouble (const char *display)
{
	char *buffer;
	double value;
	int rtn;

	while (1) 
	{
		buffer = getstring (display);

		rtn = stringtodouble (buffer, &value);

		free (buffer);

		if (rtn == EXIT_SUCCESS) return value;
	}
}


/* Gracefully get an integer value */
int getint (const char *display)
{
	char *buffer;
	int value;
	int rtn;

	while (1) 
	{
		buffer = getstring (display);

		rtn = stringtoint (buffer, &value);

		free (buffer);

		if (rtn == EXIT_SUCCESS) return value;
	} 
}
