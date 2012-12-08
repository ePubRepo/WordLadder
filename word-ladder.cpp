/**
 * File: word-ladder.cpp
 * ---------------------
 * Implements a program to find word ladders connecting pairs of words.
 */

#include <iostream>
#include <string>
#include <cmath>
using namespace std;

#include "console.h"
#include "lexicon.h"
#include "strlib.h"
#include "simpio.h"
#include "vector.h"
#include "queue.h"

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

static string getWord(Lexicon& english, string prompt) {
    while (true) {
        string response = trim(toLowerCase(getLine(prompt)));
        if (response.empty() || english.contains(response)) return response;
        cout << "Your response needs to be an English word, so please try again." << endl;
    }
}

string getStrByAscii(int ascii) {
    char W = static_cast<char>(ascii);
    return string(1, W);
}

//  Construct strings that are one char different from the target word
//  and store them
void findWordsDifferingByOneChar(Lexicon &english, const string &startWord,
                                 Vector<string> &possibleWords) {
    for (int i = 0; i < startWord.size(); i++) {
        for (int ascii = 97; ascii <= 122; ascii++) {
            string strReplacement = getStrByAscii(ascii);
            string testWord = startWord;
            string wordToTest = testWord.replace(i, 1, strReplacement);
            if (english.contains(wordToTest))
                possibleWords.add(wordToTest);
        }
    }
}

//  Determine number of characters different between two words
int calculateNumDiffChars(const string wordA, const string wordB) {
    int nDiff = 0;
    int minLen = (wordA.length() < wordB.length()) ?
    wordA.length() : wordB.length();

    for (int i = 0; i < minLen; i++) {
        if (wordA[i] != wordB[i]) nDiff++;
    }

    int excess = (wordA.length() - wordB.length());
    return (nDiff + abs(excess));
}

void breadthFirstSearch() {

}

static void generateLadder(Lexicon& english, const string start, const string end) {
    cout << "Here's where you'll search for a word ladder connecting \"" << start << "\" to \"" << end << "\"." << endl;

    //  define a queue of vectors for ladders
    Queue<Vector<string> > ladders;
    
    //  define a set of used words
    Set<string> usedWords;

    //  populate start word into first vector of queue
    string currentLadder = start;

    Vector<string> currentWordLadders;
    findWordsDifferingByOneChar(english, currentLadder, currentWordLadders);

    Queue<string> ladder;
    ladder.enqueue(start);
    while (ladder.size() > 0) {
        string possible = ladder.dequeue();
        if (possible == end)
            return;
        
    }
    
    
    // check to see if top word in queue is the end word
    // if not, populate vector of unused words having one char differences

    //
}

static const string kEnglishLanguageDatafile = "EnglishWords.dat";
static void playWordLadder() {
    Lexicon english(kEnglishLanguageDatafile);
    while (true) {
        string start = getWord(english, "Please enter the source word [return to quit]: ");
        if (start.empty()) break;
        string end = getWord(english, "Please enter the destination word [return to quit]: ");
        if (end.empty()) break;

        std::transform(start.begin(), start.end(), start.begin(), ::tolower);
        std::transform(end.begin(), end.end(), end.begin(), ::tolower);

        if (start.length() != end.length()) {
            cout << "Two words must be same length, else no word ladder exists." << endl;
            return;
        }
        generateLadder(english, start, end);
    }
}

void runProgram() {
    cout << "Welcome to the CS106 word ladder application!" << endl << endl;
    playWordLadder();
    cout << "Thanks for playing!" << endl;
}

int main() {
    // CATCH UNIT TESTS
    // Create a default config object
    Catch::Config config;

    // Configure CATCH to run all tests starting with "mytests"
    config.addTestSpec( "WordLadder/*" );

    // Forward on to CATCH's main using our custom config.
    // This overload doesn't take command line arguments
    // So the config object must be fully set up
    Catch::Main( config );

    // NORMAL CODE
    runProgram();

    return 0;
}

TEST_CASE( "WordLadder/calculateNumDiffChars", "" ) {
    string word1A = "hello";
    string word1B = "jello";
    REQUIRE(calculateNumDiffChars(word1A, word1B) == 1);

    string word2A = "mine";
    string word2B = "dine";
    REQUIRE_FALSE(calculateNumDiffChars(word2A, word2B) == 2);

    string word3A = "hello";
    string word3B = "helloABC";
    REQUIRE(calculateNumDiffChars(word3A, word3B) == 3);
}

TEST_CASE( "WordLadder/getCharByAscii", "" ) {
    REQUIRE(getStrByAscii(65) == "A");
    REQUIRE(getStrByAscii(97) == "a");
    REQUIRE(getStrByAscii(108) == "l");
}

TEST_CASE( "WordLadder/findWordsDifferingByOneChar", "" ) {
    string tStartWord = "hello";
    Vector<string> tPossibleWords;
    Lexicon tEnglish;
    tEnglish.add("mello");
    tEnglish.add("helno");
    tEnglish.add("chicken");
    tEnglish.add("delo");
    tEnglish.add("helln");
    findWordsDifferingByOneChar(tEnglish, tStartWord, tPossibleWords);
    REQUIRE(tPossibleWords.size() == 3);
}
