//
// Created by Lenart Treven on 04.11.22.
//

#include "task_8.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <map>


using namespace std;

tuple<vector<string>, vector<string>> parse_seven_segment_line(string *line) {
    vector<string> inputs;
    vector<string> outputs;
    string current_pattern;
    bool in_pattern = false;
    bool after_delimiter = false;
    for (char c: *line) {
        if (c == '|') {
            after_delimiter = true;
        } else if (c == ' ' and in_pattern) {
            if (after_delimiter) {
                outputs.push_back(current_pattern);
            } else {
                inputs.push_back(current_pattern);
            }
            current_pattern = "";
            in_pattern = false;
        } else if (c == ' ') {
            continue;
        } else {
            in_pattern = true;
            current_pattern.push_back(c);
        }
    }
    outputs.push_back(current_pattern);
    return tuple<vector<string>, vector<string>>(inputs, outputs);
}


map<char, char> identify_letters(vector<string> *numbers) {
    map<char, char> decoder;
    vector<string> special_lengths(4);
    vector<string> length_six;
    for (const string &number: *numbers) {
        if (number.size() == 2) {
            special_lengths[0] = number;
        } else if (number.size() == 3) {
            special_lengths[1] = number;
        } else if (number.size() == 4) {
            special_lengths[2] = number;
        } else if (number.size() == 7) {
            special_lengths[3] = number;
        } else if (number.size() == 6) {
            length_six.push_back(number);
        }
    }
    // Identify a and cf
    char encoded_a;
    string encoded_cf;
    for (char cur_letter: special_lengths[1]) {
        if (count(special_lengths[0].begin(), special_lengths[0].end(), cur_letter)) {
            encoded_cf.push_back(cur_letter);
        } else {
            encoded_a = cur_letter;
        }
    }
    decoder[encoded_a] = 'a';
    // Identify bd
    string encoded_bd;
    for (char cur_letter: special_lengths[2]) {
        if (count(special_lengths[0].begin(), special_lengths[0].end(), cur_letter)) {
            continue;
        } else {
            encoded_bd.push_back(cur_letter);
        }
    }
    // Identify eg
    string encoded_eg;
    for (char cur_letter: special_lengths[3]) {
        if (count(special_lengths[1].begin(), special_lengths[1].end(), cur_letter) or
            count(special_lengths[2].begin(), special_lengths[2].end(), cur_letter)) {
            continue;
        } else {
            encoded_eg.push_back(cur_letter);
        }
    }
    // Split cf
    char encoded_c;
    char encoded_f;
    for (char cur_letter: encoded_cf) {
        bool in_all = true;
        for (string cur_six: length_six) {
            if (count(cur_six.begin(), cur_six.end(), cur_letter)) {
                continue;
            } else {
                in_all = false;
            }
        }
        if (in_all) {
            encoded_f = cur_letter;
        } else {
            encoded_c = cur_letter;
        }
    }
    decoder[encoded_c] = 'c';
    decoder[encoded_f] = 'f';
    // Split bd
    char encoded_b;
    char encoded_d;
    for (char cur_letter: encoded_bd) {
        bool in_all = true;
        for (string cur_six: length_six) {
            if (count(cur_six.begin(), cur_six.end(), cur_letter)) {
                continue;
            } else {
                in_all = false;
            }
        }
        if (in_all) {
            encoded_b = cur_letter;
        } else {
            encoded_d = cur_letter;
        }
    }
    decoder[encoded_b] = 'b';
    decoder[encoded_d] = 'd';
    // Split eg
    char encoded_e;
    char encoded_g;
    for (char cur_letter: encoded_eg) {
        bool in_all = true;
        for (string cur_six: length_six) {
            if (count(cur_six.begin(), cur_six.end(), cur_letter)) {
                continue;
            } else {
                in_all = false;
            }
        }
        if (in_all) {
            encoded_g = cur_letter;
        } else {
            encoded_e = cur_letter;
        }
    }
    decoder[encoded_e] = 'e';
    decoder[encoded_g] = 'g';
    return decoder;
}

int from_string_to_num(string *str_num, map<char, char> *decoder) {
    map<string, int> true_decoder;
    true_decoder["abcefg"] = 0;
    true_decoder["cf"] = 1;
    true_decoder["acdeg"] = 2;
    true_decoder["acdfg"] = 3;
    true_decoder["bcdf"] = 4;
    true_decoder["abdfg"] = 5;
    true_decoder["abdefg"] = 6;
    true_decoder["acf"] = 7;
    true_decoder["abcdefg"] = 8;
    true_decoder["abcdfg"] = 9;

    string decoded_str_num;
    for (char c: *str_num) {
        decoded_str_num.push_back((*decoder)[c]);
    }
    sort(decoded_str_num.begin(), decoded_str_num.end());
    return true_decoder[decoded_str_num];
}


int from_line_to_num(vector<string> *line_nums, map<char, char> *decoder) {
    string num;
    for (string str_digit: *line_nums) {
        int cur_num = from_string_to_num(&str_digit, decoder);
        num.push_back('0' + cur_num);
    }
    return stoi(num);
}

int decode(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    int total_sum = 0;
    while (getline(MyReadFile, line_text)) {
        tuple<vector<string>, vector<string>> parsed_line = parse_seven_segment_line(&line_text);
        map<char, char> decoder = identify_letters(&get<0>(parsed_line));
        int cur_num = from_line_to_num(&get<1>(parsed_line), &decoder);
        total_sum += cur_num;
    }
    return total_sum;
}


int count_identical_lines(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    tuple<vector<string>, vector<string>> parsed_line;
    int num_unique_words = 0;
    while (getline(MyReadFile, line_text)) {
        parsed_line = parse_seven_segment_line(&line_text);
        for (const string &cur_word: get<1>(parsed_line))
            if (cur_word.size() == 2 or cur_word.size() == 3 or cur_word.size() == 4 or cur_word.size() == 7) {
                num_unique_words += 1;
            }

    }
    return num_unique_words;
}