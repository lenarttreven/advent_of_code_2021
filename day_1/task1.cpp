//
// Created by Lenart Treven on 22.10.22.
//

#include "task1.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int my_sum(vector<int> *list) {
    int sum = 0;
    for (int i: *list) {
        sum = sum + i;
    }
    return sum;
}

int one_pass(string *filename) {
    int num_increases = 0;
    string myText;
    ifstream MyReadFile(*filename);
    int line_num = 0;
    vector<int> current_triple;

    vector<int> last_triple;

    while (getline(MyReadFile, myText)) {
        int number = stoi(myText);
        if (line_num < 3) {
            current_triple.push_back(number);
        } else {
            last_triple = current_triple;
            current_triple.push_back(number);
            current_triple.erase(current_triple.begin());
            if (my_sum(&current_triple) > my_sum(&last_triple)) {
                num_increases = num_increases + 1;
            }
        }
        line_num = line_num + 1;
    }
    return num_increases;
}


vector<int> moving_window(string *filename) {
    string myText;
    ifstream MyReadFile(*filename);
    int line_num = 0;
    vector<int> last_three;
    vector<int> sequence;
    while (getline(MyReadFile, myText)) {
        int number = stoi(myText);
        if (line_num < 2) {
            last_three.push_back(number);
        } else {
            last_three.push_back(number);
            sequence.push_back(my_sum(&last_three));
            last_three.erase(last_three.begin());
        }
        line_num = line_num + 1;
    }
    return sequence;
}

int count_increasing_depths(vector<int> *depths) {
    int num_increases = 0;
    vector<int> depths_val = *depths;
    unsigned long size_of_depths = depths_val.size();
    for (int i = 0; i < size_of_depths; i++) {
        if (depths_val[i] < depths_val[i + 1]) {
            num_increases = num_increases + 1;
        }
    }
    return num_increases;
}