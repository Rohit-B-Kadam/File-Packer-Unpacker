#include "header.h"

/*
		Author:  	ROHIT BABU KADAM
		Program:	To pack and un pack File
		cc main.c filePacker.c fileUnpacker.c helpInfo.c helperFunction.c -o ExcuteData/PackUnpack;
		./ExcuteData/PackUnpack -M ExcuteData/Folder ExcuteData/merge.txt
		./ExcuteData/PackUnpack -S ExcuteData/merge.txt ExcuteData/Folder7

*/


int main( int argc , char* argv[])
{
	BOOL ret;

	// checking valid argument
	if( argc == 4 )
	{
		if( strcasecmp ( argv[1] , "-M" ) == 0)
		{
			// File Pack with application defined key
			ret = filePack( argv[2] , argv[3] , 0);
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: Packing Fail\n");
				return 0;
			}
			printf("Successfully Packed\n");
			return 0;
		}
		else if ( strcasecmp ( argv[1] , "-S" ) == 0 )
		{
			// File unPack with application defined key
			ret = fileUnpack( argv[2] , argv[3] , 0 );
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: UnPacking fail\n");
				return 0;
			}
			printf("Successfully UnPacked\n");
			return 0;
		}
	}
	else if(argc == 5)
	{
		
		if( strcasecmp ( argv[1] , "-M" ) == 0)
		{
			// File Pack with userdefined key
			ret = filePack( argv[2] , argv[3] , atoi(argv[4]) );
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: Packing Fail\n");
				return 0;
			}
			printf("Successfully Packed\n");
			return 0;
		}
		else if ( strcasecmp ( argv[1] , "-S" ) == 0 )
		{
			// File unpack with userdefined key
			ret = fileUnpack( argv[2] , argv[3] , atoi(argv[4]) );
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: UnPacking fail\n");
				return 0;
			}
			printf("Successfully UnPacked\n");
			return 0;
		}
	}else if( argc == 2 )
	{
		//Help Display
		if( strcasecmp(argv[1] , "-H") == 0 )
		{
			helpInfo();
			return 0;
		}
	}
	else
	{
		/*
			Get specfic file from packfile:
				serach given file name in packfile and if it found then extract that file. 
		*/
		if( ( strcasecmp (argv[2] , "-GET") == 0 ) && ( strcasecmp ( argv[1] , "-S" ) == 0 ) && argc >= 8 && ( strcasecmp ( argv[3] , "-e" ) == 0 )  )
		{
			// User defined encrypted file
			ret = searchFile( &argv[5] , argc - 5 , atoi(argv[4]));
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: Unpacking Fail\n");
				return 0;
			}
			printf("Successfully unpack search File\n");
			return  0;
		}
		else if( ( strcasecmp (argv[2] , "-GET") == 0 ) && ( strcasecmp ( argv[1] , "-S" ) == 0 ) && argc >= 6 )
		{
			// Application defined encrypted file
			ret = searchFile( &argv[3] , argc - 3 , 0);
			if(ret != SUCCESS)
			{
				displayError(ret);
				printf("Error: Unpacking Fail\n");
				return 0;
			}
			printf("Successfully unpack search file\n");
			return 0;
		}
	}

	// If argument are not proper.
	printf("Pass proper argument\n ");
	printf("check -h \n");
	return 0;
}