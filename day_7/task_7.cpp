//
// Created by Lenart Treven on 04.11.22.
//

#include "task_7.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


vector<int> parse_integers(string *line, char separator = ',') {
    vector<int> to_return;
    string current_num_in_string;
    for (char c: *line) {
        if (c == separator) {
            to_return.push_back(stoi(current_num_in_string));
            current_num_in_string = "";
        } else {
            current_num_in_string.push_back(c);
        }
    }
    to_return.push_back(stoi(current_num_in_string));
    return to_return;
}


int compute_median(vector<int> *elems) {
    unsigned num_elems = (*elems).size();
    sort((*elems).begin(), (*elems).end());
    if (num_elems % 2 == 0) {
        return ((*elems)[num_elems / 2 - 1] + (*elems)[num_elems / 2]) / 2;
    } else {
        return (*elems)[num_elems / 2];
    }
}

int move_to_median_cost(vector<int> *elems) {
    int median = compute_median(elems);
    int total_cost = 0;
    for (int i: *elems) {
        total_cost += abs(i - median);
    }
    return total_cost;
}


int align_position_cost(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    getline(MyReadFile, line_text);
    vector<int> positions = parse_integers(&line_text);
    return move_to_median_cost(&positions);
}

int max_el(vector<int> *elems) {
    int cur_max = (*elems)[0];
    for (int i: *elems) {
        if (i > cur_max) {
            cur_max = i;
        }
    }
    return cur_max;
}

int min_el(vector<int> *elems) {
    int cur_min = (*elems)[0];
    for (int i: *elems) {
        if (i < cur_min) {
            cur_min = i;
        }
    }
    return cur_min;
}

int evaluate_cost(vector<int> *positions, int center) {
    int total_cost = 0;
    for (int position: *positions) {
        int dist = abs(position - center);
        total_cost += dist * (dist + 1) / 2;
    }
    return total_cost;
}


int align_weighted_position_cost(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    getline(MyReadFile, line_text);
    vector<int> positions = parse_integers(&line_text);
// Find maximal and minimal element
    int min_possible = min_el(&positions);
    int max_possible = max_el(&positions);
    int min_value = -1;
    for (int i = min_possible; i <= max_possible; i++) {
        int cur_value = evaluate_cost(&positions, i);
        if (cur_value < min_value or min_value == -1) {
            min_value = cur_value;
        }
    }
    return min_value;
}