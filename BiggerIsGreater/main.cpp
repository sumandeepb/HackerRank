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
 * Created on 23 April, 2018, 9:36 AM
 */

#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

string biggerIsGreater(string w) {
    // Complete this function
    int len = w.length();
    bool found = false;
    int j = len - 2;
    while (!found && j >= 0) {
        for (int i = len - 1; i > j; i--) {
            if (w[j] < w[i]) {
                swap (w[j], w[i]);
                found = true;
                sort(w.begin() + j + 1, w.end());
                break;
            }
        }
        j--;
    }
    
    if (!found) {
        return string("no answer");
    } else {
        return w;
    }
}

int main() {
    int T;
    cin >> T;
    for(int a0 = 0; a0 < T; a0++){
        string w;
        cin >> w;
        string result = biggerIsGreater(w);
        cout << result << endl;
    }
    return 0;
}
