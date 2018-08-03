#include "header.h"

void InsertValidationCode( char *fileName , int key)
{
	char *actualName;
	strcpy ( authentication.hardcoded , "MARVALLOUS" );
	if( key == 0 )
		authentication.type = APPLICATION_DEF;
	else
		authentication.type = USER_DEF;
	actualName = fileName;
	for (int i = strlen(fileName); i >= 0; i--)
	{
		if( fileName[i] == '/' )
		{
			actualName = &fileName[i + 1] ;
			break;
		}
	}
	authentication.key = strlen(actualName) + key;
	write( outputFd , &authentication , sizeof(authentication) );	
}

void writeFileInfo( char* dirName , int size )
{
	FILEINFO obj;
	ssize_t count;
	strcpy( obj.name , dirName );
	obj.size = size;
	count = write( outputFd , &obj , sizeof(obj) );	 
}

BOOL readFile()
{
	ssize_t retread;
	int temp;
	char buffer[256]; //to store read data
	//Open a file to read
	inputFd = open( relativePath, O_RDONLY);
	if( inputFd == -1 )
		return ERR_CREATE;
	
	while( (retread = read( inputFd , buffer , sizeof(buffer) ) ) != 0 )
	{
		
		temp = retread;
		while(temp != 0)
		{
			buffer[temp] += authentication.key;
			temp--;
		}
		write( outputFd , buffer , retread );
		
	}

	close(inputFd);

	return SUCCESS;
}

BOOL readDirectory( char* dirName)
{
	ssize_t count;
	DIR* dir;
	struct dirent *dirEntry;  //output of readdir store complete info about file
	struct stat status;		  // file status
	BOOL ret;
	//to open directory	
	dir = opendir(relativePath);
	if( dir == 0)
	{
		printf("Error: Cannot open directory ( Give proper name of directory) \n");
		return ERR_ACCESS;
	}

	//check if directory is open or not
	if ( (dirEntry = readdir(dir) ) == NULL )
	{
		printf("%s Directory  is Empty\n",relativePath);
		return FALSE;
	}

	//write Directory info in file ( to indicate directory is open)
	writeFileInfo( dirName , DIRECTORY_OPEN );
	do
	{
		// skip  '.' and '..' directory
		if( strcmp(dirEntry->d_name , ".") == 0 || strcmp(dirEntry->d_name , "..") == 0 )
			continue;

		//concate file name to relativePath
		relativePath = dynamicConcat( relativePath  , "/" );
		relativePath = dynamicConcat( relativePath , dirEntry->d_name );
		//get status of file;
		if(lstat(relativePath,&status) == -1 )
		{
			return FALSE;
		}

		//checking if file is regular or not
		if(S_ISREG( status.st_mode))
		{
			writeFileInfo( dirEntry->d_name , status.st_size );

			ret = readFile();
			if( ret != SUCCESS )	
			{
				return ret;
			}

		}
		else if( S_ISDIR( status.st_mode) )
		{
			ret = readDirectory( dirEntry -> d_name);
			if( ret != SUCCESS )	
			{
				return ret;
			}
		}

		//remove file name form path
		relativePath = dynamicRemoveLast(relativePath , '/');

	}while ( (dirEntry = readdir(dir) ) != NULL );
	
	//write Directory info in file ( to indicate directory is close)
	writeFileInfo( dirName , DIRECTORY_CLOSE );
	return SUCCESS;
}


BOOL filePack( char* path , char* fileName  ,int key )
{
	BOOL ret;
	char dirName[255];

	//Open new or existing file to write
	outputFd = creat( fileName , 0444 );
	if(outputFd == -1)
		return ERR_CREATE;

	//VALIDATION CODE
	InsertValidationCode( fileName , key );


	// To get main Folder name eg( ExcuteData/Folder get "Folder" )
	relativePath = ( char * ) malloc ( strlen(path) + 1);
	strcpy( relativePath , path); 
	strcpy ( dirName ,relativePath);
	for (int i = strlen(relativePath); i >= 0; i--)
	{
		if( relativePath[i] == '/' )
		{
			strcpy( dirName , &relativePath[i + 1]) ;
			break;
		}
	}


	//read given directory data
	ret = readDirectory( dirName );
	if(ret != SUCCESS)		return ret;

	close(outputFd);
	return SUCCESS;
}