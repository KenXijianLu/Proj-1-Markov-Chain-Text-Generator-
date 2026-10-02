#include "markov.h"
#include <fstream>
#include <cstdlib>

using namespace std;

// Joins a selected range of words with spaces between them.
string joinWords(const string words[], int startIndex, int count) {
    string result = "";

    for (int i = 0; i < count; i++) {
        result += words[startIndex + i];

        if (i < count - 1) {
            result += " ";
        }
    }

    return result;
}

// Reads words from a file and returns the number read, or -1 on open failure.
int readWordsFromFile(string filename, string words[], int maxWords) {
    ifstream file(filename);

    if (!file.is_open()) { 
        return -1;
    }

    int numWords = 0;
    string word;

    while (numWords < maxWords && file >> word) {
        words[numWords++] = word;
    }

    file.close();
    return numWords;
}

// Stores prefix-suffix pairs and returns the number of entries built.
int buildMarkovChain(const string words[], int numWords, int order,
                     string prefixes[], string suffixes[],
                     int maxChainSize) {
    if (order < 1 || order > 3 || numWords <= order || maxChainSize <= 0) {
        return 0;
    }

    int count = 0;

    for (int i = 0; i < numWords - order && count < maxChainSize; i++) {
        prefixes[count] = joinWords(words, i, order);
        suffixes[count] = words[i + order];
        count++;
    }

    return count;
}

// Randomly selects a word that follows the given prefix.
string getRandomSuffix(const string prefixes[], const string suffixes[],
                       int chainSize, string currentPrefix) {
    int matchCount = 0;

    for (int i = 0; i < chainSize; i++) {
        if (prefixes[i] == currentPrefix) {
            matchCount++;
        }
    }

    if (matchCount == 0) {
        return "";
    }

    int pick = rand() % matchCount;
    int matchIndex = 0;

    for (int i = 0; i < chainSize; i++) {
        if (prefixes[i] == currentPrefix) {
            if (matchIndex == pick) {
                return suffixes[i];
            }
            matchIndex++;
        }
    }


    return "";
}

// Selects a random starting prefix from the chain.
string getRandomPrefix(const string prefixes[], int chainSize) {
    if (chainSize <= 0) {
        return "";
    }

    int index = rand() % chainSize;
    return prefixes[index];
}

// Generates text by following recorded prefix-suffix transitions.
string generateText(const string prefixes[], const string suffixes[],
                    int chainSize, int order, int numWords) {
    return "";
}