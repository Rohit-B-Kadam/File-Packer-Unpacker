#include "header.h"

BOOL checkDirectoryExist( char* dirName )
{
	struct stat st;
	if( stat(dirName , &st) == -1 )
		return FALSE;
	return TRUE;
}

BOOL checkValidation( char* fileName , int key)
{
	char *actualName;
	read(inputFd , &authentication , sizeof(authentication));

	//checking hardcoded data
	if( strcmp(authentication.hardcoded , "MARVALLOUS" ) != 0 )
		return ERR_INVALID;

	//user not given key
	if( ( key == 0 ) && ( authentication.type == USER_DEF) )
	{
		printf("Error : Give encryt key value\n");
		return ERR_AUTHENTICATION;	
	}
	
	//geting autal fileName
	actualName = fileName;
	for (int i = strlen(fileName); i >= 0; i--)
	{
		if( fileName[i] == '/' )
		{
			actualName = &fileName[i + 1] ;
			break;
		}
	}

	//check key set by application
	if( ( key == 0 ) && ( authentication.type == APPLICATION_DEF ))
	{
		if( authentication.key !=  strlen(actualName) )
			return ERR_AUTHENTICATION;
	}
	else  // check userdefined key
	{

		if( authentication.key != ( strlen(actualName) + key ) )
			return ERR_AUTHENTICATION;
	}
	return SUCCESS;
}

BOOL writeFile( char* fileName , int size)
{
	int temp;
	char * ptr = (char * ) malloc ( size * sizeof(char));
	outputFd = open( fileName ,  O_WRONLY | O_CREAT );
	if( outputFd == -1 )
		return ERR_CREATE;

	read( inputFd , ptr , size );

	temp = size;
	while(temp != 0)
	{
		ptr[temp] -= authentication.key;
		temp--;
	}
	write( outputFd , ptr , size );
	close(outputFd);
	free(ptr);
	return SUCCESS;
}

BOOL fileUnpack( char* fileName , char* dirName , int key)
{
	BOOL ret;
	FILEINFO obj;
	relativePath = NULL;
	

	inputFd = open(fileName, O_RDONLY );
	if(inputFd == -1)
	{
		printf("Error: File Not Found\n");
		return ERR_ACCESS;
	}

	//Open  existing file to read
	ret = checkValidation(fileName , key );
	if(ret != SUCCESS )		return ret;

	relativePath = dynamicConcat(relativePath,dirName);
	if(checkDirectoryExist( relativePath ) == FALSE)
	{	
		if( mkdir(dirName , 0777) == -1)
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
			relativePath = dynamicConcat(relativePath,"/");	
			relativePath = dynamicConcat(relativePath,obj.name);

			if(checkDirectoryExist( relativePath ) == FALSE)
			{	
				if( mkdir(relativePath , 0777) == -1)
				{
					printf("Error: will creating directory\n");
					return ERR_CREATE;
				}
			}
			continue;
		}
		else if(  obj.size == DIRECTORY_CLOSE )
		{
			//remove file name form path
			relativePath = dynamicRemoveLast(relativePath , '/');
			continue;
		}
		else
		{
			relativePath = dynamicConcat(relativePath,"/");
			relativePath = dynamicConcat(relativePath,obj.name);
			ret = writeFile( relativePath , obj.size );
			if( ret != SUCCESS )
				return ret;
			relativePath = dynamicRemoveLast(relativePath , '/');
	
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