#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"
#include "day_4/task_4.h"

using namespace std;

int main() {
    string filename = "../day_4/bingo.txt";
    int result = solve_last_bingo(&filename);
    cout << result << endl;
    return 0;
}
