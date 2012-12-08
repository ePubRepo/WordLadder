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

string getLadderAsString(const Vector<string> &ladder) {
    string str;
    for (int i = 0; i < ladder.size(); i++) {
        str += ladder.get(i) + " ";
    }
    str.replace(str.length() - 1, 1, "");
    return str;
}

Vector<string> createWordLadder(Lexicon& english,
                                const string start,
                                const string end,
                                Queue<Vector<string> > &ladders,
                                Set<string> &usedWords) {
    while (!ladders.isEmpty()) {
        Vector<string> currentLadder = ladders.dequeue();
        string lastWord = currentLadder.get(currentLadder.size() - 1);

        for (int i = 0; i < lastWord.size(); i++) {
            for (int ascii = 97; ascii <= 122; ascii++) {
                string strReplacement = getStrByAscii(ascii);
                string testWord = lastWord;
                string wordToTest = testWord.replace(i, 1, strReplacement);
                if (english.contains(wordToTest)
                    && !usedWords.contains(wordToTest)) {
                    Vector<string> newLadder = currentLadder;
                    newLadder.add(wordToTest);
                    if (wordToTest == end) {
                        return newLadder;
                    } else {
                        usedWords.add(wordToTest);
                        ladders.enqueue(newLadder);
                    }
                }
            }
        }
    }
    return Vector<string>();
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
    usedWords.add(start);

    Vector<string> finalLadder = createWordLadder(english, start, end, ladders, usedWords);
    if (finalLadder.size() == 0)
        cout << "No Word Ladder Existed" << endl;
    else
        getLadderAsString(finalLadder);
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

TEST_CASE( "WordLadder/getLadderAsString", "" ) {
    Vector<string> ladder1;
    ladder1.add("cat");
    ladder1.add("hat");
    ladder1.add("mat");
    REQUIRE(getLadderAsString(ladder1) == "cat hat mat");

    Vector<string> ladder2;
    ladder2.add("mike");
    ladder2.add("bike");
    ladder2.add("bake");
    REQUIRE(getLadderAsString(ladder2) == "mike bike bake");
}

TEST_CASE( "WordLadder/createWordLadder", "" ) {
    Lexicon tEnglish1;
    tEnglish1.add("cat");
    tEnglish1.add("cut");
    tEnglish1.add("mike");
    tEnglish1.add("but");

    string tStart1 = "cat";
    string tEnd1 = "but";
    Queue<Vector<string> > tLadders1;
    Set<string> tUsedWords1;

    Vector<string> tInitialLadder1;
    tInitialLadder1.add(tStart1);
    tLadders1.enqueue((tInitialLadder1));
    tUsedWords1.add(tStart1);

    Vector<string> tFinalLadder1 = createWordLadder(tEnglish1, tStart1,
                                                    tEnd1, tLadders1, tUsedWords1);
    REQUIRE(getLadderAsString(tFinalLadder1) == "cat cut but");

    Lexicon tEnglish2;
    tEnglish2.add("cat");
    tEnglish2.add("cut");
    tEnglish2.add("mike");
    tEnglish2.add("but");
    tEnglish2.add("work");
    tEnglish2.add("fork");
    tEnglish2.add("form");
    tEnglish2.add("foam");
    tEnglish2.add("flam");
    tEnglish2.add("flay");
    tEnglish2.add("play");

    string tStart2 = "work";
    string tEnd2 = "play";
    Queue<Vector<string> > tLadders2;
    Set<string> tUsedWords2;

    Vector<string> tInitialLadder2;
    tInitialLadder2.add(tStart2);
    tLadders2.enqueue((tInitialLadder2));
    tUsedWords2.add(tStart2);

    Vector<string> tFinalLadder2 = createWordLadder(tEnglish2, tStart2,
                                                    tEnd2, tLadders2, tUsedWords2);
    REQUIRE(getLadderAsString(tFinalLadder2) == "work fork form foam flam flay play");
}