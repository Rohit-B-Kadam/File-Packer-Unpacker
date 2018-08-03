#include "header.h"

char *  dynamicConcat( char * dest , char * src)
{
	if(dest == NULL)
	{
		dest = (char *) malloc (strlen(src) + 1);
		strcpy( dest , src );
		return dest;
	}
	char * temp = NULL ;
	temp = (char *) malloc ( strlen(dest) + strlen(src) + 1);
	strcpy(temp , dest);
	strcat(temp , src);
	free(dest);
	dest = temp;
	return dest;
}

char *dynamicRemoveLast( char * dest , char ch)
{
	ssize_t len;
	len = strlen(dest);
	for (int i = len; i >= 0; i--)
	{
		if( dest[i] == ch )
		{
			dest[i] = '\0';
			break;
		}
	}
	char* temp = (char *) malloc (strlen(dest) + 1);
	strcpy(temp,dest);
	free(dest);
	return temp;
}
