/* La logica del gioco 
il gioco e' basato su Guess th word */



#pragma once

#include <string>

//per usare le classi che usa unreal
using FString = std::string;
using int32 = int;


struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
}; 


enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Lenght,
	Not_Lowercase


};


class FBullCowGame
{
public:
	FBullCowGame(); //Constructor



	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const; 


	void Reset();
	FBullCowCount SubmitValidGuess(FString);
	
private:
	// see constructor for initialisation
	int32 MyCurrentTry; 
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};
