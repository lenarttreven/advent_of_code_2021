#include <iostream>
#include <vector>
//#include "day_1/task1.h"
#include "day_2/task_2.h"
//#include "day_3/task_3.h"
#include "day_4/task_4.h"
//#include "day_5/task_5.h"
#include "day_6/task_6.h"
#include "day_7/task_7.h"
#include "day_8/task_8.h"

using namespace std;

int main() {
    string filename = "../day_8/input.txt";
    int out = decode(&filename);
    cout << out << endl;
    return 0;
}