#include <stdio.h>
#include <stdbool.h>
#include<stdlib.h>
struct Process {
    int arrival_time;
    int burst_time;
    int priority;
};

void calculate_FCFS(struct Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    int turnaround_time[n];
    int waiting_time[n];

    turnaround_time[0] = processes[0].burst_time;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        turnaround_time[i] = turnaround_time[i - 1] + processes[i].burst_time;
        waiting_time[i] = turnaround_time[i] - processes[i].arrival_time;
    }

    *avg_turnaround_time = 0;
    *avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        *avg_turnaround_time += turnaround_time[i];
        *avg_waiting_time += waiting_time[i];
    }
    *avg_turnaround_time /= n;
    *avg_waiting_time /= n;
}

void calculate_SJF(struct Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].burst_time > processes[j].burst_time) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int turnaround_time[n];
    int waiting_time[n];

    turnaround_time[0] = processes[0].burst_time;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        turnaround_time[i] = turnaround_time[i - 1] + processes[i].burst_time;
        waiting_time[i] = turnaround_time[i] - processes[i].arrival_time;
    }

    *avg_turnaround_time = 0;
    *avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        *avg_turnaround_time += turnaround_time[i];
        *avg_waiting_time += waiting_time[i];
    }
    *avg_turnaround_time /= n;
    *avg_waiting_time /= n;
}

void calculate_RoundRobin(struct Process processes[], int n, int time_quantum, float *avg_turnaround_time, float *avg_waiting_time) {
    int remaining_time[n];
    for (int i = 0; i < n; i++) {
        remaining_time[i] = processes[i].burst_time;
    }

    int current_time = 0;
    bool done = false;

    while (!done) {
        done = true;
        for (int i = 0; i < n; i++) {
            if (remaining_time[i] > 0) {
                done = false;
                if (remaining_time[i] <= time_quantum) {
                    current_time += remaining_time[i];
                    remaining_time[i] = 0;
                } else {
                    current_time += time_quantum;
                    remaining_time[i] -= time_quantum;
                }
            }
        }
    }

    int turnaround_time[n];
    int waiting_time[n];

    for (int i = 0; i < n; i++) {
        turnaround_time[i] = current_time - processes[i].arrival_time;
        waiting_time[i] = turnaround_time[i] - processes[i].burst_time;
    }

    *avg_turnaround_time = 0;
    *avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        *avg_turnaround_time += turnaround_time[i];
        *avg_waiting_time += waiting_time[i];
    }
    *avg_turnaround_time /= n;
    *avg_waiting_time /= n;
}

void calculate_Priority(struct Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].priority > processes[j].priority) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    int turnaround_time[n];
    int waiting_time[n];

    turnaround_time[0] = processes[0].burst_time;
    waiting_time[0] = 0;

    for (int i = 1; i < n; i++) {
        turnaround_time[i] = turnaround_time[i - 1] + processes[i].burst_time;
        waiting_time[i] = turnaround_time[i] - processes[i].arrival_time;
    }

    *avg_turnaround_time = 0;
    *avg_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        *avg_turnaround_time += turnaround_time[i];
        *avg_waiting_time += waiting_time[i];
    }
    *avg_turnaround_time /= n;
    *avg_waiting_time /= n;
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time, and priority for process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].arrival_time, &processes[i].burst_time, &processes[i].priority);
    }
while(1)
{
    int choice;
    printf("Select scheduling algorithm:\n");
    printf("1. FCFS\n");
    printf("2. SJF\n");
    printf("3. Round Robin\n");
    printf("4. Priority\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    int time_quantum;
    if (choice == 3) {
        printf("Enter time quantum for Round Robin: ");
        scanf("%d", &time_quantum);
    }

    float avg_turnaround, avg_waiting;
    switch (choice) {
        case 1:
            calculate_FCFS(processes, n, &avg_turnaround, &avg_waiting);
            printf("FCFS Average Turnaround Time: %.2f\n", avg_turnaround);
            printf("FCFS Average Waiting Time: %.2f\n", avg_waiting);
            break;
        case 2:
            calculate_SJF(processes, n, &avg_turnaround, &avg_waiting);
            printf("SJF Average Turnaround Time: %.2f\n", avg_turnaround);
            printf("SJF Average Waiting Time: %.2f\n", avg_waiting);
            break;
        case 3:
            calculate_RoundRobin(processes, n, time_quantum, &avg_turnaround, &avg_waiting);
            printf("Round Robin Average Turnaround Time: %.2f\n", avg_turnaround);
            printf("Round Robin Average Waiting Time: %.2f\n", avg_waiting);
            break;
        case 4:
            calculate_Priority(processes, n, &avg_turnaround, &avg_waiting);
            printf("Priority Average Turnaround Time: %.2f\n", avg_turnaround);
            printf("Priority Average Waiting Time: %.2f\n", avg_waiting);
            break;
        case 5: printf("EXITING...\n");
        exit(0);
        
        default:
            printf("Invalid choice!\n");
    }
}
    return 0;
}
