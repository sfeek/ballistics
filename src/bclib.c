#include <stdio.h>
#include <stdlib.h>


/*Safe function to get values from the user*/
void sgets(char *line,size_t size)
{
	size_t i;
	
	fflush(stdin);
		
	for ( i = 0; i < size - 1; ++i )
	{
		int ch = fgetc(stdin);
		if ( ch == '\n' || ch == EOF )
		{
			break;
		}
		line[i] = ch;
	}
	line[i] = '\0';
}

/* Wait for the user to Press ENTER */
void PauseForEnterKey(void)
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
