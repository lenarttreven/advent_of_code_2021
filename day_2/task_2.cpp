//
// Created by Lenart Treven on 22.10.22.
//

#include "task_2.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

tuple<string, int> split(string *line) {
    string direction = "";
    string number = "";
    int number_switch = 0;
    for (char c: *line) {
        if (number_switch == 0) {
            if (c == ' ') {
                number_switch = 1;
            } else {
                direction.push_back(c);
            }
        } else {
            number.push_back(c);
        }
    }
    return make_tuple(direction, stoi(number));
}

int task_2(string *filename) {
    int horizontal_position = 0;
    int depth = 0;

    string myText;
    ifstream MyReadFile(*filename);

    while (getline(MyReadFile, myText)) {
        tuple<string, int> command = split(&myText);
        if (get<0>(command) == "forward") {
            horizontal_position = horizontal_position + get<1>(command);
        } else if (get<0>(command) == "up") {
            depth = depth - get<1>(command);
        } else if (get<0>(command) == "down") {
            depth = depth + get<1>(command);
        }
    }
    return horizontal_position * depth;
}

int task_2_part_2(string *filename) {
    int horizontal_position = 0;
    int depth = 0;
    int aim = 0;

    string myText;
    ifstream MyReadFile(*filename);

    while (getline(MyReadFile, myText)) {
        tuple<string, int> command = split(&myText);
        if (get<0>(command) == "forward") {
            horizontal_position = horizontal_position + get<1>(command);
            depth = depth + get<1>(command) * aim;
        } else if (get<0>(command) == "up") {
            aim = aim - get<1>(command);
        } else if (get<0>(command) == "down") {
            aim = aim + get<1>(command);
        }
    }
    return horizontal_position * depth;
}