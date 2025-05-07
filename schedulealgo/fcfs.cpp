#include<iostream>
using namespace std;
/*
bt->burst time
wt-> wait time
tat -> turnaround time
avwt -> average wait-time
avtat -> average turn-around time
*/

int main(){
    int n, bt[20], wt[20], tat[20], avwt=0, avtat=0, i, j;
    cout<<"Enter total number os processes(maximum 20):"<<endl;
    cin>>n;

    cout<<"\nEnter Process Burst Times"<<endl;
    for(i=0; i<n; i++){
        cout<<"P["<<i+1<<"]:";
        cin>>bt[i];
    }

    wt[0] = 0; //wait time for first process is 0
    for(i=1; i<n; i++){
        wt[i] = 0;
        for(j=0;j<i;j++) wt[i] += bt[j]; // add up all the wait times for next process
    }
    cout<<"\nProcess BurstTime WaitingTime TurnaroundTime"<<endl;
    for(i=0;i<n; i++){
        tat[i] = bt[i]+wt[i];
        avwt += wt[i];
        avtat += tat[i];
        cout<<"\nP["<<i+1<<"]"<<"\t"<<bt[i]<<"\t"<<wt[i]<<"\t"<<tat[i]<<endl;
    }
    avwt /= i;
    avtat /= i;
    cout<<"\nAverage Waiting Time: "<<avwt<<endl;
    cout<<"\nAverage Turnaround Time: "<<avtat<<endl;
    return 0;

}