/**
 * "Virtual" CPU that also maintains track of system time.
 */

#include <stdio.h>
#include "cpu.h"
#include "task.h"

// run this task for the specified time slice
void run(Task *task, int slice) {
    printf("Running task = [%s] [%d] [%d] for %d units.\n",task->name, task->priority, task->burst, slice);
    time += slice;
    // dis++;
    printf("        Time is now: %d\n", time);
}
