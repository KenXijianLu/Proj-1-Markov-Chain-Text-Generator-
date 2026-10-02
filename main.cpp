#include "markov.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Prompts for a whole number in range; returns false if input ends.
bool readInteger(string prompt, int minimum, int maximum, int& value) {
    while (true) {
        cout << prompt;
        int candidate;

        if (!(cin >> candidate)) {
            if (cin.eof()) {
                return false;
            }

            // Resets the input error and discards the rest of the bad line.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a whole number.\n";
            continue;
        }

        // Rejects extra text after the number, such as "2.5" or "3abc".
        string remaining;
        getline(cin, remaining);
        if (remaining.find_first_not_of(" \t\r\v\f") != string::npos) {
            cout << "Please enter a whole number.\n";
            continue;
        }

        if (candidate < minimum || candidate > maximum) {
            cout << "Please enter a number from " << minimum
                 << " to " << maximum << ".\n";
        } else {
            value = candidate;
            return true;
        }
    }
}

// Gets user input, builds the chain, and prints generated text and its word count.
int main() {
    srand(static_cast<unsigned int>(time(0)));
    const int MAX_WORDS = 5000;
    string words[MAX_WORDS];
    string prefixes[MAX_WORDS];
    string suffixes[MAX_WORDS];
    string filename;
    int order = 0;
    int numWords = 0;
    int chainSize = 0;
    while (true) {
        cout << "Enter input filename: ";
        if (!getline(cin, filename)) {
            return 0;
        }

        if (!readInteger("Enter order (1, 2, or 3): ", 1, 3, order)) {
            return 0;
        }

        if (!readInteger(
                "Enter maximum number of words to generate (at least "
                + to_string(order) + "): ",
                order, numeric_limits<int>::max(), numWords)) {
            return 0;
        }
        int count = readWordsFromFile(filename, words, MAX_WORDS);

        if (count == -1) {
            cout << "Could not open the file. Check its name or path and try again.\n\n";
            continue;
        }
        if (count <= order) {
            cout << "The file contains " << count << " words. Order " << order
                 << " requires at least " << order + 1
                 << " training words. Please try again.\n\n";
            continue;
        }
        if (count == MAX_WORDS) {
            cout << "At most " << MAX_WORDS << " input words were used. "
                 << "Additional words, if any, were ignored.\n";
        }
        chainSize = buildMarkovChain(
            words, count, order, prefixes, suffixes, MAX_WORDS);

        if (chainSize <= 0) {
            cout << "No chain entries were built. Please try again.\n\n";
            continue;
        }

        break;
    }
    string output = generateText(
        prefixes, suffixes, chainSize, order, numWords);
    
    int actualWords = 0;

    if (!output.empty()) {
        actualWords = 1;

        for (string::size_type i = 0; i < output.length(); i++) {
            if (output[i] == ' ') {
                actualWords++;
            }
        }
    }

    cout << "\n" << output << "\n\n";
    cout << "Generated " << actualWords
         << " of at most " << numWords << " words.\n";

    if (actualWords < numWords) {
        cout << "Stopped early: the current prefix has no successor.\n";
    }

    return 0;
}
