/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: sumandeep
 *
 * Created on 24 April, 2018, 6:43 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the climbingLeaderboard function below.
 */
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {
    /*
     * Write your code here.
     */
    // determine number of unique score tables
    int numUnique = 0;
    int valUnique = -1;
    for (int i = 0; i < scores.size(); i++) {
        if (valUnique != scores[i]) {
            valUnique = scores[i];
            numUnique++;
        }
    }
    //cout << "Total Ranks " << numUnique << endl;

    // initialize just outside the score table
    int lastScore = -1;
    int lastRank = numUnique + 1;
    int lastPos = scores.size();
    vector<int> results;
    for (int j = 0; j < alice.size(); j++) {
        int currScore = alice[j];
        //cout << "currScore " << currScore << endl;
        if (currScore > lastScore) {
            int numUnique = 0;
            int valUnique = lastScore;
            int k = lastPos - 1;
            for (; k >= 0 && currScore >= scores[k]; k--) {
                if (valUnique != scores[k]) {
                    valUnique = scores[k];
                    numUnique++;
                }
            }
            lastRank -= numUnique;
            lastPos = k + 1; // check
            lastScore = currScore;
        }
        
        //cout << "lastRank " << lastRank << endl;
        results.push_back(lastRank);
    }

    return results;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    int scores_count;
    cin >> scores_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string scores_temp_temp;
    getline(cin, scores_temp_temp);

    vector<string> scores_temp = split_string(scores_temp_temp);

    vector<int> scores(scores_count);

    for (int scores_itr = 0; scores_itr < scores_count; scores_itr++) {
        int scores_item = stoi(scores_temp[scores_itr]);

        scores[scores_itr] = scores_item;
    }

    int alice_count;
    cin >> alice_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string alice_temp_temp;
    getline(cin, alice_temp_temp);

    vector<string> alice_temp = split_string(alice_temp_temp);

    vector<int> alice(alice_count);

    for (int alice_itr = 0; alice_itr < alice_count; alice_itr++) {
        int alice_item = stoi(alice_temp[alice_itr]);

        alice[alice_itr] = alice_item;
    }

    vector<int> result = climbingLeaderboard(scores, alice);

    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        fout << result[result_itr];

        if (result_itr != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}
