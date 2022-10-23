//
// Created by Lenart Treven on 23.10.22.
//

#include "task_3.h"
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

int power(int a, int b) {
    int to_return = 1;
    for (int i = 0; i < b; i++) {
        to_return = to_return * a;
    }
    return to_return;
}

int part_one(string *filename) {
    int num_samples = 0;
    unsigned long string_len = 0;
    vector<int> num_zeros;
    vector<int> num_ones;

    string myText;
    ifstream MyReadFile(*filename);

    while (getline(MyReadFile, myText)) {
        if (num_samples == 0) {
            string_len = myText.size();
            num_zeros.resize(string_len, 0);
            num_ones.resize(string_len, 0);
        }
        num_samples = num_samples + 1;
        for (int i = 0; i < string_len; i++) {
            char c = myText[i];
            if (c == '0') {
                num_zeros[i] = num_zeros[i] + 1;
            } else {
                num_ones[i] = num_ones[i] + 1;
            }
        }
    }


    int gamma_rate = 0;
    int epsilon_rate = 0;

    for (int i = 0; i < string_len; i++) {
        if (num_zeros[i] > num_ones[i]) {
            epsilon_rate = epsilon_rate + power(2, int(string_len) - 1 - i);
        } else {
            gamma_rate = gamma_rate + power(2, int(string_len) - 1 - i);
        }
    }

    return gamma_rate * epsilon_rate;
}