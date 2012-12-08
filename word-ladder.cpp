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
void findWordsDifferingByOneChar(Queue<Vector<string> > ladders,
                                 Lexicon &english,
                                 const string &startWord,
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

static void generateLadder(Lexicon& english, const string start, const string end) {
    cout << "Here's where you'll search for a word ladder connecting \"" << start << "\" to \"" << end << "\"." << endl;

    //  define a set of used words
    Set<string> usedWords;
    
    //  define a queue of vectors to store ladders
    Queue<Vector<string> > ladders;

    //  populate start word into first vector of queue
    Vector<string> initialLadder;
    initialLadder.add(start);

    //  add initial ladder to queue
    ladders.enqueue(initialLadder);

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

TEST_CASE( "WordLadder/getCharByAscii", "" ) {
    REQUIRE(getStrByAscii(65) == "A");
    REQUIRE(getStrByAscii(97) == "a");
    REQUIRE(getStrByAscii(108) == "l");
}

TEST_CASE( "WordLadder/findWordsDifferingByOneChar", "" ) {
    string tStartWord = "hello";
    Queue<Vector<string> > tLadders;
    Vector<string> tPossibleWords;
    Lexicon tEnglish;
    tEnglish.add("mello");
    tEnglish.add("helno");
    tEnglish.add("chicken");
    tEnglish.add("delo");
    tEnglish.add("helln");
    findWordsDifferingByOneChar(tLadders,
                                tEnglish,
                                tStartWord,
                                tPossibleWords);
    REQUIRE(tPossibleWords.size() == 3);
}
