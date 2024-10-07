// Shortest-job-first (SJF), which schedules tasks in order of the length of the tasks' next CPU burst.
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

// the current head during adding/inserting operation
struct node *l_head;

// add a task to the list 
void add(char *name, int priority, int burst) {
  //creates the task
  struct task *newTask = malloc(sizeof(struct task));
  struct node **currHeadPtr = &l_head;
  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;
  insert(currHeadPtr, newTask);
}

bool comesBefore(char *a, char *b) { return strcmp(a, b) < 0; }
// based on traverse from list.c
// finds the task whose name comes first in dictionary
Task *pickNextTask() {
  // if list is empty, nothing to do
  if (!l_head)
    return NULL;

  struct node *temp;
  temp = l_head;
  Task *short_sofar = temp->task;

  while (temp != NULL) {
    if (temp->task->burst < short_sofar->burst)
      short_sofar = temp->task;
    else if (temp->task->burst == short_sofar->burst && (comesBefore(temp->task->name, short_sofar->name))) {
        short_sofar = temp->task;
    }
    temp = temp->next;
  }
  // delete the node from list, Task will get deleted later
  delete (&l_head, short_sofar);
  return short_sofar;
}

// sjf schedules based on shortest job first
void schedule () {
    while (l_head != NULL) {
        Task *shortest_sofar = pickNextTask();
        run(shortest_sofar, shortest_sofar->burst);
    }
}