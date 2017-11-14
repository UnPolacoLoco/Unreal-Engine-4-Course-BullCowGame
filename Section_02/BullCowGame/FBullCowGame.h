/*
The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on Mastermind.
*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

//all variables initialized to zero
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	INVALID,
	OK,
	NOT_ISOGRAM,
	WRONG_LENGHT,
	NOT_LOWERCASE,
	WHITESPACE_ONLY,
	UNSUPPORTED_CHARACTERS,

};

class FBullCowGame
{

public:
	
	FBullCowGame();

	

	int32 GetMaxTries() const;
	int32 GetTotalIncorrect() const;
	int32 GetTotalCorrect() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLenght() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;
	void SetHiddenWordKey(int32);


	void Reset(); //TODO make a more rich return value

	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsLowerCase(FString) const;
	bool IsIsogram(FString) const;

	//see ctor for initialisation
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon = false;
};