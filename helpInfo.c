#include "header.h"

void helpInfo()
{
		printf("\n-------------------------------------[ File Packer Unpacker ]----------------------------------------------\n\n");
		printf("                   					   Developed by- Marvellous    			                                  \n");
		printf("--------------------------------------------------------------------------------------------------------------\n\n");
		printf("\nApplication defined encryption:- \n\n");
		printf("To Merge(pack)                      : -M        DirectoryName   FileName\n");
		printf("To Split(unpack)                    : -S        FileName        DirectoryName\n");
		printf("\nTo get the specfic File from pack   : -S  -get  packFileName    Foldername 		getFileName1 getFileName2 ...\n");

		printf("\n\nUser defined encryption:--\n\n");
		printf("To Merge(pack)                      : -M        DirectoryName   FileName         key(numberical key)\n");
		printf("To split(unpack)                    : -S        FileName        DirectoryName    key\n");
		printf("\nTo get the specfic File from pack   : -S  -get  -e key   packFileName    Foldername       getFileName1 getFileName2 ...\n");
		printf("\n------------------------------------------------------------------------------------------------------------\n");
}


void displayError(BOOL ret)
{
	switch(ret)
	{
		case ERR_ACCESS : 
							printf("Error: Access denied\n");
							break;
		case ERR_INVALID:
							printf("Error: Invalid file for unpacking\n");
							break;
		case ERR_CREATE : 
							printf("Error: File can't be create\n");
							break;

		case ERR_AUTHENTICATION :
							printf("Error: Incorrect key \n");
							break;
		case FALSE : 	
							printf("Error: Something gone wrong\n");
	}
}