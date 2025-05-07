#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include<algorithm>

using namespace std;

struct Process {
    int id;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    cout << "Enter total number of processes (maximum 20): ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "P[" << processes[i].id << "]:" << endl;
        cout << "Burst time: ";
        cin >> processes[i].burst_time;
        cout << "Arrival time: ";
        cin >> processes[i].arrival_time;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    int time_quantum;//determinses how long a process can run before being preempted
    cout << "Enter Time Quantum: ";
    cin >> time_quantum;

    queue<int> ready_queue;
    int current_time = 0;
    int completed = 0;
    vector<bool> in_queue(n, false);

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), [](const Process &a, const Process &b) {
        return a.arrival_time < b.arrival_time;
    });

    // Enqueue processes that have arrived at time 0
    for (int i = 0; i < n; ++i) {
        if (processes[i].arrival_time <= current_time && !in_queue[i]) {
            ready_queue.push(i);
            in_queue[i] = true;
        }
    }

    while (completed != n) {
        if (ready_queue.empty()) {
            current_time++;
            for (int i = 0; i < n; ++i) {
                if (processes[i].arrival_time <= current_time && !in_queue[i] && processes[i].remaining_time > 0) {
                    ready_queue.push(i);
                    in_queue[i] = true;
                }
            }
            continue;
        }

        int idx = ready_queue.front();
        ready_queue.pop();

        int exec_time = min(time_quantum, processes[idx].remaining_time);
        processes[idx].remaining_time -= exec_time;
        current_time += exec_time;

        // Enqueue processes that have arrived during the execution
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && !in_queue[i] && processes[i].remaining_time > 0) {
                ready_queue.push(i);
                in_queue[i] = true;
            }
        }

        if (processes[idx].remaining_time == 0) {
            processes[idx].completion_time = current_time;
            processes[idx].turnaround_time = processes[idx].completion_time - processes[idx].arrival_time;
            processes[idx].waiting_time = processes[idx].turnaround_time - processes[idx].burst_time;
            completed++;
        } else {
            ready_queue.push(idx);
        }
    }

    double total_waiting_time = 0;
    double total_turnaround_time = 0;

    cout << "\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &proc : processes) {
        cout << "P[" << proc.id << "]\t"
             << proc.arrival_time << "\t\t"
             << proc.burst_time << "\t\t"
             << proc.waiting_time << "\t\t"
             << proc.turnaround_time << "\n";
        total_waiting_time += proc.waiting_time;
        total_turnaround_time += proc.turnaround_time;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << (total_waiting_time / n) << endl;
    cout << "Average Turnaround Time: " << (total_turnaround_time / n) << endl;

    return 0;
}
