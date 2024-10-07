#include "task.h"

// length of a time quantum
#define QUANTUM 10

// total time ran so far
int time;

// // dispatch time?
// int dis = -1.000;

// run the specified task for the following time slice
void run(Task *task, int slice);
