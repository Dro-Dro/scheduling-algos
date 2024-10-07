// Round-robin (RR) scheduling, where each task is run for a time quantum (or for the remainder of its CPU burst).
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

// add a task to the list 
void add(char *name, int priority, int burst) {
  //creates the task
  struct task *newTask = malloc(sizeof(struct task));
  struct node **currHeadPtr = &l_head;
  newTask->name = name;
  newTask->priority = priority;
  newTask->burst = burst;
  //using tid as a counter for how much burst is left
  newTask->tid = burst;
  insert(currHeadPtr, newTask);
}

// rr schedules based on round robin giving each task a burst going round till all done
void schedule () {
    reverse();
    struct node *temp;
    temp = l_head;
    while (temp != NULL) {
        
        if (temp->task->tid < quant) {
            run(temp->task, temp->task->tid);
            delete(&l_head, temp->task);
        } else if (temp->task->tid == quant) {
            run(temp->task, quant);
            delete(&l_head, temp->task);
        } else {
            run(temp->task, quant);
            temp->task->tid -= quant;
        }

        if (temp->next == NULL && temp != l_head) {
            temp = l_head;
        } else {
            temp = temp->next;
        }
    }
}