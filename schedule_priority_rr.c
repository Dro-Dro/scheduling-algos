// Priority with round-robin, which schedules tasks in order of priority and uses round-robin scheduling for tasks with equal priority.
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "schedulers.h"
#include "list.h"
#include "task.h"
#include "cpu.h"

// quantum used for slice
int quant = 20;
// the current head during adding/inserting operation
struct node *l_head;
// the current rr head
struct node *rrHead;

// based on geeksforgeeks implementation of reverse a linked list
// reverses the task list
void reverse()
{
    struct node *prev;
    struct node *current = l_head;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    l_head = prev;
}

// based on geeksforgeeks implementation of reverse a linked list
// reverses the RR list
void reverseRR()
{
    struct node *prev;
    struct node *current = rrHead;
    struct node *next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    rrHead = prev;
}

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
    else if (temp->task->priority == best_sofar->priority) {
        struct node *fTemp = temp;
        struct task *newTask = malloc(sizeof(struct task));
        struct node *newNode = malloc(sizeof(struct node));
        newTask->name = best_sofar->name;
        newTask->priority = best_sofar->priority;
        newTask->burst = best_sofar->burst;
        newTask->tid = best_sofar->burst;
        newNode->task = newTask;
        struct task *newTask2 = malloc(sizeof(struct task));
        newTask2->name = temp->task->name;
        newTask2->priority = temp->task->priority;
        newTask2->burst = temp->task->burst;
        newTask2->tid = temp->task->burst;
        rrHead = newNode;
        struct node **currRRHead = &rrHead;
        insert(currRRHead, newTask2);
        while (fTemp != NULL) {
            if (fTemp->task->priority == rrHead->task->priority) { insert(currRRHead, fTemp->task); }
        }
        //temp = l_head;

        reverseRR();
        struct node *RRtemp;
        RRtemp = rrHead;
        while (RRtemp != NULL) {
            
            if (RRtemp->task->tid < quant) {
                run(RRtemp->task, RRtemp->task->tid);
                delete(&rrHead, RRtemp->task);
            } else if (RRtemp->task->tid == quant) {
                run(RRtemp->task, quant);
                delete(&rrHead, RRtemp->task);
            } else {
                run(RRtemp->task, quant);
                RRtemp->task->tid -= quant;
            }

            if (RRtemp->next == NULL && RRtemp != rrHead) {
                RRtemp = rrHead;
            } else {
                RRtemp = RRtemp->next;
            }
        }
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