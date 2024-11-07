/* 
 * File:   alice_and_bob.cpp
 * Author: sumandeep
 *
 * Created on 12 August, 2018, 5:43 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <list>

using namespace std;

//#define _DEBUG

/* 
 * function to count number of possible moves in a sequence
 * since we are iterating only once through the sequence
 * the big O complexity is O(n) in number of elements in sequence
 */
int countPossibleMoves(list<bool>& inSequence) {
    // maintain count of moves
    int count = 0;

    // no moves possible
    if (inSequence.size() < 3) {
        return count;
    }

    // iterators representing three consecutive positions in sequence
    std::list<bool>::const_iterator prev, curr, next;

    // initialize iterators
    prev = inSequence.begin();
    curr = prev;
    curr++;
    next = curr;
    next++;

    /* this logic derives from the fact that given the rules of removing element
     * only when it is enclosed with two 0's, removing any element either 0 or 1
     * does not preclude any other removal/move from occurring. in fact removing
     * 1's sometimes open up new moves even immediately earlier in the sequence
     */
    // move through sequence finding moves and incrementing count
    while (next != inSequence.end() && inSequence.size() >= 3) {
        // found possible move
        if (false == *prev && false == *next) {
            // update move counter
            count++;

#ifdef _DEBUG
            cout << "move ";
#endif
            // save current value & remove current
            bool currValue = *curr;
            inSequence.erase(curr);

            // take a step backward (if possible) as new move may have opened up
            // with a possible removal of 1 where prev is now surrounded by 0's
            if (prev != inSequence.begin() && true == currValue) {
#ifdef _DEBUG
                cout << "stepBack ";
#endif
                prev--;
                curr = prev;
                curr++;
                next = curr;
                next++;
            } else { // stay put if can't go back
#ifdef _DEBUG
                cout << "stayPut ";
#endif
                // reevaluate curr & next iterators as list has changed
                curr = prev;
                curr++;
                next = curr;
                next++;
            }

            // go back to beginning of loop
            continue;
        }

        // step ahead along sequence to find more moves
#ifdef _DEBUG
        cout << "stepAhead ";
#endif
        prev++;
        curr = prev;
        curr++;
        next = curr;
        next++;
    }

    return count;
}

/* 
 * function to decide winner based on number of possible moves
 */
void printWinnerName(list<bool>& inSequence) {
    // as Alice is always the first one to make a move
    // even possible moves Bob Wins, odd possible moves Alice wins
    int nMoves = countPossibleMoves(inSequence);
#ifdef _DEBUG
    cout << "nMoves: " << nMoves << endl;
#endif    
    if (nMoves % 2 == 0) {
        cout << "Bob" << endl;
    } else {
        cout << "Alice" << endl;
    }
}

/* 
 * main function to parse input data
 */
int main(int argc, char** argv) {
    // need to have the input file as argument
    if (argc != 2) {
        cout << "Syntax: ./a.out sampleTest.txt" << endl;
        cout << "Please specify input file. Quitting ..." << endl;

        // exit with error
        return -1;
    }

    // open file stream to sample input file
    ifstream input;
    input.open(argv[1], ifstream::in);

    /* the following code assumes the format and contents of the 
     * test case input files are fully correct as specified in document 
     * no checks are done on correctness and validity of data */

    // read number of games
    int g;
    input >> g;
#ifdef _DEBUG
    cout << "g: " << g << endl;
#endif

    for (int iGame = 0; iGame < g; iGame++) {
        // read input sequence length
        int n;
        input >> n;
#ifdef _DEBUG
        cout << "n: " << n << endl;
#endif

        // read input sequence into a linked list
        list<bool> inSequence;
        for (int iData = 0; iData < n; iData++) {
            bool data;
            input >> data;
#ifdef _DEBUG
            cout << data << " ";
#endif

            inSequence.push_back(data);
        }
#ifdef _DEBUG
        cout << endl;
#endif

        // compute and print winner's name
        printWinnerName(inSequence);
    }

    // close file stream
    input.close();

    // exit without error
    return 0;
}
