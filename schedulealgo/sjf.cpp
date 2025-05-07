#include<iostream>
#include<algorithm>
using namespace std;
/*
bt->burst time
wt-> wait time
tat -> turnaround time
avwt -> average wait-time
avtat -> average turn-around time
*/
int main(){
    int bt[20], p[20], wt[20], tat[20], i, j, n, total=0, pos, temp;
    float avg_wt, avg_tat;
    cout<<"Enter total number os processes(maximum 20):"<<endl;
    cin>>n;

    cout<<"\nEnter Process Burst Times"<<endl;
    for(i=0; i<n; i++){
        cout<<"P["<<i+1<<"]:";
        cin>>bt[i];
        p[i] = i+1;
    }

    //sort burst times
    for(i=0;i<n;i++){
        pos = i;
        for(j=i+1;j<n;j++){
            if(bt[j]<bt[pos]) pos = j;
        }
        swap(bt[i], bt[pos]);
        swap(p[i], p[pos]);
    }

    wt[0]=0;
    for(i=1;i<n;i++){
        wt[i]=0;
        for(j=0;j<i;j++) wt[i] += bt[j];
        total += wt[i];
    }
    avg_wt = (float)total/n;
    total = 0;
    cout<<"\nProcess\tBurstTime\tWaitingTime\tTurnaroundTime"<<endl;
    for(i=0;i<n; i++){
        tat[i] = bt[i]+wt[i];
        total += tat[i];
        cout<<"\nP["<<p[i]<<"]"<<"\t\t"<<bt[i]<<"\t\t"<<wt[i]<<"\t\t"<<tat[i]<<endl;
    }

    avg_tat=(float)total/n;
    cout<<"\nAverage Waiting Time: "<<avg_wt<<endl;
    cout<<"\nAverage Turnaround Time: "<<avg_tat<<endl;
    return 0;
}