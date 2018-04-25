/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
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
