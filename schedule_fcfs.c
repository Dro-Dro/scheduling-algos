// First-come, first-served (FCFS), which schedules tasks in the order in which they request the CPU.
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
  insert(currHeadPtr, newTask);
}

// fcfs schedules based on first come first serve
void schedule () {
    reverse();
    struct node *temp;
    temp = l_head;

    while (temp != NULL) {
        run(temp->task, temp->task->burst);
        temp = temp->next;
    }
    // printf("Time with dispatcher = %d \n", time + dis);
    // double avg = (1.0) * (time / (time + dis));
    // printf("CPU Utilization: %f percent \n", avg);
}