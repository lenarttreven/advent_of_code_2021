//
// Created by Lenart Treven on 24.10.22.
//

#include "task_4.h"
#include <utility>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>


using namespace std;

class Board {
public:
    int n = 5;
    vector<vector<int>> table_numbers;
    vector<vector<int>> table_appearances;

    Board(vector<vector<int>> x, vector<vector<int>> y) {
        table_numbers = std::move(x);
        table_appearances = std::move(y);
    }

    void add_number(int number);

    bool won();

    int score(int k);
};

int Board::score(int k) {
    int score_sum = 0;
    for (int i = 0; i < Board::n; i++) {
        for (int j = 0; j < Board::n; j++) {
            if (Board::table_appearances[i][j] == 0) {
                score_sum += Board::table_numbers[i][j];
            }
        }
    }
    return score_sum * k;
}


void Board::add_number(int number) {
    for (int i = 0; i < Board::n; i++) {
        for (int j = 0; j < Board::n; j++) {
            if (Board::table_numbers[i][j] == number) {
                Board::table_appearances[i][j] = 1;
            }
        }
    }
}

bool Board::won() {
    bool won = false;
    // Check if we have full row
    for (int row = 0; row < Board::n; row++) {
        bool win = true;
        for (int column = 0; column < Board::n; column++) {
            if (Board::table_appearances[row][column] == 0) {
                win = false;
            }
        }
        if (win) { won = true; }
    }
    // Check if we have full column
    for (int column = 0; column < Board::n; column++) {
        bool win = true;
        for (int row = 0; row < Board::n; row++) {
            if (Board::table_appearances[row][column] == 0) {
                win = false;
            }
        }
        if (win) { won = true; }
    }
    return won;
}


int solve_bingo(string *filename) {
    int n = 5;
    string line_text;
    ifstream MyReadFile(*filename);

    getline(MyReadFile, line_text);
    stringstream line_stream(line_text);
    vector<int> played_numbers;

    string part_of_line;

    while (getline(line_stream, part_of_line, ',')) {
        played_numbers.push_back(stoi(part_of_line));
    }

    vector<vector<int>> table_appearances;
    for (int i = 0; i < n; i++) {
        vector<int> one_row(0);
        for (int j = 0; j < n; j++) {
            one_row.push_back(0);
        }
        table_appearances.push_back(one_row);
    }


    vector<Board> boards;

    while (getline(MyReadFile, line_text)) {
        vector<vector<int>> table;
        for (int i = 0; i < n; i++) {
            vector<int> line(0);
            getline(MyReadFile, line_text);
            stringstream line_stream(line_text);
            while (getline(line_stream, part_of_line, ' ')) {
                if (!part_of_line.empty()) {
                    line.push_back(stoi(part_of_line));
                }
            }
            table.push_back(line);
        }
        boards.emplace_back(table, table_appearances);
    }
    int winning_index = -1;
    int winning_board = -1;
    int winning_score = -1;

    for (int i = 0; i < played_numbers.size(); i++) {
        for (int j = 0; j < boards.size(); j++) {
            boards[j].add_number(played_numbers[i]);
            if (boards[j].won()) {
                winning_index = i;
                winning_board = j;
                winning_score = boards[j].score(played_numbers[i]);
                break;
            }
        }
        if (winning_index != -1) {
            break;
        }
    }
    return winning_score;
}

int solve_last_bingo(string *filename) {
    int n = 5;
    string line_text;
    ifstream MyReadFile(*filename);

    getline(MyReadFile, line_text);
    stringstream line_stream(line_text);
    vector<int> played_numbers;

    string part_of_line;

    while (getline(line_stream, part_of_line, ',')) {
        played_numbers.push_back(stoi(part_of_line));
    }

    vector<vector<int>> table_appearances;
    for (int i = 0; i < n; i++) {
        vector<int> one_row(0);
        for (int j = 0; j < n; j++) {
            one_row.push_back(0);
        }
        table_appearances.push_back(one_row);
    }


    vector<Board> boards;

    while (getline(MyReadFile, line_text)) {
        vector<vector<int>> table;
        for (int i = 0; i < n; i++) {
            vector<int> line(0);
            getline(MyReadFile, line_text);
            stringstream line_stream(line_text);
            while (getline(line_stream, part_of_line, ' ')) {
                if (!part_of_line.empty()) {
                    line.push_back(stoi(part_of_line));
                }
            }
            table.push_back(line);
        }
        boards.emplace_back(table, table_appearances);
    }
    vector<int> already_won_boards(boards.size(), 0);
    int total_number_of_won_boards = 0;

    int winning_index = -1;
    int winning_board = -1;
    int winning_score = -1;

    for (int i = 0; i < played_numbers.size(); i++) {
        for (int j = 0; j < boards.size(); j++) {
            boards[j].add_number(played_numbers[i]);
            if (boards[j].won()) {
                if (total_number_of_won_boards == boards.size()-1 and already_won_boards[j] == 0){
                    winning_index = i;
                    winning_board = j;
                    winning_score = boards[j].score(played_numbers[i]);
                    break;
                }
                if (already_won_boards[j] == 0){
                    total_number_of_won_boards += 1;
                    already_won_boards[j] = 1;
                }
            }
        }
        if (winning_score != -1){
            break;
        }
    }
    return winning_score;
}