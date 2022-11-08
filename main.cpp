#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"
#include "day_4/task_4.h"
#include "day_5/task_5.h"
#include "day_6/task_6.h"
#include "day_7/task_7.h"
#include "day_8/task_8.h"
#include "day_9/task_9.h"

using namespace std;

int main() {
    string filename = "../day_9/input.txt";
    int out = product_of_basins(&filename);
    cout << out << endl;
//    vector<int> myvector = {1, 2, 3, 4, 5};
//    myvector.pop_back();
    return 0;
}