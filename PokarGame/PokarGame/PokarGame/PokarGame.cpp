// PokarGame.cpp : main project file.


#include "stdafx.h"
#include "conio.h"
#include "iostream"
#include "PokarGame.h"
#include <stdlib.h>

using namespace std;


int main(array<System::String ^> ^args)
{

	bool quit_game = false;



	while (!quit_game){

		int end_game = false;
		int playerBookCn = 0, computerBookCn = 0;
		bool player_turn = true, go_fish = false;
		char *name;
		Location playerPos(0, 34), computerPos(0, 9);
		Deck **main_deck = getFullDeck(),//main deck bidimensional array
			playerDeck, computerDeck,
			*playerBooks = (Deck*)malloc(sizeof(Deck)),
			*computerBooks = (Deck*)malloc(sizeof(Deck));


		Console::Title = "Poker Game - Go Fish";
		Console::Clear();
		playerBooks->clear();
		computerBooks->clear();

		drawGameTitle(20, 15);

		name = getName(20, 25);

		//Shuffle deck
		shuffle_card(main_deck, 1000);

		//Assigncards to each player
		dealCards(CARDS_SZ, &playerDeck, &computerDeck, main_deck);

		while (!end_game){

			Console::Clear();

			//WRITE GAME TITLE
			drawGameTitle(20, 2);

			/*
				VERIFY IF PLAYERS REQUIRE CARDS FROM DECK
				*/

			//COMPUTER
			if (getDeckSz(&computerDeck) == 0){
				Console::CursorVisible = false;
				Console::ForegroundColor = ConsoleColor::Yellow;
				write_msg("<<<<COMPUTER DO NOT HAVE MORE CARDS>>>>", 0, 20);
				getch();

				if (!resizeDeck(CARDS_SZ, &computerDeck, main_deck)){
					Console::ForegroundColor = ConsoleColor::Red;
					write_msg("<<<<THERE IS NO MORE CARDS AVAILABLE TO FISH>>>>", 0, 20);
					getch();
					end_game = true;//End of game
					break;//Exit while loop
				}
				Console::CursorVisible = true;
				Console::ResetColor();
			}

			//PLAYER
			if (getDeckSz(&playerDeck) == 0){
				Console::CursorVisible = false;
				Console::ForegroundColor = ConsoleColor::Yellow;
				write_msg("<<<<YOU DO NOT HAVE MORE CARDS>>>>", 0, 20);
				getch();
				write_msg("<<<<PRESS ANY KEY TO FISH>>>>", 0, 20);
				getch();

				if (!resizeDeck(CARDS_SZ, &playerDeck, main_deck)){
					Console::ForegroundColor = ConsoleColor::Red;
					write_msg("<<<<THERE IS NO MORE CARDS AVAILABLE TO FISH>>>>", 0, 20);
					getch();
					end_game = true;
					break;//Exit while loop
				}
				Console::CursorVisible = true;
				Console::ResetColor();
			}

			/*
				DRAW PLAYERS DECK
				*/

			//DRAW - PLAYER DECK
			drawPlayerDeckInfo(name, &playerDeck, playerPos, false, playerBookCn);
			if (findFinishedBook(&playerDeck, playerBooks)){//Count how many books are finished
				Console::CursorVisible = false;
				playerBookCn++;
				write_msg(">>>>PLAYER HAS FINISH A BOOK<<<<", 0, 20);
				getch();
				write_msg("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tt\t\t\t\t\t\t\t", 0, 20);
				Console::CursorVisible = true;
				drawPlayerDeckInfo(name, &playerDeck, playerPos, false, playerBookCn);
			}

			//DRAW - COMPUTER DECK
			drawPlayerDeckInfo("Computer", &computerDeck, computerPos, true, computerBookCn);
			if (findFinishedBook(&computerDeck, computerBooks)){//Count how many books are finished
				Console::CursorVisible = false;
				computerBookCn++;
				write_msg(">>>>COMPUTER HAS FINISH A BOOK<<<<", 0, 20);
				getch();
				write_msg("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tt\t\t\t\t\t\t\t", 0, 20);
				Console::CursorVisible = true;
				drawPlayerDeckInfo("Computer", &computerDeck, computerPos, true, computerBookCn);
			}




			if (player_turn){
				/*
					PLAYER TURNS
				*/

				if (getDeckSz(&computerDeck) > 0){
					Deck *d = (Deck*)malloc(sizeof(Deck));
					int rank_value = 0;
					//Ask only there's 				
					rank_value = askForRankValue(0, 33);



					if (getDeckSz(&computerDeck) > 0 & computerDeck.getFacesOf(rank_value, d)){
						//Add cards to the player deck 
						playerDeck.addDeck(d);
						d = NULL;
						free(d);
					}
					else{
						//PLAYER GOES FISH!
						player_turn = playerGoesFish(name, rank_value, &playerDeck, main_deck, 0, 20);
					}

				}

			}
			else{
				/*
					COMPUTER TURNS
				*/

				if (getDeckSz(&computerDeck) > 0){
					
					int rnk_value;
					char *rnd_card = getRndRankFrom(&computerDeck);
					char question[255];

					sprintf(question, "Do you have card(s) with %s?", rnd_card);

					if (askYesOrNo(question, 0, 17)){
						Deck *usr_deck = (Deck*)malloc(sizeof(Deck));
						rnk_value = convertRankToInt(rnd_card);

						usr_deck->clear();

						if (playerDeck.getFacesOf(rnk_value, usr_deck)){
							computerDeck.addDeck(usr_deck);
						}
						else{
							goto_xy(0, 17);
							cout << "\t\t\t\t\t\t\t\t\t\t\t";
							goto_xy(0, 17);
							cout << ">>>>You do NOT HAVE card(s) with " << rnd_card << " <<<<";
							getch();
						}

					}
					else{

						//COMPUTER GOES FISH!
						//If computer got the asked ran then player turns is false
						player_turn = !playerGoesFish("Computer", rnk_value, &computerDeck, main_deck, 0, 20);

					}
				}
			}

		}

		//FREE RESOURCES
		free(main_deck);
		free(playerBooks);
		free(computerBooks);

		Console::CursorVisible = true;
		Console::Clear();
		drawGameTitle(20, 15);

		if (playerBookCn > computerBookCn){
			Console::ForegroundColor = ConsoleColor::Green;
			write_msg("<<<< YOU WON >>>>", 20, 25);
		}
		else{
			Console::ForegroundColor = ConsoleColor::Yellow;
			write_msg("<<<< COMPUTER WINS >>>>", 20, 25);
		}
		Console::ResetColor();

		quit_game = !askYesOrNo("YOU WANNA A PLAY AGAIN ? ", 20, 28);

	}
	Console::Clear();
	Console::CursorVisible = false;
	drawGameTitle(20, 15);
	write_msg("Developed by : MrAlex6204", 20, 25);
	write_msg("email : engineer.vera@yahoo.com", 20, 26);

	getch();

	return 0;
}
