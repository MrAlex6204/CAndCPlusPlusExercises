
#include "iostream"
#include <stdlib.h>
#include <time.h>
//Card face chars
#define EMPTY -1
#define CHR_CLUB (char)05
#define CHR_SPADES (char)06
#define CHR_HEARTS (char)03
#define CHR_DIAMONDS (char)04
#define COLUMNS 13
#define ROWS 4
#define CARDS_SZ 7

time_t t;


using namespace std;
using namespace System;

typedef struct location_s{
	int x;
	int y;

	location_s(){//struct constructor
		x = 0;
		y = 0;
	}

	location_s(int x, int y){//overloaded struct constructor
		this->x = x;
		this->y = y;
	}


}Location;

//Define cards suit types
typedef enum suit_s{
	CLUB = 0,
	SPADES = 1,
	HEARTS = 2,
	DIAMONDS = 3
} SuitType;

//Define card structure info
typedef struct cards_s{

	SuitType suit;
	int face;
	struct cards_s *next;//Pointer to the next card in the list


	cards_s(){
		this->clear();
	}

	void draw(int x, int  y, bool hidden){//Draw card in the output
		ConsoleColor clr = Console::ForegroundColor;
		char suit_chr;
		char left_suit_text[15],
			right_suit_text[15];

		switch (this->suit)
		{
		case CLUB:
			suit_chr = CHR_CLUB;
			break;
		case SPADES:
			suit_chr = CHR_SPADES;
			break;
		case HEARTS:
			suit_chr = CHR_HEARTS;
			clr = ConsoleColor::Red;
			break;
		case DIAMONDS:
			suit_chr = CHR_DIAMONDS;
			clr = ConsoleColor::Red;
			break;
		}

		if (hidden){
			sprintf(left_suit_text, "|%c%c     |\n", '+', '+');
			sprintf(right_suit_text, "|     %c%c|\n", '+', '+');
			clr = ConsoleColor::Gray;
		}
		else{
			if (this->face == 1){//A
				sprintf(left_suit_text, "|%c%c     |\n", suit_chr, 'A');
				sprintf(right_suit_text, "|     %c%c|\n", suit_chr, 'A');
			}
			else if (this->face == 11){//J
				sprintf(left_suit_text, "|%c%c     |\n", suit_chr, 'J');
				sprintf(right_suit_text, "|     %c%c|\n", suit_chr, 'J');
			}
			else if (this->face == 12){//K
				sprintf(left_suit_text, "|%c%c     |\n", suit_chr, 'Q');
				sprintf(right_suit_text, "|     %c%c|\n", suit_chr, 'Q');
			}
			else if (this->face == 13){//Q
				sprintf(left_suit_text, "|%c%c     |\n", suit_chr, 'K');
				sprintf(right_suit_text, "|     %c%c|\n", suit_chr, 'K');
			}
			else if (this->face == 10){//The 10
				sprintf(left_suit_text, "|%d%c    |\n", this->face, suit_chr);
				sprintf(right_suit_text, "|    %d%c|\n", this->face, suit_chr);
			}
			else{//Any other number
				sprintf(left_suit_text, "|%d%c     |\n", this->face, suit_chr);
				sprintf(right_suit_text, "|     %d%c|\n", this->face, suit_chr);
			}
		}

		if (this->face != EMPTY){

			//Draw card
			Console::SetCursorPosition(x, y++);
			Console::ForegroundColor = clr;
			printf("+-------+\n");

			Console::SetCursorPosition(x, y++);
			printf("%s", left_suit_text);

			Console::SetCursorPosition(x, y++);
			printf("|       |\n");

			Console::SetCursorPosition(x, y++);
			printf("%s", right_suit_text);

			Console::SetCursorPosition(x, y++);
			printf("+-------+\n");
			Console::ResetColor();
		}

	}

	bool hasNext(){
		//Returns true/false if node has next value		
		return (this->next != NULL);
	}

	void clear(){
		this->face = EMPTY;
		this->next = NULL;

	}

	void push(cards_s *node){
		cards_s *head = this, *tail = node;

		tail->next = NULL;

		if (this->face != EMPTY){
			while (head->hasNext()){//Find tail
				//Move to the next item 
				head = head->next;
			}

			head->next = tail;//Set to the last node a new tail
		}
		else{
			memcpy(this, tail, sizeof(cards_s));
		}
	}

	void addDeck(cards_s *deck){
		cards_s *ptr_head = deck;

		if (ptr_head->face != EMPTY){
			//Copy the full deck if has more that one card
			do{
				cards_s *item = ptr_head->clone();
				this->push(item);
				ptr_head = ptr_head->next;
			} while (ptr_head != NULL);

		}

	}

	void pop(cards_s *node){

		if (node->hasNext()){
			//Copy addr from next slot data
			cards_s *remove_node = node->next;

			//Copy data from the next node to the current node addr.
			memcpy(node, node->next, sizeof(cards_s));

			//Remove addr from memory slot of the next node that's already duplicated and is pointing to the next node						
			free(remove_node);

		}
		else {

			cards_s *ptr_head = this;

			if (this == node){
				this->face = EMPTY;
			}
			else{
				while (ptr_head != NULL && ptr_head->hasNext()){
					if (ptr_head->next == node){
						cards_s *remove_node = ptr_head->next;
						free(remove_node);
						ptr_head->next = NULL;
					}
					ptr_head = ptr_head->next;

				}
			}

		}


	}

	cards_s* clone(){
		cards_s *cpy = (cards_s*)malloc(sizeof(cards_s));

		memcpy(cpy, this, sizeof(cards_s));

		return cpy;
	}

	void drawDeck(int x, int y, bool hidden){//Draw all the list from the current node
		cards_s *head = this;
		int counter = 0;

		//Clear
		Console::SetCursorPosition(x, y);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t");
		Console::SetCursorPosition(x, y + 1);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t");
		Console::SetCursorPosition(x, y + 2);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t");
		Console::SetCursorPosition(x, y + 3);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t");
		Console::SetCursorPosition(x, y + 4);
		printf("\t\t\t\t\t\t\t\t\t\t\t\t");


		if (this->face != EMPTY){
			while (head->hasNext()){
				head->draw(x, y, hidden);
				head = head->next;//Move to the next item from the list
				x += 4;
			}
			head->draw(x, y, hidden);//Draw the tail item
		}

	}

	bool equals(cards_s *card){
		//Return true/false if two cards are equals
		return (this->face == card->face && this->suit == card->suit);
	}

	bool contains(cards_s *card){
		cards_s *head = this;

		//Loop in the linked list
		while (head->hasNext()){
			if (head->equals(card)){
				return true;//Return true & exit function
			}
			else{
				head = head->next;
			}
		}

		if (head->equals(card)){//Compare the tail item
			return true;//Return true & exit
		}

		return false;//Return false because card was not found in the deck
	}

	bool getFacesOf(int face, cards_s *deck){
		cards_s *head = this;
		bool bfaces = false;

		deck->clear();

		//Loop in the linked list
		while (head->hasNext()){

			if (head->face == face){
				cards_s *node = head->clone();
				deck->push(node);
				bfaces = true;//Return true & exit function
				this->pop(head);
			}
			else{
				head = head->next;
			}

		}

		if (head->face == face){//Compare the tail item
			cards_s *node = head->clone();
			deck->push(node);
			bfaces = true;//Return true & exit
			this->pop(head);
		}

		return bfaces;//Return false because face was not found in the deck
	}


} Card;

//Define a
typedef cards_s Deck;

Deck** getFullDeck(){

	Deck **suits = (Card**)malloc(sizeof(Card*)*ROWS);

	for (int r = 0; r < ROWS; r++){
		suits[r] = (Card*)malloc(sizeof(Card)*COLUMNS);

		for (int c = 0; c < COLUMNS; c++){

			switch (r)
			{
			case CLUB:
				suits[r][c].suit = suit_s::CLUB;
				break;
			case SPADES:
				suits[r][c].suit = suit_s::SPADES;
				break;
			case HEARTS:
				suits[r][c].suit = suit_s::HEARTS;
				break;
			case DIAMONDS:
				suits[r][c].suit = suit_s::DIAMONDS;
				break;
			}

			suits[r][c].face = c + 1;

		}

	}


	return suits;
}

char* getName(int x, int y){
	char *name = (char*)malloc(255);
	Console::SetCursorPosition(x, y);
	cout << "Enter your name : ";
	Console::ForegroundColor = ConsoleColor::Red;
	cin >> name;
	Console::ResetColor();

	return name;
}

void write_msg(const char *text, int x, int y){
	Console::SetCursorPosition(x, y);
	cout << "\t\t\t\t\t\t\t\t\t\t\t\t\t\t";
	Console::SetCursorPosition(x, y);
	cout << text;
}

void shuffle_card(Deck **main_deck, int seed){
	int row1 = 0, col1 = 0;
	int row2 = 0, col2 = 0;
	Card c1, c2;
	time_t seconds;
	time(&seconds);
	srand((unsigned int)seconds);

	for (int n = 0; n < seed; n++){
		row1 = rand() % ROWS;
		col1 = rand() % COLUMNS;

		row2 = rand() % ROWS;
		col2 = rand() % COLUMNS;

		c1 = main_deck[row1][col1];
		c2 = main_deck[row2][col2];
		//Swap
		main_deck[row1][col1] = c2;
		main_deck[row2][col2] = c1;


	}

}

void drawGameTitle(int x, int y){

	int t[6][20] = {//Title char map
		{ 218, 196, 196, 196, 191, 197, 197, 197, 218, 196, 196, 196, 191, 197, 197, 197, 218, 191, 00, 000 },
		{ 179, 218, 196, 191, 179, 197, 197, 197, 179, 218, 196, 196, 217, 197, 197, 197, 179, 179, 00, 000 },
		{ 179, 179, 197, 192, 197, 196, 196, 191, 179, 192, 196, 196, 194, 194, 196, 196, 180, 192, 196, 191 },
		{ 179, 179, 218, 196, 180, 218, 191, 179, 179, 218, 196, 196, 197, 180, 196, 196, 180, 218, 191, 179, },
		{ 179, 192, 193, 196, 179, 192, 217, 179, 179, 179, 197, 197, 179, 192, 196, 196, 179, 179, 179, 179, },
		{ 192, 196, 196, 196, 193, 196, 196, 217, 192, 217, 197, 197, 192, 193, 196, 196, 193, 217, 192, 217, },
	};

	for (int r = 0; r < 6; r++){
		Console::SetCursorPosition(x, y + r);
		for (int c = 0; c < 20; c++){
			Console::ForegroundColor = ConsoleColor::Magenta;
			if (t[r][c] == 197){
				Console::ForegroundColor = ConsoleColor::DarkMagenta;
			}
			cout << (char)t[r][c];
		}
	}
	Console::ResetColor();
}

void goto_xy(int x, int y){
	Console::SetCursorPosition(x, y);
}

int getDeckSz(Deck *deck){
	int counter = 0;
	Card *head = deck;

	if (head->face != EMPTY){

		while (head->hasNext()){
			head = head->next;
			counter++;
		}
		counter++;
	}

	return counter;
}

int askForRankValue(int x, int y){//Ask for a rank value
	int n = 0;
	char value[255];
	bool exit = false;
	do{
		goto_xy(x, y);
		cout << "\t\t\t\t\t\t\t\t\t\t";//Clear line text
		goto_xy(x, y);
		cout << "What rank are you loonking for ? >";
		cin >> value;

		if (*value == 'A' || *value == 'a'){
			n = 1;
		}
		else if (*value == 'J' || *value == 'j'){
			n = 11;
		}
		else if (*value == 'Q' || *value == 'q'){
			n = 12;
		}
		else if (*value == 'K' || *value == 'k'){
			n = 13;
		}
		else{
			n = atoi(value);
		}

		if (!(n > 0 && n <= 13)){//If value not in range
			goto_xy(x, y);
			cout << "\t\t\t\t\t\t\t\t\t\t";//Clear line text
			goto_xy(x, y);
			cout << "<<<<<<INVALID RANK VALUE>>>>>>";
			getch();
		}
		else{
			exit = true;
		}

	} while (!exit);//Repeat while 

	return n;

}

char* getRndRankFrom(Deck *deck){
	char *chr_value = (char*)malloc(10);
	int counter = 0;
	int total_cards = getDeckSz(deck);
	int num = 0;

	srand((unsigned)&t);

	if (total_cards > 0){
		num = (rand() % total_cards) + 1;//Get random number between total deck cards
	}
	else{
		num = 1;
	}
	Card *ptr_head = NULL;

	do{
		if (ptr_head == NULL){
			ptr_head = deck;//Return back to the first position
		}
		else{
			ptr_head = ptr_head->next;//Move to the next position
		}

		counter++;
	} while (counter != num);

	switch (ptr_head->face)
	{

	case 1:
		sprintf(chr_value, "%c", 'A');
		break;
	case 11:
		sprintf(chr_value, "%c", 'J');
		break;
	case 12:
		sprintf(chr_value, "%c", 'Q');
		break;

	case 13:
		sprintf(chr_value, "%c", 'K');
		break;
	default:
		sprintf(chr_value, "%d", ptr_head->face);
		break;

	}

	return chr_value;
}

int convertRankToInt(char *chr_value){
	int value = 0;

	switch (*chr_value)
	{

	case 'A':
		value = 1;
		break;
	case 'J':
		value = 11;
		break;
	case 'Q':
		value = 12;
		break;

	case 'K':
		value = 13;
		break;
	default:
		value = atoi(chr_value);
		break;
	}

	return value;
}

void drawPlayerDeckInfo(char *player_name, Deck *deck, Location pos, bool hiddenCard, int bookCn){
	//Deck info
	goto_xy(pos.x, pos.y);
	cout << "Player : " << player_name;
	deck->drawDeck(pos.x, pos.y + 1, hiddenCard);
	goto_xy(pos.x, pos.y + 6);
	cout << getDeckSz(deck) << " Card(s)\t";
	cout << bookCn << " Book(s) Finished";
}

bool askYesOrNo(const char *question, int x, int y){
	char ans;

	do{

		goto_xy(x, y);
		cout << "\t\t\t\t\t\t\t\t\t\t\t";
		goto_xy(x, y);
		printf(question);
		ans = (char)getch();

	} while (!(ans == 'n' || ans == 'N' || ans == 'y' || ans == 'Y'));

	if (ans == 'Y' || ans == 'y'){
		return true;
	}
	else{
		return false;
	}

}

int countMainDeck(Deck **main_deck){
	int counter = 0;

	for (int r = 0; r < ROWS; r++){
		for (int c = 0; c < COLUMNS; c++){
			if (main_deck[r][c].face != EMPTY){
				counter++;
			}
		}
	}

	return counter;
}

Card* getCardFromDeck(Card **main_deck, Card *c){
	int iRow = 0, iCol = 0;
	c->clear();
	while (iRow < ROWS){
		iCol = 0;
		while (iCol < COLUMNS){

			if (main_deck[iRow][iCol].face != EMPTY){
				//Copy value				
				memcpy(c, &main_deck[iRow][iCol], sizeof(Card));
				//Clear value from array
				main_deck[iRow][iCol].face = EMPTY;

				return c;//Return pointer
			}


			iCol++;
		}
		iRow++;
	}
}

bool resizeDeck(int cards_qty, Card *player, Deck **main_deck){
	bool resized = false;

	//If get more cards from deck when user doesn't have cards
	if (countMainDeck(main_deck) > 0){
		for (int i = 0; i < cards_qty; i++){
			Deck *newCard = (Deck*)malloc(sizeof(Deck));
			getCardFromDeck(main_deck, newCard);
			player->push(newCard);
		}
		resized = true;
	}

	return resized;
}

void dealCards(int cards_qty, Deck *player1, Deck *player2, Deck **main_deck){

	//Assigncards to each player
	for (int n = 0; n < cards_qty; n++){

		Card *player1_card = (Card*)malloc(sizeof(Card));
		Card *player2_card = (Card*)malloc(sizeof(Card));

		//Player#1
		getCardFromDeck(main_deck, player1_card);
		//Player#2
		getCardFromDeck(main_deck, player2_card);

		//Add card to the Deck
		player1->push(player1_card);
		player2->push(player2_card);

	}

}

bool playerGoesFish(const char* name, int askedRank, Deck *playerDeck, Deck **main_deck, int x, int y){
	Card *card = (Card*)malloc(sizeof(Card));
	card->clear();
	goto_xy(0, 20);
	printf("|------- ------- ------- ------- ------- -------|\n");
	printf("|------- ------- ------- ------- ------- -------|\n");
	printf("\t\t%s, Lets play Go Fish\n", name);
	printf("|------- ------- ------- ------- ------- -------|\n");
	printf("|------- ------- ------- ------- ------- -------|\n");
	printf("            <<<<PRESS ANY KEY TO FISH>>>>        \n");

	Console::CursorVisible = false;
	getch();
	Console::CursorVisible = true;

	//Get a card from Deck
	getCardFromDeck(main_deck, card);

	playerDeck->push(card);//Add Card to player deck

	//Verify y player got the requested rank value
	return card->face == askedRank;//Returns true if asked face was found in the main deck
}

int countFaceOf(int face_value, Deck *playerDeck){
	Card *ptrHead = playerDeck;
	int counter = 0;

	do{
		if (ptrHead->face == face_value){
			counter++;
		}
		ptrHead = ptrHead->next;
	} while (ptrHead != NULL);

	return counter;
}

bool findFinishedBook(Deck *playerDeck, Deck *book){
	bool bBookFound = false;
	Card *ptrHead = playerDeck;

	do{
		int counter = countFaceOf(ptrHead->face, playerDeck);

		if (counter == 4){
			playerDeck->getFacesOf(ptrHead->face, book);
			bBookFound = true;
			counter = 0;
			ptrHead = playerDeck;//Slide back and tray again
		}
		else{

			ptrHead = ptrHead->next;
		}


	} while (ptrHead != NULL);

	return bBookFound;
}

