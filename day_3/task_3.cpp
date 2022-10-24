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

vector<vector<int>> filter_by_position(vector<vector<int>> *list_of_bits, int position, int leading_bit) {
    vector<vector<int>> filtered_bits;
    if ((*list_of_bits).size() == 1) {
        return *list_of_bits;
    }
    int num_ones = 0;
    int num_zeros = 0;
    for (vector<int> bit: *list_of_bits) {
        if (bit[position] == 1) {
            num_ones += 1;
        } else {
            num_zeros += 1;
        }
    }
    int deciding_bit = 0;
    if (leading_bit == 0) {
        deciding_bit = (num_ones >= num_zeros) ? 0 : 1;
    } else if (leading_bit == 1) {
        deciding_bit = (num_ones >= num_zeros) ? 1 : 0;
    }

    for (vector<int> bit: *list_of_bits) {
        if (bit[position] == deciding_bit) {
            filtered_bits.push_back(bit);
        }
    }
    return filtered_bits;
}

int from_vec_to_int(vector<int> *vec) {
    int to_return = 0;
    unsigned long len_vec = (*vec).size();
    for (int i = 0; i < len_vec; i++) {
        if ((*vec)[i] == 1) {
            to_return += power(2, int(len_vec) - 1 - i);
        }
    }
    return to_return;
}

int part_two(string *filename) {
    int oxygen_generator = 0;
    int co2_scrubber = 0;

    string myText;
    ifstream MyReadFile(*filename);
    vector<vector<int>> data;
    while (getline(MyReadFile, myText)) {
        vector<int> one_line(0);
        for (char c: myText) {
            one_line.push_back((int) c - '0');
        }
        data.push_back(one_line);
    }
    unsigned long length_of_seq = data[0].size();
    vector<vector<int>> current_data_oxygen = data;
    for (int i = 0; i < length_of_seq; i++) {
        current_data_oxygen = filter_by_position(&current_data_oxygen, i, 1);
    }
    vector<int> oxygen_generator_vec = current_data_oxygen[0];

    vector<vector<int>> current_data_co2 = data;
    for (int i = 0; i < length_of_seq; i++) {
        current_data_co2 = filter_by_position(&current_data_co2, i, 0);
    }
    vector<int> co2_scrubber_vec = current_data_co2[0];
    oxygen_generator = from_vec_to_int(&oxygen_generator_vec);
    co2_scrubber = from_vec_to_int(&co2_scrubber_vec);
    return oxygen_generator * co2_scrubber;
};
