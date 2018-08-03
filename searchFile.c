#include "header.h"

BOOL searchFile( char* fileName[] , int filecount , int key)
{
	BOOL ret;
	FILEINFO obj;
	relativePath = NULL;
	
	for(int i = 0 ; i < filecount ; i++)
	{
		printf("%s\n",fileName[i]);
	}


	inputFd = open(fileName[0], O_RDONLY );
	if(inputFd == -1)
	{
		printf("Error: File Not Found\n");
		return ERR_ACCESS;
	}

	//Open  existing file to read
	ret = checkValidation(fileName[0] , key );
	if(ret != SUCCESS )		return ret;

	relativePath = dynamicConcat(relativePath,fileName[1]);
	if(checkDirectoryExist( relativePath ) == FALSE)
	{	
		if( mkdir(fileName[1] , 0777) == -1)
		{
			printf("Error: will creating directory\n");
			return ERR_CREATE;
		}
	}

	//open pack file
	while( (read( inputFd , &obj , sizeof(obj) ) ) != 0 )
	{
		
		if( obj.size == DIRECTORY_OPEN )
		{
			continue;
		}
		else if(  obj.size == DIRECTORY_CLOSE )
		{
			continue;
		}
		else
		{
			int i;
			BOOL flag = FALSE;;
			for( i = 2 ; i < filecount ; i++ )
			{
				printf("%s %s\n",fileName[i] , obj.name);
				if ( strcmp( fileName[i] , obj.name ) == 0)
				{
					relativePath = dynamicConcat(relativePath,"/");
					relativePath = dynamicConcat(relativePath,obj.name);
					ret = writeFile( relativePath , obj.size );
					if( ret != SUCCESS )
						return ret;
					relativePath = dynamicRemoveLast(relativePath , '/');
					flag = TRUE;
					break;
				}
			}
			if ( flag == FALSE)
			{
				lseek(inputFd , obj.size , SEEK_CUR);
			}
			continue;
		}

	}

	if( close(inputFd) == -1 )
	{
		printf("Error: Will Closing the output file \n");
		return FALSE;
	}
	return TRUE;
}