#include "FBullCowGame.h"
#include <map>
#define TMap std::map

#pragma once
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap <int32, int32> WordLengthToMaxTries = { {3,4},{4,5},{5,6},{6,6},{7,7} };// map of word length and max tries, first int is the word length and the second is the tries for that word length.
	
	return WordLengthToMaxTries[MyHiddenWord.length()];// returns an int value based on the int value gotten from MyHiddenWord.length() aka if MyHiddenWord.length() returns a 3 then the returned value from the map is 4 as that corespondes to the key value of 3
	// remeber maps are paired values!!
	
}
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "nukem";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isn't an isogram  aka if IsIsogram(Guess) is not true then execute the statement.
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) // if the guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}


// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// compare letters against the guess
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
	if (Word.length() <= 1) { return true; }; // treats any input with only 1 charcter as an isogram

	TMap <char, bool> LetterSeen;// creates aka declares a map of chars and bools.

	for (auto Letter : Word) // for all the Letters in Word. auto means the compiler** defines the type automatically which in this case is a char.
	{
		Letter = tolower(Letter);// this makes any input from word lower case so if i put AaB this makes sure that i have aab as each letter is made lowercase
		if (LetterSeen[Letter]) // if letter is in the map we dont have an isogram so return false
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true; // adds letter to map and assigns its key to true so it would been |W| |true| *maps are kinda similar to multidimensional arrays think boxes of columns and rows.
		}
	
	
	
	}



	return true;
}

bool FBullCowGame::IsLowercase(FString guess) const
{
	for (auto Letter : guess)// for all the letters in guess aka check each charcter in the string individualy each run through the loop.
	{
		if (isupper(Letter))//checks if letter is uppercase
		{
			return false;// if isupper returns true aka it found that the letter is uppercase then return false beacuse its NOT lowercase.

		}

	}

	return true;// if no upercase is found return true.
}
