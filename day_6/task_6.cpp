//
// Created by Lenart Treven on 04.11.22.
//

#include "task_6.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;


vector<int> simulation_step(vector<int> *fishes) {
    vector<int> next_day_old;
    vector<int> next_day_new;
    for (int fish: *fishes) {
        if (fish == 0) {
            next_day_old.push_back(6);
            next_day_new.push_back(8);
        } else {
            next_day_old.push_back(fish - 1);
        }
    }
    vector<int> all_fishes = next_day_old;
    all_fishes.insert(all_fishes.end(), next_day_new.begin(), next_day_new.end());
    return all_fishes;
}

vector<int> parse_fish_line(string *line) {
    vector<int> nums;
    for (char c: *line) {
        if (isdigit(c)) {
            nums.push_back((int) c - '0');
        }
    }
    return nums;
}

vector<long int> update_generation(vector<long int> *generation) {
    vector<long int> new_generation(9, 0);
    for (int i = 0; i < 9; i++) {
        if (i == 0) {
            new_generation[8] += (*generation)[0];
            new_generation[6] += (*generation)[0];
        } else {
            new_generation[i - 1] += (*generation)[i];
        }
    }
    return new_generation;
}


long int count_fishes_fast(string *filename, int num_steps) {
    ifstream MyReadFile(*filename);
    string line_text;
    getline(MyReadFile, line_text);
    vector<int> initial_generation = parse_fish_line(&line_text);
    vector<long int> short_generation(9, 0);
    for (long int fish: initial_generation) {
        short_generation[fish] += 1;
    }
    for (long int i = 0; i < num_steps; i++) {
        short_generation = update_generation(&short_generation);
    }
    long int num_fishes = 0;
    for (long int fish: short_generation) {
        num_fishes += fish;
    }
    return num_fishes;
}


int count_fishes(string *filename, int num_steps) {
    ifstream MyReadFile(*filename);
    string line_text;
    getline(MyReadFile, line_text);
    vector<int> initial_generation = parse_fish_line(&line_text);
    for (int i = 0; i < num_steps; i++) {
        initial_generation = simulation_step(&initial_generation);
    }
    return initial_generation.size();
}