#include <iostream>
#include <vector>
#include "day_1/task1.h"
#include "day_2/task_2.h"
#include "day_3/task_3.h"
#include "day_4/task_4.h"
#include "day_5/task_5.h"

using namespace std;

int main() {
    string filename = "../day_5/hydrothermal_vent.txt";
    int result = find_overlapping_points_all(&filename);
    cout << result << endl;
//    for (int i = 0; i <= 4; i++){
//        cout << i << endl;
//    }
    return 0;
}
