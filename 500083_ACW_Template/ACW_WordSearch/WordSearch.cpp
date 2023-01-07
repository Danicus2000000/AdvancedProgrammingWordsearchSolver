#include "WordSearch.h"
#include "gridNode.h"
#include <iostream>
#include <fstream>
#include <vector>
#include<string>
using namespace std;

WordSearch::WordSearch(const char * const filename) : simpleGrid(),outputFileName(filename)
{
}
WordSearch::~WordSearch() 
{
}

void WordSearch::readSimplePuzzle() 
{
	ifstream inputStream(puzzleName);//read in each character from the grid as well as the array size
	inputStream >> arraySize;
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			inputStream >> simpleGrid[i][j];
		}
	}
	inputStream.close();
}

void WordSearch::readSimpleDictionary() 
{
	ifstream inputStream(dictionaryName);//open the dictionary and read in each word found in the file
	string wordInFile="";
	while(inputStream >> wordInFile)
	{
		simpleDictionary.push_back(wordInFile);
	}
	inputStream.close();
}

void WordSearch::readAdvancedPuzzle() 
{
	ifstream inputStream(puzzleName);//read in the array size and generate a node for each character in the grid
	inputStream >> arraySize;
	for(int i=0;i<arraySize;i++)
	{
		vector<gridNode> wordToAdd;
		for(int j=0; j<arraySize;j++)
		{
			char letterToAdd;
			inputStream >> letterToAdd;
			wordToAdd.push_back(gridNode(letterToAdd));
		}
		advancedGrid.push_back(wordToAdd);
	}
	inputStream.close();
	for (int i = 0; i < advancedGrid.size(); i++)
	{
		for (int j = 0; j < advancedGrid[i].size(); j++)
		{
			if (i != 0)//add pointers heading in an upward direction accross the wordsearch
			{
				advancedGrid[i][j].setUp(&advancedGrid[i - 1][j]);
			}
			if (i != advancedGrid.size() - 1)//add pointers heading in an downward direction accross the wordsearch
			{
				advancedGrid[i][j].setDown(&advancedGrid[i + 1][j]);
			}
			if (j != 0)//add pointers heading in a leftward direction accross the wordsearch
			{
				advancedGrid[i][j].setLeft(&advancedGrid[i][j - 1]);
			}
			if (j != advancedGrid[i].size() - 1)//add pointers heading in a rightward direction accross the wordsearch
			{
				advancedGrid[i][j].setRight(&advancedGrid[i][j + 1]);
			}
			if (i != 0 && j != 0)//add pointers heading in a up and left direction accross the wordsearch
			{
				advancedGrid[i][j].setUpLeft(&advancedGrid[i - 1][j - 1]);
			}
			if (i != 0 && j != advancedGrid[i].size() - 1)//add pointers heading in a up and right direction accross the wordsearch
			{
				advancedGrid[i][j].setUpRight(&advancedGrid[i - 1][j + 1]);
			}
			if (i != advancedGrid.size() - 1 && j != 0)//add pointers heading in a down and left direction accross the wordsearch
			{
				advancedGrid[i][j].setDownLeft(&advancedGrid[i + 1][j - 1]);
			}
			if (i != advancedGrid.size() - 1 && j != advancedGrid.size() - 1)//add pointers heading in a down and right direction accross the wordsearch
			{
				advancedGrid[i][j].setDownRight(&advancedGrid[i + 1][j + 1]);
			}
		}
	}
}

void WordSearch::readAdvancedDictionary()
{
	//use the simple dictionary reader as we have used the advanced puzzle generation
	ifstream inputStream(dictionaryName);//open the dictionary and read in each word found in the file
	string wordInFile = "";
	while (inputStream >> wordInFile)
	{
		simpleDictionary.push_back(wordInFile);
	}
	inputStream.close();
}

void WordSearch::solvePuzzleSimple() 
{
	for(int i=0; i<9;i++)//loop through each column
	{
		for(int j=0; j<9;j++)//loop through each row
		{
			numberGridCellsVisited++;//increment grid cells visited
			for(int word=0;word<simpleDictionary.size();word++)//loop through each word in the dictionary
			{
				numberEntriesVisited++;//increment entries visited as we visit each word in the dictionary
				if(simpleGrid[i][j]==simpleDictionary[word].at(0))//if the first letter of the grid matches the first letter of a word in the dictionary
				{
					for(int letter=0; letter<simpleDictionary[word].size();letter++)//loop through the letters of the word that could be found
					{
						if (simpleGrid[i + letter][j] != simpleDictionary[word][letter] && simpleGrid[i - letter][j] != simpleDictionary[word][letter] && simpleGrid[i][j + letter] != simpleDictionary[word][letter] && simpleGrid[i][j - letter] != simpleDictionary[word][letter] && simpleGrid[i + letter][j + letter] != simpleDictionary[word][letter] && simpleGrid[i - letter][j - letter] != simpleDictionary[word][letter] && simpleGrid[i + letter][j - letter] != simpleDictionary[word][letter] && simpleGrid[i - letter][j + letter] != simpleDictionary[word][letter])
						{//ensure that the candidate is valid i.e. in any direction there is at least one way that allows the code to continue towards finding the full word
							break;
						}
						else if(letter==simpleDictionary[word].size()-1)//if at any point the nullifying condition is not triggered and we have reached the end of the word
						{
							bool isAlreadyFound = false;//ensures the word is not already found and adds it if it hasn't been found yet
							for(int loop=0; loop<wordsFound.size();loop++)
							{
								if(wordsFound[loop]==simpleDictionary[word])
								{
									isAlreadyFound = true;
									break;
								}
							}
							if (!isAlreadyFound) 
							{
								wordLocationX.push_back(j);//add the word and location to found lists and increment words found
								wordLocationY.push_back(i);
								wordsFound.push_back(simpleDictionary[word]);
								numberWordsFound++;
							}
						}
					}
				}
			}
		}
	}
	for (int i = 0; i < simpleDictionary.size(); i++)//loop through all words in dictionary
	{
		bool isFound = false;
		for (int j = 0; j < wordsFound.size(); j++)//check if the word occurs in found list
		{
			if (wordsFound[j] == simpleDictionary[i])//if it does ensure we do not write it to not found list
			{
				isFound = true;
				break;
			}
		}
		if (!isFound)//if it is not found then add to not found output
		{
			wordsNotFound.push_back(simpleDictionary[i]);
		}
	}
}

void WordSearch::solvePuzzleAdvanced() 
{
	for(int i=0;i<arraySize;i++)//loop through all y values in grid
	{
		for(int j=0;j<arraySize;j++)//loop through all x values
		{
			numberGridCellsVisited++;//increment point on wordsearch visited
			for(int word=0;word<simpleDictionary.size();word++)//loop through all words in dictionary
			{
				numberEntriesVisited++;//increment words visited in dictionary
				if (advancedGrid[i][j].getLetter() == simpleDictionary[word][0])//if the letter checked begins with the same letter the word in the dictionary does
				{
					checkDirection("up", word, i, j);//if so check each direction and see if words can be formed using the pointers (see checkDirection function)
					checkDirection("down", word, i, j);
					checkDirection("left", word, i, j);
					checkDirection("right", word, i, j);
					checkDirection("upleft", word, i, j);
					checkDirection("upright", word, i, j);
					checkDirection("downleft", word, i, j);
					checkDirection("downright", word, i, j);
				}
			}
		}
	}
	for (int i = 0; i < simpleDictionary.size(); i++)//loop through all words in dictionary
	{
		bool isFound = false;
		for (int j = 0; j < wordsFound.size(); j++)//check if the word occurs in found list
		{
			if (wordsFound[j] == simpleDictionary[i])//if it does ensure we do not write it to not found list
			{
				isFound = true;
				break;
			}
		}
		if (!isFound)//if it is not found then add to not found output
		{
			wordsNotFound.push_back(simpleDictionary[i]);
		}
	}
}

void WordSearch::writeResults(const double loadTime, const double solveTime) const 
{
	ofstream outputStream(outputFileName);//output the results in the format that is required
	outputStream << "NUMBER_OF_WORDS_MATCHED " << numberWordsFound << endl << endl;
	outputStream << "WORDS_MATCHED_IN_GRID" << endl;
	for(int i=0;i<wordsFound.size();i++)//outputs all words that where found and the x and y coordinate of their starting letter
	{
		outputStream << wordLocationX[i] << " " << wordLocationY[i] << " " << wordsFound[i] << endl;
	}
	outputStream << endl;
	outputStream << "WORDS_UNMATCHED_IN_GRID" << endl;
	for(int i=0;i<wordsNotFound.size();i++)//outputs all words that where not found
	{
		outputStream << wordsNotFound[i] << endl;
	}
	outputStream << endl;
	outputStream << "NUMBER_OF_GRID_CELLS_VISITED " << numberGridCellsVisited << endl << endl;
	outputStream << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << numberEntriesVisited << endl << endl;
	outputStream << "TIME_TO_POPULATE_GRID_STRUCTURE " << loadTime << endl << endl;
	outputStream << "TIME_TO_SOLVE_PUZZLE " << solveTime;
	outputStream.close();
	
}

/// <summary>
/// Checks the direction requested and attempts to traverse it as required
/// </summary>
/// <param name="directionToCheck">The string representing the direction to check</param>
/// <param name="wordIndex">The index of the word to check for</param>
/// <param name="i">The Y coordinate on the grid</param>
/// <param name="j">The X coordinate on the grid</param>
void WordSearch::checkDirection(const string &directionToCheck, const int wordIndex, const int i,const int j)
{
	const int wordLength = simpleDictionary[wordIndex].size();//get the length of the word to check
	gridNode* currentNode = &advancedGrid[i][j];//stores the current node being checked
	string wordCreation = "";//stores the letters as they are found to see if they create the word in the end
	while (currentNode != nullptr && wordCreation.size() != wordLength)//while we have not hit the edge of the grid or the end of the word
	{
		if (currentNode->getLetter() == simpleDictionary[wordIndex][wordCreation.size()])//if the letter we are looking at is the same as the one listed in this dictionaries word
		{
			wordCreation.push_back(currentNode->getLetter());//push this letter onto the word for later checking
			numberGridCellsVisited++;//increment cells visited as we are about to visit another cell
			if (directionToCheck == "up")//continue to next node based on the direction requested
				currentNode = currentNode->getUp();
			if (directionToCheck == "down")
				currentNode = currentNode->getDown();
			if (directionToCheck == "right")
				currentNode = currentNode->getRight();
			if (directionToCheck == "left")
				currentNode = currentNode->getLeft();
			if (directionToCheck == "upleft")
				currentNode = currentNode->getUpLeft();
			if (directionToCheck == "upright")
				currentNode = currentNode->getUpRight();
			if (directionToCheck == "downleft")
				currentNode = currentNode->getDownLeft();
			if (directionToCheck == "downright")
				currentNode = currentNode->getDownRight();
		}
		else//if the word is not a match break
		{
			break;
		}
	}
	if (wordCreation == simpleDictionary[wordIndex])//if we found the word instead of leaving the loop due to an incorrect word
	{
		wordLocationX.push_back(j);//add the word and location to found lists and increment words found
		wordLocationY.push_back(i);
		wordsFound.push_back(simpleDictionary[wordIndex]);
		numberWordsFound++;
	}
}