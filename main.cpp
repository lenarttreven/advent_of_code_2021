#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"
#include "day_4/task_4.h"
#include "day_5/task_5.h"
#include "day_6/task_6.h"

using namespace std;

int main() {
    string filename = "../day_6/input.txt";
    long int result = count_fishes_fast(&filename, 256);
    cout << result << endl;
    return 0;
}