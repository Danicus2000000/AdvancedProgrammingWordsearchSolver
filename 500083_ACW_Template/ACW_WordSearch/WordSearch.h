#pragma once
#include <vector>
#include <string>
#include "gridNode.h"
class WordSearch 
{
	char simpleGrid[9][9];
	std::vector<std::string> simpleDictionary;
	std::vector<std::string> wordsFound;
	std::vector<int> wordLocationX;
	std::vector<int> wordLocationY;
	std::vector<std::string> wordsNotFound;
	std::vector<std::vector<gridNode>> advancedGrid;
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	const char* outputFileName;
	int arraySize = 9;
	int numberWordsFound = 0;
	int numberGridCellsVisited = 0;
	int numberEntriesVisited = 0;

public:
	explicit WordSearch(const char * const filename);
	~WordSearch();
	void readSimplePuzzle();
	void readSimpleDictionary();
	void readAdvancedPuzzle();
	void readAdvancedDictionary();
	void solvePuzzleSimple();
	void solvePuzzleAdvanced();
	void writeResults(const	double loadTime, const double solveTime) const;
	void checkDirection(const std::string &directionToCheck,const int word, const int i, const int j);//Method added to reduce code required to check directions
	WordSearch(const WordSearch& o) : simpleGrid(), outputFileName(o.outputFileName) //copy constructor and operator for wordsearch to satisfy parasoft issues
	{ 
	}
	WordSearch& operator=(const WordSearch& o)
	{
		if (&o != this) 
		{
			simpleDictionary = o.simpleDictionary;
			advancedGrid = o.advancedGrid;
			arraySize = o.arraySize;
			dictionaryName = o.dictionaryName;
			numberEntriesVisited = o.numberEntriesVisited;
			numberGridCellsVisited = o.numberGridCellsVisited;
			numberWordsFound = o.numberWordsFound;
			outputFileName = o.outputFileName;
			puzzleName = o.puzzleName;
			wordLocationX = o.wordLocationX;
			wordLocationY = o.wordLocationY;
			wordsFound = o.wordsFound;
			wordsNotFound = o.wordsNotFound;
		}
		return *this; 
	}
};

