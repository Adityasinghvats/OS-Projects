#include<iostream>
#include<thread>
using namespace std;

//this algo solves the problems of concurrency of lockVariable approach and waitTurn approach

#define TRUE 1
#define FALSE 0
#define N 2

int turn = 0;
int interested[N];
int x = 0;

void enter_section(int process){
    int other = 1 - process;
    interested[other] = TRUE;
    turn = process;
    while(turn == process && interested[other] == TRUE);
}

void leave_section(int process){
    interested[process] = FALSE;
}

class thread_object{
    public:
    void operator()(int process){
        for(int i=0;i<1000000000; i++){
            enter_section(process);
            x += 1;
            cout<<"Thread "<<process<<" "<<x<<endl;
            leave_section(process);
        }
    }
};

int main(){
    thread_object obj;
    std::thread t1(obj, 0);
    std::thread t2(obj, 1);
    t1.join();
    t2.join();
    return 0;
}