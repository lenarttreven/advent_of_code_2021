//
// Created by Lenart Treven on 04.11.22.
//

#ifndef ADVENT_OF_CODE_2021_TASK_8_H
#define ADVENT_OF_CODE_2021_TASK_8_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

tuple<vector<string>, vector<string>> parse_seven_segment_line(string *line);
int count_identical_lines(string *filename);
int decode(string *filename);

#endif //ADVENT_OF_CODE_2021_TASK_8_H
