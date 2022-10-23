#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"

using namespace std;

int main() {
    string filename = "../day_3/task_3_part_1.txt";
    int result = part_two(&filename);
    cout << result << endl;
    return 0;
}
