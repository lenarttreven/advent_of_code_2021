//
// Created by Lenart Treven on 04.11.22.
//

#ifndef ADVENT_OF_CODE_2021_TASK_6_H
#define ADVENT_OF_CODE_2021_TASK_6_H

#include <vector>

using namespace std;

vector<int> simulation_step(vector<int> *fishes);

int count_fishes(string *filename, int num_steps);

long int count_fishes_fast(string *filename, int num_steps);

#endif //ADVENT_OF_CODE_2021_TASK_6_H
