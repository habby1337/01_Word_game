//bull lettere giuste e posizione giuste
//cow lettere giuste posizione errata

/*
This is the console executable that makes use of the BullCow Class
This acts as the views in a MVC pattern, and is teponsabile for all
user interation. For game logic see the FBullCowGame
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//per usare le classi che usa unreal
using FText = std::string; 
using int32 = int;



using namespace std;


void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummery();



FBullCowGame BCGame;  //Instanza una nuova partita




  // the entry point for our application

int main() 
{

	bool bPlayAgain = false;

	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
		
	} while (bPlayAgain);


	return 0;// exit the application

}


void PrintIntro()
{
	//Introduzione del gico 

	system("cls");
	cout << "Benvenuto su Indovina la parola, un gioco di parole.\n";
	cout << endl;
	cout << "Numero di tentativi "<<BCGame.GetMaxTries()<<"\n";
	cout << endl;
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /-------\\ " << endl;
	cout << "  / | Fede |O            O| Tensi | \\ " << endl;
	cout << " *  |-,--- |     Game     |-------|  * " << endl;
	cout << "    ^      ^              ^      ^ " << endl;
	cout << "Puoi indovinare la parola isogramma con " << BCGame.GetHiddenWordLenght() << " lettere  a cui sto pensando?\n";
	cout << endl;

	return;
}


void PlayGame()
{
	BCGame.Reset();
	
	int32 MaxTries = BCGame.GetMaxTries();

	// cicla chiedendo la parola finche il gioco non si vince o si perde
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{

		FText Guess = GetValidGuess(); 

		// Inserisce il valid guess al gioco e ritorna il contatore
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
			

		cout << "Lettere giuste e posizioni giuste = " << BullCowCount.Bulls<<"\n";
		cout << "Lettere giuste posizioni errate  = " << BullCowCount.Cows << endl;
		cout << endl;

	}

	
	PrintGameSummery();
	return;
}


FText GetValidGuess()
{

	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		// get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Tentativo " << CurrentTry << " su " << BCGame.GetMaxTries() << ". Scrivi la parola: ";
		std::getline(std::cin, Guess);

		// controlla lo status e da feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Wrong_Lenght:
			std::cout << "Perfavore inserisci una parola con " << BCGame.GetHiddenWordLenght() << " lettere.\n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Perfavore inserici una parola senza ripetizioni di lettere.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Perfavore immetti tutta la parola con caratteri minuscoli.\n\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK); // continua a ciclare finche non ci sono piu errori
	return Guess;
	
}


bool AskToPlayAgain()
{
	cout << "Vuoi giocare di nuovo con la stessa parola? (S/N)\n";
	FText Response = "";
	getline(cin, Response);

	
	
	return (Response[0] == 's') || (Response[0] == 'S');
}


void PrintGameSummery()
{
	if (BCGame.IsGameWon())
	{
		cout << endl;
		cout << "BEN FATTO - HAI VINTO \n";
	}
	else
	{
		cout << endl;
		cout << "Ritenta sarai più fortunato\n";
	}
}
