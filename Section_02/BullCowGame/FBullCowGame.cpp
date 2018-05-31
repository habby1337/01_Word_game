#pragma once

#include "FBullCowGame.h"
#include <map>

//unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{ 
	TMap<int32, int32>WorldLentghToMaxTries{ {3, 5}, {4, 6}, {5,7}, {6,9}, {7,20}};
	return WorldLentghToMaxTries[MyHiddenWord.length()];
}


void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "cane"; //questo deve essere un isogramma
	MyHiddenWord = HIDDEN_WORD;
	
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLenght())
	{
		return EGuessStatus::Wrong_Lenght;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}


//Revies a valid guess, increment turn, and retun count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); //assuming same lenght as guess

	//loop through all letters in the hidden world
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess word
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{ // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else
				{
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}


bool FBullCowGame::IsIsogram(FString Word) const
{
	//tratta le parole 0 e 1 lettere come isogrammi
	if (Word.length() <= 1) { return true; }

	//setup la mappa
	TMap<char, bool> LetterSeen;
	for (auto Letter : Word) //per tutte le lettere di word
	{
		Letter = tolower(Letter); //elencare lettere minuscole e maiuscole
		if (LetterSeen[Letter])
		{ 
			return false; 
		}
		else
		{
			LetterSeen[Letter] = true;
		}	
	}
	return true; //per esempio in casi dove sia implementato /0 o cose simili
}


bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//se le lettere non sono in minuscolo
		{
			return false;
		}
	}
	return true;
}
