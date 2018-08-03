#include <sys/stat.h>	//for stat function
#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h> 
#include <unistd.h>		//for universal standard I/O
#include <dirent.h>		//for directory handling
#include <string.h>
#include <stdlib.h>

typedef int BOOL;
#define TRUE 1
#define FALSE 0
#define SUCCESS 1
#define ERR_ACCESS 2
#define ERR_INVALID 3
#define ERR_CREATE 4
#define ERR_AUTHENTICATION 5


typedef struct
{
	char name[255];			//name of file
	int size;			//size value
						// if size = -1 : The file is directory and its open 
						// if size = -2 : The file is directory and its close
						// if size >  0 : The file is regular file and its size
}FILEINFO;

//FILE SIZE 
#define DIRECTORY_OPEN  -1
#define DIRECTORY_CLOSE -2

typedef struct 
{
	char hardcoded[11];
	char key;
	int type;			//type = 0 application define key
						//type = 1 user defined key
}VALIDATION;

VALIDATION authentication;

//VALIDATION TYPE 
#define APPLICATION_DEF 0
#define USER_DEF 1

int inputFd , outputFd;					 	//file description
char *relativePath;

void helpInfo();							//display the user how to give input 

char *dynamicConcat( char * , char *);	//concate string to dynamic allocate variable

char *dynamicRemoveLast( char *  , char );  //remove string after given character

void displayError(BOOL );

//file packer function declaration

BOOL filePack( char * , char * , int );

BOOL readDirectory( char* dirName);

BOOL readFile();

void InsertValidationCode( char *fileName , int key);

void writeFileInfo( char* dirName , int size );

// file unpacker function declaration

BOOL fileUnpack( char * , char * , int );

BOOL writeFile( char* fileName , int size);

BOOL checkValidation( char* fileName , int key);

BOOL checkDirectoryExist( char* dirName );

BOOL searchFile( char* fileName[] , int filecount , int key);