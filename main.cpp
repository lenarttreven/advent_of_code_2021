#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"
#include "day_4/task_4.h"
#include "day_5/task_5.h"
#include "day_6/task_6.h"
#include "day_7/task_7.h"

using namespace std;

int main() {
    string filename = "../day_7/input.txt";
    int result = align_weighted_position_cost(&filename);
    cout << result << endl;
//    vector<int> test = {1, 58};
//    cout << compute_median(&test) << endl;
    return 0;
}