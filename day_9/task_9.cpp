//
// Created by Lenart Treven on 07.11.22.
//

#include "task_9.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include<set>

using namespace std;


vector<tuple<int, int>> neighbours_pos(vector<vector<int>> *map, int row, int col) {
    vector<tuple<int, int>> all_neighbours;
    int num_rows = (*map).size();
    int num_columns = (*map)[0].size();
    if (row == 0 and col == 0) {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row + 1, col);
    } else if (row == 0 and col == num_columns - 1) {
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row + 1, col);
    } else if (row == num_rows - 1 and col == 0) {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row - 1, col);
    } else if (row == num_rows - 1 and col == num_columns - 1) {
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row - 1, col);
    } else if (row == 0) {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row + 1, col);
    } else if (row == num_rows - 1) {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row - 1, col);
    } else if (col == 0) {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row + 1, col);
        all_neighbours.emplace_back(row - 1, col);
    } else if (col == num_columns - 1) {
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row + 1, col);
        all_neighbours.emplace_back(row - 1, col);
    } else {
        all_neighbours.emplace_back(row, col + 1);
        all_neighbours.emplace_back(row, col - 1);
        all_neighbours.emplace_back(row + 1, col);
        all_neighbours.emplace_back(row - 1, col);
    }
    return all_neighbours;
}


vector<int> neighbours(vector<vector<int>> *map, int row, int col) {
    vector<int> all_neighbours;
    int num_rows = (*map).size();
    int num_columns = (*map)[0].size();
    if (row == 0 and col == 0) {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
    } else if (row == 0 and col == num_columns - 1) {
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
    } else if (row == num_rows - 1 and col == 0) {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row - 1][col]);
    } else if (row == num_rows - 1 and col == num_columns - 1) {
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row - 1][col]);
    } else if (row == 0) {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
    } else if (row == num_rows - 1) {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row - 1][col]);
    } else if (col == 0) {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
        all_neighbours.push_back((*map)[row - 1][col]);
    } else if (col == num_columns - 1) {
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
        all_neighbours.push_back((*map)[row - 1][col]);
    } else {
        all_neighbours.push_back((*map)[row][col + 1]);
        all_neighbours.push_back((*map)[row][col - 1]);
        all_neighbours.push_back((*map)[row + 1][col]);
        all_neighbours.push_back((*map)[row - 1][col]);
    }
    return all_neighbours;
}


int count_elements_in_basin(vector<vector<int>> *map, int row, int col) {
    set<tuple<int, int>> checked_elements;
    int num_elements_in_basin = 0;
    tuple<int, int> low_element(row, col);
    vector<tuple<int, int>> my_stack = {low_element};
    while (my_stack.size() > 0) {
        tuple<int, int> cur_element = my_stack.back();
        my_stack.pop_back();
        if (checked_elements.find(cur_element) != checked_elements.end()) {
            continue;
        } else {
            checked_elements.insert(cur_element);
            num_elements_in_basin += 1;
            vector<tuple<int, int>> all_neighbours = neighbours_pos(map, get<0>(cur_element), get<1>(cur_element));
            for (tuple<int, int> cur_neigh: all_neighbours) {
                if (checked_elements.find(cur_neigh) != checked_elements.end()) {
                    continue;
                } else if ((*map)[get<0>(cur_neigh)][get<1>(cur_neigh)] == 9) {
                    continue;
                } else {
                    my_stack.push_back(cur_neigh);
                }
            }
        }
    }
    return num_elements_in_basin;
}

int product_of_basins(string *filename) {
    vector<vector<int>> field;
    ifstream MyReadFile(*filename);
    string line_text;
    while (getline(MyReadFile, line_text)) {
        vector<int> cur_row(0);
        for (char c: line_text) {
            cur_row.push_back((int) c - '0');
        }
        field.push_back(cur_row);
    }
    vector<tuple<int, int>> low_points;
    for (int row = 0; row < field.size(); row++) {
        for (int column = 0; column < field[0].size(); column++) {
            vector<int> all_neighbours = neighbours(&field, row, column);
            bool is_low_point = true;
            for (int neighbour: all_neighbours) {
                if (neighbour <= field[row][column]) {
                    is_low_point = false;
                }
            }
            if (is_low_point) {
                low_points.emplace_back(row, column);
            }
        }
    }
    vector<int> basin_elems;
    for (tuple<int, int> low_point: low_points) {
        basin_elems.push_back(count_elements_in_basin(&field, get<0>(low_point), get<1>(low_point)));
    }
    sort(basin_elems.begin(), basin_elems.end(), greater<int>());
    return basin_elems[0] * basin_elems[1] * basin_elems[2];
}


int sum_risk_levels(string *filename) {
    vector<vector<int>> field;
    ifstream MyReadFile(*filename);
    string line_text;
    while (getline(MyReadFile, line_text)) {
        vector<int> cur_row(0);
        for (char c: line_text) {
            cur_row.push_back((int) c - '0');
        }
        field.push_back(cur_row);
    }
    int total_sum_risk_levels = 0;
    for (int row = 0; row < field.size(); row++) {
        for (int column = 0; column < field[0].size(); column++) {
            vector<int> all_neighbours = neighbours(&field, row, column);
            bool is_low_point = true;
            for (int neighbour: all_neighbours) {
                if (neighbour <= field[row][column]) {
                    is_low_point = false;
                }
            }
            if (is_low_point) {
                total_sum_risk_levels += field[row][column] + 1;
            }
        }
    }
    return total_sum_risk_levels;
}