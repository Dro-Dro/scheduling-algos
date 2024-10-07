// Priority scheduling, which schedules tasks based on priority.
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
  Task *best_sofar = temp->task;

  while (temp != NULL) {
    if (temp->task->priority > best_sofar->priority)
      best_sofar = temp->task;
    else if (temp->task->priority == best_sofar->priority && (comesBefore(temp->task->name, best_sofar->name))) {
        best_sofar = temp->task;
    }
    temp = temp->next;
  }
  // delete the node from list, Task will get deleted later
  delete (&l_head, best_sofar);
  return best_sofar;
}

// priority schedules based on priority given to each task
void schedule () {
    while (l_head != NULL) {
        Task *bestest_sofar = pickNextTask();
        run(bestest_sofar, bestest_sofar->burst);
    }
}