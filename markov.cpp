#include "markov.h"
#include <fstream>
#include <cstdlib>

using namespace std;

// Joins a selected range of words with spaces between them.
string joinWords(const string words[], int startIndex, int count) {
    return "";
}

// Reads words from a file and returns the number read, or -1 on open failure.
int readWordsFromFile(string filename, string words[], int maxWords) {
    return 0;
}

// Stores prefix-suffix pairs and returns the number of entries built.
int buildMarkovChain(const string words[], int numWords, int order,
                     string prefixes[], string suffixes[],
                     int maxChainSize) {
    return 0;
}

// Randomly selects a word that follows the given prefix.
string getRandomSuffix(const string prefixes[], const string suffixes[],
                       int chainSize, string currentPrefix) {
    return "";
}

// Selects a random starting prefix from the chain.
string getRandomPrefix(const string prefixes[], int chainSize) {
    return "";
}

// Generates text by following recorded prefix-suffix transitions.
string generateText(const string prefixes[], const string suffixes[],
                    int chainSize, int order, int numWords) {
    return "";
}