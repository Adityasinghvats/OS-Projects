#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

struct process{
    int id;
    int burst_time;
    int priority;
};

int main(){
    int n, i;
    cout<<"Enter total number os processes(maximum 20):"<<endl;
    cin>>n;

    vector<process> Processes(n);

    cout<<"\nEnter Process Burst Time and Priority"<<endl;
    for(i=0; i<n; i++){
        Processes[i].id = i+1;
        cout<<"P["<<i+1<<"]:\n";
        cout<<"Burst time: ";
        cin>>Processes[i].burst_time;
        cout<<"Priority: ";
        cin>>Processes[i].priority;
    }
    sort(Processes.begin(), Processes.end(), [](process& a, process& b){
        return a.priority < b.priority;
    });
    
    int total_twt = 0;
    int total_tat = 0;
    int wt = 0;
    
    cout << "\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (const auto &proc : Processes) {
        int turnaround_time = wt + proc.burst_time;
        cout << "P[" << proc.id << "]\t" << proc.burst_time << "\t\t"
                  << wt << "\t\t" << turnaround_time << "\n";
        total_twt += wt;
        total_tat += turnaround_time;
        wt += proc.burst_time;
    }

    cout << "\nAverage Waiting Time: "
              << static_cast<float>(total_twt) / n << "\n";
    cout << "Average Turnaround Time: "
              << static_cast<float>(total_tat) / n << "\n";

    return 0;
}