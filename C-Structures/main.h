
//File mode
const char *WRITE_MODE		= "w";
const char *READ_MODE		= "r";
const char *APPEND_MODE 	= "a";

const char *HIDE_CURSOR 	= "\e[?25l";
const char *SHOW_CURSOR		= "\e[?25h";

#define HIDE() printf("\e[?25l")
#define SHOW() printf("\e[?25h")

const char *DATA_FILE_NAME = "island.dat";//File path

typedef struct island {
	char name[100];
	char opens[100];
	char closes[100];
	struct island *next;
} island;

typedef enum MENU_OPTION_e {
    NEW_ISAND		= 49,	//PAD NUM1
    LIST_ALL		= 50,	//PAD NUM2
    DELETE_DAT_FILE	= 51,	//PAD NUM3
    QUIT			= 52	//PAD NUM4
} MENU_OPTION;

island* createNode(char *name);
island* appendNode(island **headNode,island *item);
MENU_OPTION mainMenuOption(MENU_OPTION *option);
void saveToFileNodeInfo(island *headNode,FILE *fsw);
void loadFromFileNodeInfo(island **headNode,FILE *fsr);
void displayNodeInfo(island *headNode);
void captureInfo(island **headNode);
void memReleaseNode(island **headNode);
void clscr();
const char* padding(char *text,char *chr,int width);
const char* trimChar(char **text,const char chr);
////////////////////////////////////////////////////////////////////////////////////////////////

island* createNode(char *name) {
	island *ptr = malloc(sizeof(island));


	strcpy(ptr->name,name);
	strcpy(ptr->opens,"09:00");
	strcpy(ptr->closes,"17:00");
	ptr->next = NULL;

	return ptr;
}

void displayNodeInfo(island *headNode) {

	island *i = headNode;
	char *name = calloc(100,sizeof(char));

	printf("\n\n\t\t\t%s\n",padding("","-",60));
	printf("%65s\n","LIST OF ISLANDS");
	printf("\t\t\t%s\n",padding("","-",60));
	
	printf("\t\t\t%-20s | %-20s | %-20s \n","Name","Open","Close");
	printf("\t\t\t%s\n",padding("","-",60));

	for(; i != NULL ; i=i->next) {
		memcpy(name,i->name,sizeof( strlen(i->name) ));
		printf("\t\t\t%-20s | %-20s | %-20s \n",
		       trimChar(&name ,'\n'),i->opens,i->closes);
		printf("\t\t\t%s\n",padding("","-",60));

	}
}

island* appendNode(island **headNode,island *node) {

	island *ptrHeadNode = (*headNode);

	node->next=NULL;

	if( (*headNode) == NULL) {

		*headNode = node;

		return node;
	}

	while(ptrHeadNode->next != NULL) {
		ptrHeadNode = ptrHeadNode->next;
	}


	ptrHeadNode->next = node;


	return node;
}

void saveToFileNodeInfo(island *headNode,FILE *fsw) {

	if(fsw!=NULL) {

		island *i = headNode,*node = NULL;


		for(; i != NULL ; i=i->next) {

			node = malloc(sizeof(island));

			memcpy(node,i,sizeof(island));//Copy values from pointer

			node->next = NULL;//Set null next node pointer

			fwrite(node,sizeof(island),1,fsw);//Write pointer to file

			free(node);
		}

		fclose(fsw);
	}

}

void loadFromFileNodeInfo(island **headNode,FILE *fsr) {

	island island_item;

	(*headNode) = NULL;

	if( fsr!=NULL && !feof(fsr) ) {


		while( fread(&island_item,sizeof(island),1,fsr) != 0 ) { //Read node info from file until EOF

			island *node = (island*)malloc(sizeof(island));

			memcpy(node,&island_item,sizeof(island));//Copy island info to node

			appendNode(headNode,node);//Append node to the head node

		}

	}
	fclose(fsr);

}

void captureInfo(island **headNode) {
	island *node;
	char name[100];

	printf("\n\t\t[ CAPTURE ISLAND INFO ]\n");
	printf("\n\n\t\tType the island name\n\t\t> ");

	while(fgets(name,100,stdin)[0] != '\n') {

		node = createNode(name);
		appendNode(headNode,node);
		
		printf("\t\t> ");

	}

}

MENU_OPTION mainMenuOption(MENU_OPTION *option) {

	do {

		clscr();

		printf("\n\n\n");
		printf("\t\t\t***************************************************\n");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*          1. Enter new island                    *\n");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*          2. List all islands entered            *\n");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*          3. Delete dat file                     *\n");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*          4. Q U I T                             *\n");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t*%50s\n","*");
		printf("\t\t\t***************************************************\n");
		//printf("\e[?25l");//Hide cursor
		HIDE();

		*option = (MENU_OPTION)getch();


	} while(*option != NEW_ISAND && *option != LIST_ALL && *option != QUIT && *option != DELETE_DAT_FILE);

	SHOW();
	//printf("\e[?25h");//Show cursor

	return *option;

}

void clscr() {

#if defined(_WIN32) || defined(_WIN64)
	system("cls");
#else
	system("clear");
#endif

}

void memReleaseNode(island **headNode) {

	island *i = *headNode;

	while(i!=NULL) {
		island *tmp = i->next;

		free(i);

		i=tmp;
	}

}

const char* padding(char *text,char *chr,int width) { //R
	char *t = (char*)calloc(width,sizeof(char));
	int i = 0;

	for(i = 0 ; i <=width-1; i++) {
		t[i]= *chr;
	}

	memcpy(t,text,strlen(text));

	return t;
}

const char* trimChar(char **text,const char chr) {
	int i=0,x=0;
	char *tmpText = (char*)calloc(strlen(*text),sizeof(char));

	for(i=0; i<strlen(*text); i++) {

		if((*text)[i] != chr) {
			tmpText[x] = (*text)[i];
			x++;
		}

	}

	tmpText[x] = '\0';

	*text = (char*)calloc(strlen(tmpText)+1,sizeof(char));

	memcpy(*text,tmpText,strlen(tmpText)+1);

	return *text;
}
