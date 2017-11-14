/* This is the console executable, that makes use of the BullCow class. 
This acts as the view in a MVC pattern, and is responsible for all user interaction.
For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <chrono>
#include "FBullCowGame.h"





using int32 = int;
using FText = std::string;


void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();
int32 ChooseWordLenght();

FBullCowGame BCGame; //instantiate a new game, which we re-use across plays


int main()
{
	
	do
	{
		PrintIntro();
		PlayGame();
		
	} while (AskToPlayAgain());
	
	return 0;
}

//plays a single game to completion
void PlayGame()
{
	int32 DesiredWordLenght = 0;

	BCGame.Reset();


	DesiredWordLenght = ChooseWordLenght();
	BCGame.SetHiddenWordKey(DesiredWordLenght);

	auto Start = std::chrono::system_clock::now(); //start counting
	
	int32 MaxTries = BCGame.GetMaxTries();
	
	//loop asking for guesses while the game 
	//is NOT won and there are still tries remaining

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();
		

		//Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls << ". Cows = " << BullCowCount.Cows << ".";
	}
	

	std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now() - Start; //stop counting

	PrintGameSummary();

	std::cout << "Elapsed time: " << (int32)elapsed_seconds.count() << " second(s).\n\n";
}

//loop continually until user gets ta valid guess
FText GetValidGuess() 
{
	EGuessStatus Status = EGuessStatus::INVALID;
	FText Guess = "";
	int TriesLeft = BCGame.GetMaxTries() + 1 - BCGame.GetCurrentTry();

	do
	{
		std::cout << "\n\nTries left: " << TriesLeft << std::endl;
		std::cout << "Try " << BCGame.GetCurrentTry()  << ". Enter your guess: ";
		
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::NOT_ISOGRAM:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter isogram, aka a word without repeating letters!\n\n";
			break;
		case EGuessStatus::WRONG_LENGHT:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLenght() << " letter word!\n\n";
			break;
		case EGuessStatus::NOT_LOWERCASE:
			std::cout << "Please enter your word in lowercase!\n\n";
			break;
		default:
			break;
		}

	} while (Status != EGuessStatus::OK);
	
	return Guess;
	

}

void PrintIntro()
{
	std::system("cls");
	std::cout << "\nWelcome to Bulls and Cows!\n" << std::endl;
	std::cout << "\\|/          (__)     c__c            \\|/" << std::endl;
	std::cout << "     `\\------(oo)     (oo)------/'" << std::endl;
	std::cout << "       ||    (__)     (__)    ||" << std::endl;
	std::cout << "       ||v--||    \\|/    ||--W||     \\|/" << std::endl;
	std::cout << "   \\|/\n" << std::endl;
	
}

//ask the user the desired word lenght
int32 ChooseWordLenght()
{

	FString UserChoice;
	int32 DesiredWordLenght;

	do
	{
		std::cout << "\nHow many letters would you like to have your hidden word with? \nChoose a number between 3 and 8: ";
		std::getline(std::cin, UserChoice);
		std::stringstream ss(UserChoice);
		ss >> DesiredWordLenght;

		//DesiredWordLenght = std::stoi(UserChoice);

	} while (DesiredWordLenght > 8 || DesiredWordLenght < 3);

	return DesiredWordLenght;
}


bool AskToPlayAgain()
{
	std::cout << "Would you like to play again (y/n)?\n";
	FText Response = "";

	std::getline(std::cin, Response);

	return ((Response[0] == 'y') || (Response[0] == 'Y'));
	
	
}

void PrintGameSummary()
{
	
	if (BCGame.IsGameWon())
	{
		std::cout << "\n\nCongratulations. You win! It took you " << BCGame.GetCurrentTry()-1 << " tries.\n";
	}
	else
	{
		std::cout << "\n\nYou lost, better luck next time.\n";
	}
}
