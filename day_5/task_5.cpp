//
// Created by Lenart Treven on 25.10.22.
//

#include "task_5.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


vector<int> parse_line(string *line) {
    vector<int> numbers;
    string cur_num = "";
    bool in_number = false;
    for (char c: *line) {
        if (in_number and isdigit(c)) {
            cur_num.push_back(c);
        } else if (in_number and not isdigit(c)) {
            numbers.push_back(stoi(cur_num));
            cur_num = "";
            in_number = false;
        } else if (not in_number and isdigit(c)) {
            cur_num.push_back(c);
            in_number = true;
        }
    }
    if (in_number) {
        numbers.push_back(stoi(cur_num));
    }
    return numbers;
}

bool filter_coordinates(vector<int> *nums) {
    if ((*nums)[0] == (*nums)[2] or (*nums)[1] == (*nums)[3]) {
        return true;
    } else {
        return false;
    }
}

vector<vector<int>> prepare_field(vector<vector<int>> *all_inputs) {
    int max_num = 0;
    for (vector<int> &i: *all_inputs) {
        for (int j = 0; j < 4; j++) {
            max_num = max(max_num, i[j]);
        }
    }
    vector<vector<int>> field;
    for (int i = 0; i < max_num + 1; i++) {
        vector<int> line(max_num + 1, 0);
        field.push_back(line);
    }
    return field;
}

vector<vector<int>> prepare_coordinates(vector<int> *line) {
    vector<vector<int>> to_fill;
    if ((*line)[0] == (*line)[2] and (*line)[1] <= (*line)[3]) {
        for (int i = (*line)[1]; i <= (*line)[3]; i++) {
            vector<int> cur_element = {(*line)[0], i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] == (*line)[2] and (*line)[1] > (*line)[3]) {
        for (int i = (*line)[3]; i <= (*line)[1]; i++) {
            vector<int> cur_element = {(*line)[0], i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[1] == (*line)[3] and (*line)[0] <= (*line)[2]) {
        for (int i = (*line)[0]; i <= (*line)[2]; i++) {
            vector<int> cur_element = {i, (*line)[1]};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[1] == (*line)[3] and (*line)[0] > (*line)[2]) {
        for (int i = (*line)[2]; i <= (*line)[0]; i++) {
            vector<int> cur_element = {i, (*line)[1]};
            to_fill.push_back(cur_element);
        }
    }
    return to_fill;
}


vector<vector<int>> prepare_coordinates_full(vector<int> *line) {
    vector<vector<int>> to_fill;
    if ((*line)[0] == (*line)[2] and (*line)[1] <= (*line)[3]) {
        for (int i = (*line)[1]; i <= (*line)[3]; i++) {
            vector<int> cur_element = {(*line)[0], i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] == (*line)[2] and (*line)[1] > (*line)[3]) {
        for (int i = (*line)[3]; i <= (*line)[1]; i++) {
            vector<int> cur_element = {(*line)[0], i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[1] == (*line)[3] and (*line)[0] <= (*line)[2]) {
        for (int i = (*line)[0]; i <= (*line)[2]; i++) {
            vector<int> cur_element = {i, (*line)[1]};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[1] == (*line)[3] and (*line)[0] > (*line)[2]) {
        for (int i = (*line)[2]; i <= (*line)[0]; i++) {
            vector<int> cur_element = {i, (*line)[1]};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] < (*line)[2] and (*line)[1] < (*line)[3]) {
        int diff = (*line)[2] - (*line)[0];
        for (int i = 0; i <= diff; i++) {
            vector<int> cur_element = {(*line)[0] + i, (*line)[1] + i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] < (*line)[2] and (*line)[1] > (*line)[3]) {
        int diff = (*line)[2] - (*line)[0];
        for (int i = 0; i <= diff; i++) {
            vector<int> cur_element = {(*line)[0] + i, (*line)[1] - i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] > (*line)[2] and (*line)[1] < (*line)[3]) {
        int diff = (*line)[0] - (*line)[2];
        for (int i = 0; i <= diff; i++) {
            vector<int> cur_element = {(*line)[0] - i, (*line)[1] + i};
            to_fill.push_back(cur_element);
        }
    } else if ((*line)[0] > (*line)[2] and (*line)[1] > (*line)[3]) {
        int diff = (*line)[0] - (*line)[2];
        for (int i = 0; i <= diff; i++) {
            vector<int> cur_element = {(*line)[0] - i, (*line)[1] - i};
            to_fill.push_back(cur_element);
        }
    }
    return to_fill;
}


int find_overlapping_lines(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    vector<vector<int>> coordinates;

    while (getline(MyReadFile, line_text)) {
        vector<int> current_nums = parse_line(&line_text);
        coordinates.push_back(current_nums);
    }
    // Filter coordinates which are either vertical or horizontal
    vector<vector<int>> filtered_coordinates;
    for (vector<int> &i: coordinates) {
        if (filter_coordinates(&i)) {
            filtered_coordinates.push_back(i);
        }
    }
    vector<vector<int>> field = prepare_field(&filtered_coordinates);

    for (vector<int> &cur_coordinates: filtered_coordinates) {
        vector<vector<int>> to_fill = prepare_coordinates(&cur_coordinates);
        for (vector<int> &pair: to_fill) {
            int x = pair[0];
            int y = pair[1];
            field[x][y] += 1;
        }
    }
    int overlap_num = 0;
    for (vector<int> &row: field) {
        for (int column: row) {
            if (column >= 2) {
                overlap_num += 1;
            }
        }
    }
    return overlap_num;
}

int find_overlapping_points_all(string *filename) {
    ifstream MyReadFile(*filename);
    string line_text;
    vector<vector<int>> coordinates;

    while (getline(MyReadFile, line_text)) {
        vector<int> current_nums = parse_line(&line_text);
        coordinates.push_back(current_nums);
    }

    vector<vector<int>> field = prepare_field(&coordinates);

    for (vector<int> &cur_coordinates: coordinates) {
        vector<vector<int>> to_fill = prepare_coordinates_full(&cur_coordinates);
        for (vector<int> &pair: to_fill) {
            int x = pair[0];
            int y = pair[1];
            field[x][y] += 1;
        }
    }
    int overlap_num = 0;
    for (vector<int> &row: field) {
        for (int column: row) {
            if (column >= 2) {
                overlap_num += 1;
            }
        }
    }
    return overlap_num;
}
