/*
    Copyright 2018 Sumandeep Banerjee (sumandeep.banerjee@gmail.com)

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/* 
 * File:   main.cpp
 * Author: sumandeep
 *
 * Created on 23 April, 2018, 12:29 PM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split_string(string);

/*
 * Complete the highestValuePalindrome function below.
 */
string highestValuePalindrome(string s, int n, int k) {
    /*
     * Write your code here.
     */
    int numBalance = k;
    int numChanges = 0;
    vector<int> changePosLst;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1]) {
            if (s[i] > s[n - i - 1]) {
                s[n - i - 1] = s[i];
            } else {
                s[i] = s[n - i - 1];
            }

            numChanges++;
            numBalance--;
            if (numChanges > k) {
                return string("-1");
            }

            if (s[i] != '9') {
                changePosLst.push_back(i);
            }
        }
    }

    int numChangesBar9 = changePosLst.size();
    int j = 0; // index of change pos list
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != '9') { // need to upgrade to 9
            if (j < numChangesBar9 && i == changePosLst[j]) { // if position has already been changed
                // costs only one balance
                if (numBalance > 0) {
                    s[i] = '9';
                    s[n - i - 1] = '9';
                    numBalance--;
                    j++;
                } else {
                    break;
                }
            } else {
                if (numBalance >= 2) {
                    s[i] = '9';
                    s[n - i - 1] = '9';
                    numBalance -= 2;                    
                }
            }
        }
    }
    
    if (numBalance > 0 && (n%2 == 1)) { // if balance left and palindrome size is odd
        if (s[n / 2] != '9') {
            s[n / 2] = '9';
            numBalance--;
        }
    }

    return s;
}

int main() {
    ofstream fout(getenv("OUTPUT_PATH"));

    string nk_temp;
    getline(cin, nk_temp);

    vector<string> nk = split_string(nk_temp);

    int n = stoi(nk[0]);

    int k = stoi(nk[1]);

    string s;
    getline(cin, s);

    string result = highestValuePalindrome(s, n, k);

    fout << result << "\n";

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
