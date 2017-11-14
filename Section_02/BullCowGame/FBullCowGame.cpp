#pragma once
#include "FBullCowGame.h"
#include <map>
#include <iostream>
#include <sstream>

#define TMap std::map

using FString = std::string;
using int32 = int;

//ctor
FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap<int32, int32> WordLenghtToMaxTries = { {3,5}, {4, 6}, {5, 8}, {6, 9}, {7, 11}, {8,13}};

	return WordLenghtToMaxTries[GetHiddenWordLenght()]; 
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLenght() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }



void FBullCowGame::Reset()
{
	bIsGameWon = false;
	MyCurrentTry = 1;

	return;
}


//recieves a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 HiddenWordLenght = MyHiddenWord.length();

	//loop through all letters in the hidden word
	for (int32 i = 0; i < HiddenWordLenght; i++)
	{

		//compare letters in guess against the hidden word
		for (int32 j = 0; j < HiddenWordLenght; j++)
		{
			//if they match
			if (Guess[i] == MyHiddenWord[j])
			{
				//increment bulls if exact place
				if (Guess[i] == MyHiddenWord[i])
				{
					BullCowCount.Bulls++;
				}
					
				//increment cows if letter exists but wrong place
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLenght)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms

	if (Word.length() < 2) { return true; }
	TMap<char, bool> LetterSeen;



	for (auto Letter : Word)  //for all letters of the 'Word'
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) //confirm if its an Isogram
		{ 
			//we do not have an isogram
			return false; 
		}
		else 
		{
			//add the letter to the map
			LetterSeen[Letter] = true;
		}
	}
	

	return true;
}



EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{

	if (!IsIsogram(Guess))//If the guess isnt an isogram, 
	{
		return EGuessStatus::NOT_ISOGRAM;
	} 
	else if (Guess.length() != GetHiddenWordLenght()) //if wrong lenght
	{
		return EGuessStatus::WRONG_LENGHT;
	}
	else if (!IsLowerCase(Guess)) //if not lowercase 
	{
		return EGuessStatus::NOT_LOWERCASE;
	}
	else
	{
		return EGuessStatus::OK;
	}
		
	

}

//sets hidden word based on desired user word lenght
void FBullCowGame::SetHiddenWordKey(int32 value)
{
	TMap<int32, FString> HiddenWords = { { 3, "aim" },{ 4, "soja" },{ 5, "swarm" },{ 6, "racism" },{ 7, "isogram" },{ 8, "organism" } };

	MyHiddenWord = HiddenWords[value];

}





bool FBullCowGame::IsLowerCase(FString Guess) const
{
	if (Guess.length() == 0) { return false; }
	for (auto c : Guess)
	{
		if (!islower(c))
			return false;
	}
	return true;
}
