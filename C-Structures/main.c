#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#include "main.h"


int main(int argc, char *argv[]) {

	MENU_OPTION menu_option = -1;
	island *headNode=NULL;
	int KEY;

	while(mainMenuOption(&menu_option)!= QUIT) {

		headNode = NULL;		
		KEY = -1;
		
		clscr();//Clear screen	

		switch(menu_option) {//Execute the menu option
		
			FILE *fsw;
			FILE *fsr;			
			
			case NEW_ISAND:
				
				fsw = fopen(DATA_FILE_NAME,APPEND_MODE);
				captureInfo(&headNode);
				saveToFileNodeInfo(headNode,fsw);				
				
				break;

			case LIST_ALL:
				
				fsr = fopen(DATA_FILE_NAME,READ_MODE);
				loadFromFileNodeInfo(&headNode,fsr);
				displayNodeInfo(headNode);
				printf("\n\t\t\t\t\t [ PRESS ANY KEY TO RETURN ] \n");
				
				HIDE();
				getch();
				SHOW();
				
				break;
			
			case DELETE_DAT_FILE:
				
				printf("\n\n\t\t\t  Delete dat file [ Y|N ] : ");
				KEY = getch();
				
				
				if(KEY  == ((int)'y') || KEY == ((int)'Y') ){
					fsw = fopen(DATA_FILE_NAME,WRITE_MODE);
					fclose(fsw);
					printf("\n\n\t\t\t[ FILE DELTED SUCCESSFULLY ]\n");
				}else{
					printf("\n\n\t\t\t   [ ACTION CANCELED ]\n");
				}
				getch();
				break;
				
			default:
				printf("\n\n\t\t\t   [ INVALID OPTION ]\n");		
				getch();
				break;

		}
		
		memReleaseNode(&headNode);

	}






//	captureInfo(&headNode);
//	displayNodeInfo(headNode);
//
//	saveToFileNodeInfo(headNode,fsw);
//	printf("\n[ Saved to file successfully! ]\n");
//
//
//	fsr = fopen("island.dat","r");
//	printf("\n>>>>>Loading from file<<<<<\n");
//	loadFromFileNodeInfo(&node,fsr);
//	displayNodeInfo(node);

	return 0;
}


